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
