#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char ingredientes[10][30];
    float stock[10] = {0};
    int contIngredientes = 0;

    char productos[5][30];
    float cantidadesPorProducto[5][10] = {0};
    float tiemposProduccion[5] = {0};
    int contProductos = 0;

    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                RegistrarIngredientes(ingredientes, stock, &contIngredientes);
                break;

            case 2:
                contProductos = IngresarProductos(productos, cantidadesPorProducto, ingredientes, contIngredientes, contProductos);
                break;

            case 3:
                if (contProductos > 0) {
                    RegistrarTiempoProduccion(tiemposProduccion, contProductos - 1);
                } else {
                    printf("Debe registrar al menos un producto antes de asignar tiempo de producción.\n");
                }
                break;

            case 4:
                RealizarPedido(productos, cantidadesPorProducto, ingredientes, stock, tiemposProduccion, contProductos, contIngredientes);
                break;

            case 5:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }

    } while (opcion != 5);

    return 0;
}
