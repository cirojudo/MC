#!/bin/bash

wget https://raw.githubusercontent.com/ComputoCienciasUniandes/MetodosComputacionalesLaboratorio/master/2015-V/actividades/lottery/lottery.csv

figlet Codigo 201127636

awk -F"," '{if($1==201127636) print $2}' lottery.csv

sed '1q;d' lottery.csv

