#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char productos[5][30];
    char ingredientes[10][30];
    float cantidades[10];
    float cantidadesPorProducto[5][10] = {0}; 
    int contProductos = 0;
    int contIngredientes = 0;
    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                contProductos = IngresarProductos(productos, cantidadesPorProducto, ingredientes, contIngredientes, contProductos);
                break;
            case 2:
                RegistrarIngredientes(ingredientes, cantidades, &contIngredientes);
                break;
            case 3:
                RealizarPedido(ingredientes, cantidades, contIngredientes);
                break;
            case 4:
                printf("Función de precio promedio aún no implementada.\n");
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
