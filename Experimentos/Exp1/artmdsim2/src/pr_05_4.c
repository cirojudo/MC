
/* [[pr_05_4 - space-time correlations]] */


/*********************************************************************

  (C) 2004  D. C. Rapaport

  This software is copyright material accompanying the book
  "The Art of Molecular Dynamics Simulation", 2nd edition,
  by D. C. Rapaport, published by Cambridge University Press (2004).

**********************************************************************/


#include "in_mddefs.h"

typedef struct {
  VecR r, rv, ra;
} Mol;
typedef struct {
  real **acfST, *orgST;
  int count;
} TBuf;

Mol *mol;
VecR region, vSum;
VecI initUcell;
real deltaT, density, rCut, temperature, timeNow, uSum, velMag, vvSum;
Prop kinEnergy, totEnergy;
int moreCycles, nMol, stepAvg, stepCount, stepEquil, stepLimit;
VecI cells;
int *cellList;
real dispHi, rNebrShell;
int *nebrTab, nebrNow, nebrTabFac, nebrTabLen, nebrTabMax;
real kinEnInitSum;
int stepInitlzTemp;
TBuf *tBuf;
real **avAcfST, *valST;
int countCorrAv, limitCorrAv, nBuffCorr, nFunCorr, nValCorr, stepCorr;

NameList nameList[] = {
  NameR (deltaT),
  NameR (density),
  NameI (initUcell),
  NameI (limitCorrAv),
  NameI (nBuffCorr),
  NameI (nebrTabFac),
  NameI (nFunCorr),
  NameI (nValCorr),
  NameR (rNebrShell),
  NameI (stepAvg),
  NameI (stepCorr),
  NameI (stepEquil),
  NameI (stepInitlzTemp),
  NameI (stepLimit),
  NameR (temperature),
};


int main (int argc, char **argv)
{
  GetNameList (argc, argv);
  PrintNameList (stdout);
  SetParams ();
  SetupJob ();
  moreCycles = 1;
  while (moreCycles) {
    SingleStep ();
    if (stepCount >= stepLimit) moreCycles = 0;
  }
}


void SingleStep ()
{
  ++ stepCount;
  timeNow = stepCount * deltaT;
  LeapfrogStep (1);
  ApplyBoundaryCond ();
  if (nebrNow) {
    nebrNow = 0;
    dispHi = 0.;
    BuildNebrList ();
  }
  ComputeForces ();
  LeapfrogStep (2);
  EvalProps ();
  if (stepCount < stepEquil) AdjustInitTemp ();
  AccumProps (1);
  if (stepCount % stepAvg == 0) {
    AccumProps (2);
    PrintSummary (stdout);
    AccumProps (0);
  }
  if (stepCount > stepEquil && (stepCount - stepEquil) %
     stepCorr == 0) EvalSpacetimeCorr ();
}

void SetupJob ()
{
  AllocArrays ();
  stepCount = 0;
  InitCoords ();
  InitVels ();
  InitAccels ();
  AccumProps (0);
  InitSpacetimeCorr ();
  kinEnInitSum = 0.;
  nebrNow = 1;
}

void SetParams ()
{
  rCut = pow (2., 1./6.);
  VSCopy (region, 1. / pow (density / 4., 1./3.), initUcell);
  nMol = 4 * VProd (initUcell);
  velMag = sqrt (NDIM * (1. - 1. / nMol) * temperature);
  VSCopy (cells, 1. / (rCut + rNebrShell), region);
  nebrTabMax = nebrTabFac * nMol;
}

void AllocArrays ()
{
  int k, nb;

  AllocMem (mol, nMol, Mol);
  AllocMem (cellList, VProd (cells) + nMol, int);
  AllocMem (nebrTab, 2 * nebrTabMax, int);
  AllocMem (valST, 24 * nFunCorr, real);
  AllocMem2 (avAcfST, 3 * nFunCorr, nValCorr, real);
  AllocMem (tBuf, nBuffCorr, TBuf);
  for (nb = 0; nb < nBuffCorr; nb ++) {
    AllocMem (tBuf[nb].orgST, 24 * nFunCorr, real);
    AllocMem2 (tBuf[nb].acfST, 3 * nFunCorr, nValCorr, real);
  }
}


