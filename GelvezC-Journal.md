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

Conceptos aprendidos sobre error e incertidumbre:

+ 1

+ 2

+ 3

+ 4

###Clase 16-Jun-2015

**HandsOn-7**

