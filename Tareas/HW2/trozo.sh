#!/bin/bash

awk '{print substr($0,'$1','$(echo "$2-$1" | bc -l)')}' $3
