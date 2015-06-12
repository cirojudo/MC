#!/bin/bash
#Trabajo junto a Juan Vargas
#se crean dos numeros que entran por parametro
x=$1
y=$2

#a partir de un archivo que se lee se cambia una letra por otra en ambos sentidos
cat $3 | sed 's/'$x'/0/g' | sed 's/'$y'/1/g' | sed 's/0/'$y'/g' | sed 's/1/'$x'/g'
