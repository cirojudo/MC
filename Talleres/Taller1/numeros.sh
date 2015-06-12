#!/bin/bash

for i in {1..1000}
do
   echo "$i,$((i*i))"

done >> archivo_numeros.csv

