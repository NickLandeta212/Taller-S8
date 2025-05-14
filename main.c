#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {
    char nombres[5][30];
    char ingredientes[10][30];
    float cantidades[10];
    int opc;
    int contp=0,conti=0;
    do
    {
        opc= menu();
        switch (opc)
        {
        case 1:
            contp=IngresarProductos(nombres,contp);
            break;
        case 2:
            RegistrarIngredientes(ingredientes,cantidades,conti);
        
        default:
            break;
        }
    } while (opc !=6);
    

    return 0;
}