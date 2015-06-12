#!/bin/bash

for file in $(ls *.c)
 do
  echo "#nombre de archivo: $file" >> nombres.md
  echo "\`\`\`" >> nombres.md
  cat $file >> nombres.md 
  echo "\`\`\`" >> nombres.md
done 

