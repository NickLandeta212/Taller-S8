#include <stdio.h>
#include <string.h>
#include "funciones.h"  // Asegúrate de declarar tus funciones aquí

int main() {
    char ingredientes[10][30];
    float cantidades[10] = {0};
    float stock[10] = {0};
    int contadorIngredientes = 0;

    char productos[5][30];
    float cantidadesPorProducto[5][10] = {{0}};
    float tiemposProduccion[5] = {0};
    int contadorProductos = 0;

    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                RegistrarIngredientes(ingredientes, cantidades, &contadorIngredientes);
                for (int i = 0; i < contadorIngredientes; i++) {
                    stock[i] += cantidades[i];  // Actualiza el stock
                }
                break;

            case 2:
                contadorProductos = IngresarProductos(productos, cantidadesPorProducto, ingredientes, contadorIngredientes, contadorProductos);
                break;

            case 3:
                if (contadorProductos > 0) {
                    RegistrarTiempoProduccion(tiemposProduccion, contadorProductos - 1);
                } else {
                    printf("Primero debe registrar un producto.\n");
                }
                break;

            case 4:
                RealizarPedido(productos, cantidadesPorProducto, ingredientes, stock, tiemposProduccion, contadorProductos, contadorIngredientes);
                break;

            case 5:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != 5);

    return 0;
}
