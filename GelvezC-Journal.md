# Bitácora del curso Métodos Computacionales (2015-19)
**Ciro Fernando Gélvez Pedroza**

## Semana 1

En esta semana se creó un repositorio en GitHub del curso llamado MC, se vió como hacer nuevos commits y posteriormente un push para subirlos a la red. El proceso para esto fue el siguiente.

```
cf.gelvez1721@compufi9:~> git clone https://github.com/cirojudo
Cloning into 'cirojudo'...
fatal: repository 'https://github.com/cirojudo/' not found
cf.gelvez1721@compufi9:~> git config --global user.name "Ciro Fernando Gelvez Pedroza"
cf.gelvez1721@compufi9:~> git config --global user.email "cf.gelvez1721.uniandes.edu.co"
cf.gelvez1721@compufi9:~> git clone https://github.com/cirojudo/MC
Cloning into 'MC'...
warning: You appear to have cloned an empty repository.
Checking connectivity... done
cf.gelvez1721@compufi9:~/MC> emacs GelvezC-Journal.md
cf.gelvez1721@compufi9:~/MC> git add GelvezC-Journal.md 
cf.gelvez1721@compufi9:~/MC> git status
# On branch master
#
# Initial commit
#
# Changes to be committed:
#   (use "git rm --cached <file>..." to unstage)
#
#       new file:   GelvezC-Journal.md
#                                                                                                                                 
cf.gelvez1721@compufi9:~/MC> git commit
[master (root-commit) 22db2c9] Aquí está ,mi primera contribución al curso
 1 file changed, 12 insertions(+)
 create mode 100644 GelvezC-Journal.md
cf.gelvez1721@compufi9:~/MC> git push origin master 
Username for 'https://github.com': cirojudo
Password for 'https://cirojudo@github.com': 
Counting objects: 3, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 444 bytes | 0 bytes/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To https://github.com/cirojudo/MC
 * [new branch]      master -> master
```

###Primera Clase 27-May-2015
¡Hola Mundo!, aqui estoy comenzando el curso de **Métodos Computacionales**

Herramientas del curso:

+ git
+ GitHub
+ Bash
+ C
+ y Python

y los Métodos a  estudiar son:

1. Interpolación
2. Análisis de Fourier
3. Diferenciación e integración numéricas.
4. Ecuaciones diferenciales ordinarias y parciales
5. Método de MonteCarlo.

###Clase 29-May-2015

**HandsOn-1**

GIT

1. En su repositorio de GitHub cree un archivo y haga un commit. Luego borre el archivo y haga otro commit. A continuación regrese al primer commit hecho haciendo un checkout del hash adecuado y verifique que en el directorio de trabajo reaparece el archivo borrado. Finalmente regrese a master y fíjese que el archivo borrado ya no aparece.

Creamos un archivo de bash con `emacs ejemplo.sh`.

Para hacer el commit hacemos `git add ejemplo.sh` y luego `git commit -m "primer commit"`.

Borramos el archivo `git rm ejemplo.sh` y hacemos de nuevo el commit `git commit -m "archivo borrado"`.

Para ver el archivo borrado hacemos `git log` y `git checkout`

2. Copie y descomprima un clon del repositorio de nuestro curso que está ubicado en `/usuarios/homenfs7/j-lizara/Shared/MetodosComputacionales.tgz` y haga algo de paleontología encontrando la fecha del segundo commit y el tema de la semana 15 del primer syllabus.

+ Copiamos el archivo `scp linus@compufi3.uniandes.edu.co:/usuarios/homenfs7/j-lizara/Shared/MetodosComputacionales.tgz ./ `

+ La fecha del primer commit es `Sat Jan 5 23:05:56 2013 -500`

+ El tema de la semana 15 del Syllabus es `Métodos de Interferencia Bayesiana`

BASH

1. Escriba un script de `bash` que reciba un número e imprima usando `awk` las líneas de un `csv` cuya primera columna sea igual al número entregado.

```
#!/bin/bash
awk -F"," '{if ($1=='$a') print $0}' $b #busca loa primera columna del archivo entregado
```
2. Escriba un script de `bash` que imprima una matrix cuadrada de 5 X 5 con la secuencia de los primeros 25 enteros de izquierda a a derecha y de arriba a abajo.

```
#!/bin/bash
n=5
for i in $(seq 1 $n $(n*n))
do
  seq -s ' ' $i $((i+n-1))
done
```
3. Escriba un script de `bash` que determine si en la portada de ElTiempo aparece alguna palabra clave elegida.

```
#!/bin/bash
curl -s https://www.eltiempo.com/ #url de ElTiempo
grep '<h2 itemprop'.*'><'a.*' >' #Buscamos lineas que no nos interesan
sed s/' '.*'<h2 it'.*'><'a.*' >'// #Reemplazamos las líneas buscadas
sed s/'<\/a><\/h2>'// #Dejamos solo los Titulares
```

