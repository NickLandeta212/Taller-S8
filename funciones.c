#include <stdio.h>
#include <string.h>
#include "funciones.h"
#include <math.h>
float validarIngreso() {
     float a;
     int val;
    do {
     fflush(stdin);
     val = scanf("%f", &a);
     if (val != 1) {
     printf("Se ingreso un valor erroneo. Ingrese nuevamente:\n");
     while (getchar() != '\n'); // Limpiar el buffer de entrada
    } else if (a < 0) {
    printf("Ingrese un valor positivo:");
    }
    } while (val != 1 || a < 0);
    return a;
    }
    
int menu(){
    int opc;
    printf("Selecciones una opcion:\n");
    printf("1. Registrar producto\n");
    printf("2. Ingrese los ingredientes a utilizar y su cantidad\n");
    printf("3. Ingrese el pedido\n");
    printf("4. Precio promedio de todos los productos\n");
    printf("5. Busqueda de producto\n");
    printf("6. Salir\n");
    printf(">> ");
    opc=validarIngreso();
    return opc;
}

int IngresarProductos(char nombres[5][30], int contp) {
    if (contp < 5) {
        printf("Ingrese el nombre del producto %d: ", contp + 1);
        fflush(stdin); // Limpiar el buffer de entrada
        fgets(nombres[contp], 30, stdin);

        // Elimina el salto de línea al final del nombre
        int len = strlen(nombres[contp]) - 1;
        if (nombres[contp][len] == '\n') {
            nombres[contp][len] = '\0';
        }


        contp++;

    } else {
        printf("No se pueden ingresar más productos. El límite es 5.\n");
    }

    return contp;
}

void RegistrarIngredientes(char ingredientes[10][30], float cantidades[10], int *contador) {
    if (*contador < 10) {
        printf("Ingrese el nombre del ingrediente %d: ", *contador + 1);
        fflush(stdin);
        fgets(ingredientes[*contador], 30, stdin);

        // Eliminar salto de línea
        int len = strlen(ingredientes[*contador]) - 1;
        if (ingredientes[*contador][len] == '\n') {
            ingredientes[*contador][len] = '\0';
        }

        printf("Ingrese la cantidad del ingrediente %d: ", *contador + 1);
        cantidades[*contador] = validarIngreso();

        (*contador)++;
    } else {
        printf("No se pueden ingresar más ingredientes. Límite alcanzado.\n");
    }
}
