#!/bin/bash

awk -F"," '{if ($1=='$a') print $0}' $b #busca las  primeras lineas de una columna del archivo entregado
