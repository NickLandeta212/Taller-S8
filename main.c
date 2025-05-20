#include <stdio.h>
#include "funciones.h"

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
                    stock[i] = cantidades[i]; // Inicializa el stock con las cantidades ingresadas
                }
                break;
            case 2:
                contadorProductos = IngresarProductos(productos, cantidadesPorProducto, ingredientes, contadorIngredientes, contadorProductos);
                break;
            case 3:
                RegistrarTiempoProduccion(productos, tiemposProduccion, contadorProductos);
                break;
            case 4:
                RealizarPedido(productos, cantidadesPorProducto, ingredientes, stock, tiemposProduccion, contadorProductos, contadorIngredientes);
                break;
            case 5:
                EditarProductoOIngrediente(ingredientes, cantidades, contadorIngredientes, productos, cantidadesPorProducto, contadorProductos);
                break;
            case 6:
            contadorProductos = EliminarProducto(productos, cantidadesPorProducto, tiemposProduccion, contadorProductos);
            break;
            case 7:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}

