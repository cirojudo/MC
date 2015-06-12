#!/bin/bash

#a partir de una linea de letras se genera un archivo
cat $input > iter.txt

#se hace un ciclo que cambie las letras 10 veces
for i in {1..10}
 do
./flip.sh v z iter.txt > iter2.txt
./flip.sh h y iter2.txt > iter.txt
./flip.sh p x iter.txt > iter2.txt
./flip.sh u w iter2.txt > iter.txt
./flip.sh z v iter.txt > iter2.txt
./flip.sh s u iter2.txt > iter.txt
./flip.sh f t iter.txt > iter2.txt
./flip.sh g s iter2.txt > iter.txt
./flip.sh x r iter.txt > iter2.txt
./flip.sh e q iter2.txt > iter.txt
./flip.sh d p iter.txt > iter2.txt
./flip.sh r o iter2.txt > iter.txt
./flip.sh m n iter.txt > iter2.txt
./flip.sh b m iter2.txt > iter.txt
./flip.sh j l iter.txt > iter2.txt
./flip.sh a k iter2.txt > iter.txt
./flip.sh c j iter.txt > iter2.txt
./flip.sh y i iter2.txt > iter.txt
./flip.sh k h iter.txt > iter2.txt
./flip.sh t g iter2.txt > iter.txt
./flip.sh q f iter.txt > iter2.txt
./flip.sh o e iter2.txt > iter.txt
./flip.sh l d iter.txt > iter2.txt
./flip.sh w c iter2.txt > iter.txt
./flip.sh n b iter.txt > iter2.txt
./flip.sh i a iter2.txt > iter.txt
 done

#se muestra el archivo obtenido
cat iter.txt
#se remueven archivos adicionales
rm iter2.txt
