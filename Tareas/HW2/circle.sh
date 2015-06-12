#!/bin/bash

#trabajo junto a Juan Vargas

#comando para seguir trabajando en gnuplot
gnuplot<<EOF

#se crea la gráfica en la terminal, paramétrica, se hace circular, se borran todos los ejes
set term dumb
set parametric
set size ratio 0.5
set key off
unset xtics
unset ytics
unset border

#el rango de la gráfica se pone en un cuadrado de lado 2
set xrange [-1:1]
set yrange [-1:1]
set trange [0:2*pi]

#se grafica el circulo
plot $1*sin(t), $1*cos(t) 
EOF