##Semana 2

**Tema**:

+ En esta semana se vio la utilidad de las expresiones regulares para limpiar archivos con muchos datos, vemos aquí algunas de ellas:

```
^ inicio de línea
$ fin de línea
\d dígito 
\D no dígito
. cualquier caracter
\t Tabulación

Cuantificadores
* 0 o más
+ 1 o más
? 0 o 1 vez

Caracteres especiales
^ { } + [ ] * $ \ | ? < >
```

+ También vimos una herrmaienta para realizar gráficas llamada GNUPLOT, se pueden realizar gráficas en la terminal.


### Clase 02-Jun-2015

**Hands-on 2**

Expresiones regulares

1. Construya una expresión regular que represente cuatro caracteres al inicio de una línea junto con un espacio a continuación.

+ Se realizo con el editor de texto de UBUNTU-gedit, `^....`

2. Descargue con `curl` el código fuente de la página Pi - 10 Million Digits, límpielo de todo caracter diferente a los dígitos de pi y divídalo en líneas con 20 dígitos cada una quedando ellas en un archivo con nombre PIslices20.dat.

```
curl http://pi.karmona.com/ #Descargamos el texto de la pagina

\<.*\> :# Quitamos toda la información extra que viene de la página.

Pi - .* # Quitamos lo restante "Pi - 10 Million Digits"

\n :# Juntamos todas las líneas en una para poderlas separar luego.

fold -w20 #las dividimos en líneas de 20 numeros.
```

GNUPLOT

