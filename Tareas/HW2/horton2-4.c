#include <stdio.h>
/*Trabajo junto a Juan Vargas */
int main(void)
{
    /*declaración de variables*/
    float horas = 0.0f;
    float salario = 0.0f;
    float salarioHora=0.0f;
    int dolares;
    int cent;
    /*se pregunta por la información necesaria*/
    printf("Ingrese su pago semanal:\n $ ");
    scanf("%f", &salario);
    
    printf("ingrese el numero de horas trabajadas: \n ");
    scanf("%f", &horas);
    /*se calcula el pago por hora*/
    salarioHora=salario/horas;
    
    dolares= (int) salarioHora;
    cent = (int) (salarioHora*100)%100;
    printf("Your average hourly pay rate is %d dollars and %d cents.\n", dolares, cent);
    return 0;
}
