#include <stdio.h>
#define inches 12  
#define yards 0.027777
/*Trabajo junto a Juan Vargas*/

int main (void){

  float  xIn, yIn, xFt, yFt, xYd, yYd, area; /*declaración de variables*/

    /*se leen los datos*/
	printf("Type width of the room (feet): \n");
	scanf("%f", &xFt);
    printf("Type width of the room (inches): \n");
	scanf("%f", &xIn);

	printf("Type length of the room (feet): \n");
	scanf("%f", &yFt);
    printf("Type length of the room (inches): \n");
	scanf("%f", &yIn);

	xYd=(inches*xFt+xIn)*yards; /*calculo de x*/
	yYd=(inches*yFt+yIn)*yards;/*calculo de y*/

	area= xYd*yYd; /*calculo del área final*/

	printf("Total room area: %.2lf Yd \n", area);
	return 0;
}