1. Escriba un script de `bash` que reciba tres argumentos, el nombre de un archivo csv, el número de la columna para el eje horizontal y el número de la columna para el eje verticual y que haga con `gnuplot` una gráfica de dispersión con puntos visibles y unidos por líneas rectas. Haga pruebas con el archivo [joviansatellites.csv](https://raw.githubusercontent.com/ComputoCienciasUniandes/MetodosComputacionales/master/examples/joviansatellites.csv)]

```
#!/bin/bash
1=$1    #definimos las 3 variables
2=$2
3=$3
gnuplot<< EOF #Abrimos GNUPLOT
    set datafile separator "," #Leemos un .csv
    set term dumb #lo imprimimos en la terminal
    set parametric #gráfica paramétrica
    set size ratio 1 #comando para estética
    plot "${1}" using ${2}:${3} with lines #hacemos la gráfica
```

### Clase 05-Jun-2015

**HandsOn-3**

1. Aprenda algo sobre `make`, y haga un resumen básico de su funcionalidad.

+ Es una herramienta bastante útil para trabajos o proyectos que utilizan distinto lenguajes de programación.

+ Es posible compilar distintos lenguajes a la vez para obtener cierto resultado, puede ser un trabajo experimental.

+ Se actualizan conjuntos de archivos que dependen de otros archivos.

+ Se puede ver como un arbol de tareas, si se modifica algo en una rama hay que compilar de nuevo el arbol completo. Por lo que `make` se encarga de definir prioridades y comprimir primero ciertos archivos de los cuales dependen los más grande

###Clase 09-Jun-2015

**HandsOn-4**

Proyecto:

###Clase 10-Jun-2015

**HandsOn-5**

El panel 5 x 5 se realizo de la siguiente manera:

```
%pylab inline
from numpy import sin,pi,linspace
from pylab import plot,show,subplot

a = [1,3,5,3,7,21,11,13,7,37,31,59,61,67,19,23,41,43,47,3,5,7,23,29,31]
b = [1,5,7,4,31,29,23,7,5,3,47,43,41,23,17,67,61,59,31,37,7,13,11,21,7]
delta = pi/2
t = linspace(-pi,pi,300)
figure(figsize(20,20))

for i in range(0,25):
 x = sin(a[i] * t + delta)
 y = sin(b[i] * t)
 subplot(5,5,i+1)
 plot(x,y)
 plt.axis('off')

show()
```

Lo que nos arroja una imagen como la siguiente:

![](https://raw.githubusercontent.com/cirojudo/MC/master/Hands-On/5/lissajous.png)

###Clase 12-Jun-2015

**HandsOn-6**

2.En su bitácora escriba al menos dos párrafos de resumen de lo aprendido sobre error e incertidumbre.

Conceptos aprendidos sobre error e incertidumbre:

+ Existen 4 tipos diferentes de error computacional, los cuales son:
    
    - Mala Teoría: Esto consiste en que los datos a analizar de por sí ya cuentan con un error y por ende al analizarlos tendremos un gran error en nuestros calculos, también pueden ser debidos a que el programa esté mal ejecutado o mal implementado.
    
    - Error aleatorio: Aunque no es muy común en el caso computacional, es necesario considerarlo ya que para simulaciones o programas que duren bastante tiempo ejecutandose, hay que tener la capacidad del PC y todo lo que esto conlleva, como la temperatura de operación y la fuente de energía.
    
    - Error de aproximación: Es el error mas común en estos casos, ya que el computador no es una herramienta que pueda realizar cálculos infinitos, por ende siempre se tiene un límite. Es decir que, por ejemplo al desarrollar una serie de con intervalo infinito, el pc aproximará este infinito hasta un numero en el cual el resultado tenga una buena precisión.

    - Errores de redondeo: Un poco parecidos al anterior, al usar numeros infinitos como es el caso de Pi, o del numero de euler,hay que tener en cuenta que el programa no utilizará todas sus cifras decimales ya que este no tiene fin, por ende en cada iteración con este tipo de numeros hay que fijarse en cuantos numeros decimales se están utilizando.

###Clase 16-Jun-2015

**HandsOn-7**

3.La tabla mostrada abajo tiene información sobre el campo magnético de un dipolo magnético a lo largo de su eje, haga un ajuste por mínimos cuadrados de acuerdo a un modelo teórico adecuado y calcule la magnitud del momento magnético del imán (en A m^2) y una tabla para B(x) con 100 renglones uniformemente espaciada entre el x=4.1cm y x=11.1cm. Haga una gráfica con los datos y el ajuste encontrado.

Para realizar el ajuste para encontrar la magnitud del momento dipolar del dipolo se realizó el siguiente código:

```
%matplotlib inline
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from scipy.optimize import curve_fit

disCamp=np.transpose(np.array([[2.3 , 2.8 , 3.2 , 3.7 , 4.3],[34745,19689,12594,7982,5822]]))
def Dipolo(z,mu):
    return 2*mu*(10**(-1))*(1/(z**3))
par,cov=curve_fit(Dipolo,disCamp[:,0],disCamp[:,1])
sep=np.linspace(2.3,4.3,100)
bsep=Dipolo(sep,*par)

print("| x/cm  |  B/uT    |")
for i in range(100):
    print ("{:.2f}".format(sep[i])).rjust(1),"|",("{:.2f}".format(bsep[i])).rjust(1)

print "Dipolo magnético en uAm^2", par*10**(-5)
plt.plot(sep,Dipolo(sep,*par))
plt.scatter(disCamp[:,0],disCamp[:,1])
plt.xlabel("Distancia \n [cm]")
plt.ylabel("Campo \n [uT]")
```

Las gráfica y el resultado para el momento dipolar magnético, se puede ver en el [HandsOn-7](https://github.com/cirojudo/MC/blob/master/Hands-On/7/HandsOn-7.ipynb).

**Proyecto Final**

- Sin importar el tema del proyecto a realizar, es de gran ayuda el método para la interpolación, ya que al hacer un procedimiento experimental estamos tomando cierto numero de datos, pero sabemos que para algunos casos basta con tomar una muestra lo sificientemente grande para obtener buenas respuestas. Pero con la ayuda de la interpolación podemos generar aún mas datos que nos ayuden a disminuir el error por la pequeña cantidad de datos que se tomen. Es decir que se puede ahorrar un poco de tiempo tomando datos y que el computador lo haga por nosotros, mientras así se pueden estar realizando otro tipo de tareas de el mismo proyecto.

###Clase 17-Jun-2015

**HandsOn-8**

1. (L1 Júpiter Io) Compare la solución exacta al primer punto de Lagrange del sistema Júpiter-Io con la aproximación para el caso M₂ << M₁. Hágalo utilizando root de scipy.optimize, ver sección 1.5.6 del Scipy Reference Guide.

El código para comparar la solución fue el siguiente:

```
from scipy.optimize import  root

r  = 422000
m1 = 1.898E27
m2 = 8.931E22

def func(x):
    return m2/(x**2) + (m1+m2)*(m1*r/(m1+m2) - x)/(r**3) - m1/((r-x)*(r-x))

print(root(func,r/3))
```

Y el resultado es:

```
status: 1
 success: True
     qtf: array([-1066.])
    nfev: 14
       r: array([  2.35150308e+11])
     fun: array([-2.])
       x: array([ 10474.55011186])
 message: 'The solution converged.'
    fjac: array([[-1.]])
```

GitHub


Calculadora: Se puede ver la implementación de una [calculadora](https://github.com/juannnesss/CAL/blob/master/calculadora.py) realizada en `python` por dos contribuidores en GitHub, esto es de grán importancia para el curso ya que se puede trabajar en un mismo proyecto con una o más personas. En este caso se realizó una calculadora que tiene las funciones más simples (suma,resta,multiplicación,división).


###Clase 23-Jun-2015

**HandsOn-10**

Estime la duración del ciclo solar analizando con una DFT los datos monthrg.dat. La descripción del archivo está aquí. Además utilice un filtro de altas frecuencias para obtener una gráfica similar a la mostrada abajo.