void BuildNebrList ()
{
  VecR dr, invWid, rs, shift;
  VecI cc, m1v, m2v, vOff[] = OFFSET_VALS;
  real rrNebr;
  int c, j1, j2, m1, m1x, m1y, m1z, m2, n, offset;

  rrNebr = Sqr (rCut + rNebrShell);
  VDiv (invWid, cells, region);
  for (n = nMol; n < nMol + VProd (cells); n ++) cellList[n] = -1;
  DO_MOL {
    VSAdd (rs, mol[n].r, 0.5, region);
    VMul (cc, rs, invWid);
    c = VLinear (cc, cells) + nMol;
    cellList[n] = cellList[c];
    cellList[c] = n;
  }
  nebrTabLen = 0;
  for (m1z = 0; m1z < cells.z; m1z ++) {
    for (m1y = 0; m1y < cells.y; m1y ++) {
      for (m1x = 0; m1x < cells.x; m1x ++) {
        VSet (m1v, m1x, m1y, m1z);
        m1 = VLinear (m1v, cells) + nMol;
        for (offset = 0; offset < N_OFFSET; offset ++) {
          VAdd (m2v, m1v, vOff[offset]);
          VZero (shift);
          VCellWrapAll ();
          m2 = VLinear (m2v, cells) + nMol;
          DO_CELL (j1, m1) {
            DO_CELL (j2, m2) {
              if (m1 != m2 || j2 < j1) {
                VSub (dr, mol[j1].r, mol[j2].r);
                VVSub (dr, shift);
                if (VLenSq (dr) < rrNebr) {
                  if (nebrTabLen >= nebrTabMax)
                     ErrExit (ERR_TOO_MANY_NEBRS);
                  nebrTab[2 * nebrTabLen] = j1;
                  nebrTab[2 * nebrTabLen + 1] = j2;
                  ++ nebrTabLen;
                }
              }
            }
          }
        }
      }
    }
  }
}


void ComputeForces ()
{
  VecR dr;
  real fcVal, rr, rrCut, rri, rri3, uVal;
  int j1, j2, n;

  rrCut = Sqr (rCut);
  DO_MOL VZero (mol[n].ra);
  uSum = 0.;
  for (n = 0; n < nebrTabLen; n ++) {
    j1 = nebrTab[2 * n];
    j2 = nebrTab[2 * n + 1];
    VSub (dr, mol[j1].r, mol[j2].r);
    VWrapAll (dr);
    rr = VLenSq (dr);
    if (rr < rrCut) {
      rri = 1. / rr;
      rri3 = Cube (rri);
      fcVal = 48. * rri3 * (rri3 - 0.5) * rri;
      uVal = 4. * rri3 * (rri3 - 1.) + 1.;
      VVSAdd (mol[j1].ra, fcVal, dr);
      VVSAdd (mol[j2].ra, - fcVal, dr);
      uSum += uVal;
    }
  }
}


void LeapfrogStep (int part)
{
  int n;

  if (part == 1) {
    DO_MOL {
      VVSAdd (mol[n].rv, 0.5 * deltaT, mol[n].ra);
      VVSAdd (mol[n].r, deltaT, mol[n].rv);
    }
  } else {
    DO_MOL VVSAdd (mol[n].rv, 0.5 * deltaT, mol[n].ra);
  }
}


void ApplyBoundaryCond ()
{
  int n;

  DO_MOL VWrapAll (mol[n].r);
}


void AdjustInitTemp ()
{
  real vFac;
  int n;

  kinEnInitSum += kinEnergy.val;
  if (stepCount % stepInitlzTemp == 0) {
    kinEnInitSum /= stepInitlzTemp;
    vFac = velMag / sqrt (2. * kinEnInitSum);
    DO_MOL VScale (mol[n].rv, vFac);
    kinEnInitSum = 0.;
  }
}


void InitCoords ()
{
  VecR c, gap;
  int j, n, nx, ny, nz;

  VDiv (gap, region, initUcell);
  n = 0;
  for (nz = 0; nz < initUcell.z; nz ++) {
    for (ny = 0; ny < initUcell.y; ny ++) {
      for (nx = 0; nx < initUcell.x; nx ++) {
        VSet (c, nx + 0.25, ny + 0.25, nz + 0.25);
        VMul (c, c, gap);
        VVSAdd (c, -0.5, region);
        for (j = 0; j < 4; j ++) {
          mol[n].r = c;
          if (j != 3) {
            if (j != 0) mol[n].r.x += 0.5 * gap.x;
            if (j != 1) mol[n].r.y += 0.5 * gap.y;
            if (j != 2) mol[n].r.z += 0.5 * gap.z;
          }
          ++ n;
        }
      }
    }
  }
}


void InitVels ()
{
  int n;

  VZero (vSum);
  DO_MOL {
    VRand (&mol[n].rv);
    VScale (mol[n].rv, velMag);
    VVAdd (vSum, mol[n].rv);
  }
  DO_MOL VVSAdd (mol[n].rv, - 1. / nMol, vSum);
}


void InitAccels ()
{
  int n;

  DO_MOL VZero (mol[n].ra);
}


