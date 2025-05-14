#include <stdio.h>
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
    printf("2. Precio total del inventario\n");
    printf("3. Producto mas caro y el mas barato\n");
    printf("4. Precio promedio de todos los productos\n");
    printf("5. Busqueda de producto\n");
    printf("6. Salir\n");
    printf(">> ");
    opc=validarIngreso();
    return opc;
}
int Ingreseproductos(char nombres[5][30], int ingredientes[][30],int cantidad[][], int contp, float precio[10]) {
    int len;
    if (contp < 10) {
        
        printf("Ingrese el nombre del producto %d: ", contp);
        fflush(stdin); // Limpiar el buffer de entrada
        fgets(nombres[contp], 30, stdin);
        // Elimina el salto de línea al final del nombre
        len = strlen(nombres[contp]) - 1;
        if (nombres[contp][len] == '\n') {
            nombres[contp][len] = '\0';
        }

        printf("Ingrese el stock del producto %d: ", contp);
        stock[contp] = validarIngreso();
        printf("Ingrese el precio del producto %d: ", contp);
        precio[contp] = validarIngreso();
        contp++;

    } else {
        printf("No se pueden ingresar más productos. El límite es 10.\n");
    }
    return contp;
}