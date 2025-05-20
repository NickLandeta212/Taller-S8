#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char ingredientes[10][30];
    float cantidades[10];
    int contIngredientes = 0;

    char nombres[5][30];
    float cantidadesPorProducto[5][10] = {0};
    int contp = 0;

    float tiemposProduccion[5] = {0};
    float stock[10] = {0};

    int opcion;

    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                RegistrarIngredientes(ingredientes, cantidades, &contIngredientes);
                break;
            case 2:
                contp = IngresarProductos(nombres, cantidadesPorProducto, ingredientes, contIngredientes, contp);
                break;
            case 3:
                RegistrarTiempoProduccion(nombres, tiemposProduccion, contp);
                break;
            case 4:
                RealizarPedido(nombres, cantidadesPorProducto, ingredientes, stock, tiemposProduccion, contp, contIngredientes);
                break;
            case 5:
                EditarProducto(nombres, cantidadesPorProducto, contp);
                break;
            case 6:
                EliminarProducto(nombres, cantidadesPorProducto, &contp);
                break;
            case 7:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 7);

    return 0;
}
