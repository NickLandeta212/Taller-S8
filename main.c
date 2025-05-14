#include <stdio.h>
#include "funciones.h"
#include <string.h>
int main() {
    char productos[5][30];
    char ingredientes[10][30];
    float cantidades[10];
    int contProductos = 0;
    int contIngredientes = 0;
    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                contProductos = IngresarProductos(productos, contProductos);
                break;
            case 2:
                RegistrarIngredientes(ingredientes, cantidades, &contIngredientes);
                break;
            case 3:
                printf("Función para ingresar pedido aún no implementada.\n");
                break;
            case 4:
                printf("Función para calcular precio promedio aún no implementada.\n");
                break;
            case 5:
                printf("Función de búsqueda de producto aún no implementada.\n");
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }

        printf("\n");

    } while (opcion != 6);

    return 0;
}
