#./bin/bash
echo ==========================================
figlet arXiv #imprime en nombre de la página
echo ==========================================
echo Searching the arXiv for the new stuff
echo http://arxiv.org/list/astro-ph/new #URL de la sección de astronomía
echo ==========================================
echo keyword: $1 #se imprime la palabra seleccionada
echo ==========================================
#se imprime la cantidad de articulos encontrados según la palabra buscada
# 1. Se eliminan los caracteres no deseados
# 2. Se reemplazan los caracteres 
# 3. Se buscan las palabas que concidan con la busqueda
echo articles found: $(curl -s http://arxiv.org/list/astro-ph/new | grep -iw Title:\</span\> | sed 's/.*>//g' | grep -iw $1| wc -l)

curl -s http://arxiv.org/list/astro-ph/new | grep -iw Title:\</span\> | sed 's/.*>//g' | grep -iw $1

echo ==========================================


