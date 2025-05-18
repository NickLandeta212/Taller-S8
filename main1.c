#include <stdio.h>
#include <stdlib.h>

// Variables globales para definir límites dinámicamente
int maxIngredientes;
int maxProductos;

void configurarLimites() {
    printf("Ingrese el número máximo de ingredientes: ");
    maxIngredientes = (int) validarIngreso();
    
    printf("Ingrese el número máximo de productos: ");
    maxProductos = (int) validarIngreso();
}

int main() {
    configurarLimites(); // El usuario define los límites al inicio del programa

    // Ahora puedes usar 'maxIngredientes' y 'maxProductos' en lugar de constantes fijas
    char ingredientes[maxIngredientes][30];
    float cantidades[maxIngredientes];
    char nombres[maxProductos][30];
    float cantidadesPorProducto[maxProductos][maxIngredientes];
    float tiemposProduccion[maxProductos];

    int contIngredientes = 0, contp = 0;
    int opcion;

    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                RegistrarIngredientes(ingredientes, cantidades, &contIngredientes);
                break;
            case 2:
                contp = IngresarProductos(nombres, cantidadesPorProducto, ingredientes, tiemposProduccion, contIngredientes, contp);
                break;
            case 3:
                RealizarPedido(ingredientes, cantidades, contIngredientes, nombres, cantidadesPorProducto, tiemposProduccion, contp);
                break;
            case 4:
                mostrarTabla(nombres, cantidadesPorProducto, ingredientes, cantidades, tiemposProduccion, contp, contIngredientes);
                break;
            case 5:
                RellenarInventario(ingredientes, cantidades, contIngredientes);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida, intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}
