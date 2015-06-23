#!/bin/bash

curl -s https://www.eltiempo.com/ #url de ElTiempo

grep '<h2 itemprop'.*'><'a.*' >' #Buscamos lineas que no nos interesan

sed s/' '.*'<h2 it'.*'><'a.*' >'// #Reemplazamos las líneas buscadas

sed s/'<\/a><\/h2>'// #Dejamos solo los Titulares
