#include <stdio.h>	
#define feet 0.083	
#define yard 0.027	
/*Trabajo junto a Juan Vargas*/

int main (){

  double inches,yards,feets; /*declaración de variables a usar*/

	printf("Distance to convert in INCHES: \n");

	scanf("%lf", &inches);		
	feets=feet*inches;
	yards=yard*inches; /*se realiza la conversión*/
	
	printf("%.2lf inches --->  %.2lf feet and %.2lf yards\n",inches,feets,yards);
	
	return 0;
}