void EvalSpacetimeCorr ()
{
  real b, c, c0, c1, c2, kVal, s, s1, s2, w;
  int j, k, m, n, nb, nc, nv;

  for (j = 0; j < 24 * nFunCorr; j ++) valST[j] = 0.;
  kVal = 2. * M_PI / region.x;
  DO_MOL {
    j = 0;
    for (k = 0; k < 3; k ++) {
      for (m = 0; m < nFunCorr; m ++) {
        if (m == 0) {
          b = kVal * VComp (mol[n].r, k);
          c = cos (b);
          s = sin (b);
          c0 = c;
        } else if (m == 1) {
          c1 = c;
          s1 = s;
          c = 2. * c0 * c1 - 1.;
          s = 2. * c0 * s1;
        } else {
          c2 = c1;
          s2 = s1;
          c1 = c;
          s1 = s;
          c = 2. * c0 * c1 - c2;
          s = 2. * c0 * s1 - s2;
        }
        valST[j ++] += mol[n].rv.x * c;
        valST[j ++] += mol[n].rv.x * s;
        valST[j ++] += mol[n].rv.y * c;
        valST[j ++] += mol[n].rv.y * s;
        valST[j ++] += mol[n].rv.z * c;
        valST[j ++] += mol[n].rv.z * s;
        valST[j ++] += c;
        valST[j ++] += s;
      }
    }
  }
  for (nb = 0; nb < nBuffCorr; nb ++) {
    if (tBuf[nb].count == 0) {
      for (j = 0; j < 24 * nFunCorr; j ++)
         tBuf[nb].orgST[j] = valST[j];
    }
    if (tBuf[nb].count >= 0) {
      for (j = 0; j < 3 * nFunCorr; j ++)
         tBuf[nb].acfST[j][tBuf[nb].count] = 0.;
      j = 0;
      for (k = 0; k < 3; k ++) {
        for (m = 0; m < nFunCorr; m ++) {
          for (nc = 0; nc < 4; nc ++) {
            nv = 3 * m + 2;
            if (nc < 3) {
              w = Sqr (kVal * (m + 1));
              -- nv;
              if (nc == k) -- nv;
              else w *= 0.5;
            } else w = 1.;
            tBuf[nb].acfST[nv][tBuf[nb].count] +=
               w * (valST[j] * tBuf[nb].orgST[j] +
               valST[j + 1] * tBuf[nb].orgST[j + 1]);
            j += 2;
          }
        }
      }
    }
    ++ tBuf[nb].count;
  }
  AccumSpacetimeCorr ();
}

void AccumSpacetimeCorr ()
{
  int j, n, nb;

  for (nb = 0; nb < nBuffCorr; nb ++) {
    if (tBuf[nb].count == nValCorr) {
      for (j = 0; j < 3 * nFunCorr; j ++) {
        for (n = 0; n < nValCorr; n ++)
           avAcfST[j][n] += tBuf[nb].acfST[j][n];
      }
      tBuf[nb].count = 0;
      ++ countCorrAv;
      if (countCorrAv == limitCorrAv) {
        for (j = 0; j < 3 * nFunCorr; j ++) {
          for (n = 0; n < nValCorr; n ++)
             avAcfST[j][n] /= 3. * nMol * limitCorrAv;
        }
        PrintSpacetimeCorr (stdout);
        ZeroSpacetimeCorr ();
      }
    }
  }
}

void InitSpacetimeCorr ()
{
  int nb;

  for (nb = 0; nb < nBuffCorr; nb ++)
     tBuf[nb].count = - nb * nValCorr / nBuffCorr;
  ZeroSpacetimeCorr ();
}

void ZeroSpacetimeCorr ()
{
  int j, n;

  countCorrAv = 0;
  for (j = 0; j < 3 * nFunCorr; j ++) {
    for (n = 0; n < nValCorr; n ++) avAcfST[j][n] = 0.;
  }
}

void PrintSpacetimeCorr (FILE *fp)
{
  real tVal;
  int j, k, n;
  char *header[] = {"cur-long", "cur-trans", "density"};

  fprintf (fp, "space-time corr\n");
  for (k = 0; k < 3; k ++) {
    fprintf (fp, "%s\n", header[k]);
    for (n = 0; n < nValCorr; n ++) {
      tVal = n * stepCorr * deltaT;
      fprintf (fp, "%7.3f", tVal);
      for (j = 0; j < nFunCorr; j ++)
         fprintf (fp, " %8.4f", avAcfST[3 * j + k][n]);
      fprintf (fp, "\n");
    }
  }
  fflush (fp);
}


void EvalProps ()
{
  real vv, vvMax;
  int n;

  VZero (vSum);
  vvSum = 0.;
  vvMax = 0.;
  DO_MOL {
    VVAdd (vSum, mol[n].rv);
    vv = VLenSq (mol[n].rv);
    vvSum += vv;
    vvMax = Max (vvMax, vv);
  }
  dispHi += sqrt (vvMax) * deltaT;
  if (dispHi > 0.5 * rNebrShell) nebrNow = 1;
  kinEnergy.val = 0.5 * vvSum / nMol;
  totEnergy.val = kinEnergy.val + uSum / nMol;
}


void AccumProps (int icode)
{
  if (icode == 0) {
    PropZero (totEnergy);
    PropZero (kinEnergy);
  } else if (icode == 1) {
    PropAccum (totEnergy);
    PropAccum (kinEnergy);
  } else if (icode == 2) {
    PropAvg (totEnergy, stepAvg);
    PropAvg (kinEnergy, stepAvg);
  }
}


void PrintSummary (FILE *fp)
{
  fprintf (fp,
     "%5d %8.4f %7.4f %7.4f %7.4f %7.4f %7.4f\n",
     stepCount, timeNow, VCSum (vSum) / nMol, PropEst (totEnergy),
     PropEst (kinEnergy));
  fflush (fp);
}


#include "in_rand.c"
#include "in_errexit.c"
#include "in_namelist.c"

