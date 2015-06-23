#!/bin/bash

n=5

for i in $(seq 1 $n $(n*n))
do
  seq -s ' ' $i $((i+n-1))
done
