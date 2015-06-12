#include "stdio.h"
#include <string.h>
/*Trabajo junto a Juan Vargas*/

int main(void)
{
    /*declaración de constantes*/
    const float BARATO= 3.50f;
    const float CARO= 5.50f;
    /*declaración de variables*/
    int cantidad;
    int modelo;
    float rta=0.0f;
    printf("Cual producto desea? Si es \"Basico\" ingrese 1 ó \"Completo\" ingrese 2\n");
    scanf("%d",&modelo);
    printf("cuantos productos desea?\n");
    scanf("%d",&cantidad);
    /*se valida cual producto es*/
    if(modelo== 1)
    {
        rta=cantidad*BARATO;
        printf("TTOTAL: $ %.2f\n",rta);/*calculo del total*/
     
    }
    else
    {
        rta=cantidad*CARO;
        printf("TOTAL: $ %.2f\n",rta);
        

    }
    return 0;
    
}
