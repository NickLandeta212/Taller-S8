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
    printf("1. Ingrese los ingredientes y su cantidad\n");
    printf("2. Registrar producto\n");
    printf("3. Ingrese el pedido\n");
    printf("4. Precio promedio de todos los productos\n");
    printf("5. Busqueda de producto\n");
    printf("6. Salir\n");
    printf(">> ");
    opc=validarIngreso();
    return opc;
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
        printf("No se pueden ingresar mas ingredientes. Limite alcanzado.\n");
    }
}
int IngresarProductos(char nombres[5][30], float (*cantidadesPorProducto)[10], char ingredientes[10][30], int contIngredientes, int contp) {
    if (contp < 5) {
        printf("Ingrese el nombre del producto %d: ", contp + 1);
        fflush(stdin);
        fgets(nombres[contp], 30, stdin);

        // Eliminar salto de línea
        int len = strlen(nombres[contp]) - 1;
        if (nombres[contp][len] == '\n') {
            nombres[contp][len] = '\0';
        }

        printf("¿Cuántos ingredientes necesita '%s'? ", nombres[contp]);
        int numIng = (int)validarIngreso();

        for (int i = 0; i < numIng; i++) {
            int encontrado = -1;
            char nombreIng[30];

            // Repetir hasta que se ingrese un ingrediente válido
            while (encontrado == -1) {
                printf("Ingrese el nombre del ingrediente %d: ", i + 1);
                fflush(stdin);
                fgets(nombreIng, 30, stdin);
                int lenIng = strlen(nombreIng) - 1;
                if (nombreIng[lenIng] == '\n') nombreIng[lenIng] = '\0';

                for (int j = 0; j < contIngredientes; j++) {
                    if (strcmp(nombreIng, ingredientes[j]) == 0) {
                        encontrado = j;
                        break;
                    }
                }

                if (encontrado == -1) {
                    printf("Ingrediente '%s' no encontrado. Debe ingresar un ingrediente ya registrado.\n", nombreIng);
                }
            }

            printf("Ingrese la cantidad necesaria de %s: ", nombreIng);
            float cantidad = validarIngreso();
            *(*(cantidadesPorProducto + contp) + encontrado) = cantidad;
        }

        contp++;
    } else {
        printf("No se pueden ingresar más productos. El límite es 5.\n");
    }

    return contp;
}

void RealizarPedido(char ingredientes[10][30], float cantidades[10], int contador) {
    if (contador == 0) {
        printf("No hay ingredientes registrados para realizar un pedido.\n");
        return;
    }

    printf("\n--- Ingredientes disponibles ---\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s - %.2f unidades\n", i + 1, ingredientes[i], cantidades[i]);
    }

    char nombre[30];
    float cantidadSolicitada;
    char continuar;

    do {
        printf("\nIngrese el nombre del ingrediente que desea usar: ");
        fflush(stdin);
        fgets(nombre, 30, stdin);
        int len = strlen(nombre) - 1;
        if (nombre[len] == '\n') {
            nombre[len] = '\0';
        }

        int encontrado = 0;
        for (int i = 0; i < contador; i++) {
            if (strcmp(nombre, ingredientes[i]) == 0) {
                encontrado = 1;
                printf("Ingrese la cantidad que desea usar de %s: ", nombre);
                cantidadSolicitada = validarIngreso();

                if (cantidadSolicitada <= cantidades[i]) {
                    cantidades[i] -= cantidadSolicitada;
                    printf("Pedido realizado: %.2f unidades de %s\n", cantidadSolicitada, nombre);
                } else {
                    printf("No hay suficiente cantidad disponible. Solo hay %.2f unidades.\n", cantidades[i]);
                }
                break;
            }
        }

        if (!encontrado) {
            printf("Ingrediente no encontrado.\n");
        }

        printf("¿Desea pedir otro ingrediente? (s/n): ");
        fflush(stdin);
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');
}

