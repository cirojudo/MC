#./bin/bash

echo "##########################################"
figlet StarDate #imprime el nombre del programa
echo "##########################################"
figlet $1 #imprime el año que entra por parametro

grep $1 worldhistory.tsv | sed 's/\t/---\>/g' #imprime la línea correspondiente a un evento historico

echo "##########################################"

echo LOOK AT THE FOLLOWING STARS:

echo RA/     DEC/      HIP No.

#Primero se convierte una variable bash en una variable para awk donde se buscan las estrellas en el intervalo y se imprimen las 5 primeras, con su RA, DEC y nombre
awk -v ano="$1" -F"," '{if($10<(2015-ano+1)&&$10>(2015-ano)) print $8,$9,$2}' hyg.csv | head -5
