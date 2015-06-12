#!/bin/bash

#se crea un while que siempre sea cierto para que el loop del ciculo se infinito
while true
do
#se hace un sleep y un clear para que la gráfica no se genere instantaneamente y se cree una simulación de movimiento
 sleep 0.4
 clear
 # el script del punto anterior recibe una función de cos^2 con una frecuencia de 1/10
 ./circle.sh $(echo "c($t/10)*c($t/10)" | bc -l) 
 let t++
done
