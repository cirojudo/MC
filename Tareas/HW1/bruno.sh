#./bin/bash
# Se descarga el archivo csv
wget https://raw.githubusercontent.com/ComputoCienciasUniandes/MetodosComputacionales/master/homework/2015-V/HW1/kepler.csv

echo =====================================
#se cuentan la cantidad de planetas según las lineas
echo Cantidad de Planetas: $(awk -F"," '{print $1}' kepler.csv | sed '1d' | wc -l)

echo =====================================
#se compara con la masa menos a una centésima y además que el valor sea distinto de cero
echo Cantidad de planetas con una masa menor a una centésima de la masa de Júpiter: $(awk -F"," '{if ($2 < 0.01 && $2 > 0) print $2}' kepler.csv | wc -l)

echo Y sus nombres son:
#se imprime la primera columna correspondiente al nombre
awk -F"," '{if ($2 < 0.01 && $2 > 0) print $1}' kepler.csv

echo =====================================

echo El planeta con el MENOR periodo orbital es:
#se organiza la tabla según el periodo orbital y se imprime el primer nombre del mismo
sort -t "," --key=6 -n kepler.csv | awk -F"," '{print $1}' | sed '1d'| head -1
