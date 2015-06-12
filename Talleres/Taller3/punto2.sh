#!/bin/bash

let var = 1

for file in $(ls) #se toman todos los archivos
 do
 if (var=31) #se toman los 30 primeros
 cc -o "$first.out"
 grep -A 1 "Example" $file #se imprime la linea que dice Example
 open $first.out #se abre el erchivo
 read -p "presionar enter para compilar el siguiente" #al oprimir enter e compila el siguiente
  break
  let var++
done
 
    
