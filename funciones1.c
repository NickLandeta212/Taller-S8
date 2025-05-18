#include <stdio.h>
#include <string.h>
#include <math.h>

float validarTiempo() {
    float tiempo;
    do {
        printf("Ingrese el tiempo estimado de producción (en minutos): ");
        tiempo = validarIngreso();
        
        if (tiempo < 10) {  // Ejemplo: Establecer un tiempo mínimo
            printf("El tiempo ingresado es muy corto. Ingrese un tiempo mayor.\n");
        }
    } while (tiempo < 10); // Si el tiempo es insuficiente, se solicita otro
    
    return tiempo;
}

void RegistrarTiempoProduccion(float *tiemposProduccion, int contp) {
    printf("Ingrese el tiempo estimado de producción (en segundos) para el producto %d: ", contp + 1);
    tiemposProduccion[contp] = validarIngreso();
}


void ValidarTiempoPedido(float *tiemposProduccion, int productoIndex, int *cantidadPedido) {
    float tiempoIngresado;
    
    printf("Ingrese el tiempo estimado para producir %d unidades del producto: ", *cantidadPedido);
    tiempoIngresado = validarIngreso();

    while (tiempoIngresado < (*cantidadPedido * tiemposProduccion[productoIndex])) {
        printf("El tiempo ingresado es insuficiente para producir %d unidades.\n", *cantidadPedido);
        printf("Opciones:\n");
        printf("1. Aumentar el tiempo de producción\n");
        printf("2. Disminuir la cantidad de productos\n");
        printf("Seleccione una opción: ");
        
        int opcion = (int)validarIngreso();
        if (opcion == 1) {
            printf("Ingrese un nuevo tiempo estimado: ");
            tiempoIngresado = validarIngreso();
        } else if (opcion == 2) {
            printf("Ingrese una nueva cantidad de productos: ");
            *cantidadPedido = (int)validarIngreso();
        } else {
            printf("Opción inválida.\n");
        }
    }
    
    printf("Tiempo de producción validado. Procediendo con el pedido.\n");
}



void mostrarTabla(char (*productos)[30], float (*cantidadesPorProducto)[10], char (*ingredientes)[30], float *stock, float *tiemposProduccion, int numProductos, int numIngredientes) {
    printf("\n%-20s%-20s%-20s%-20s\n", "Producto", "Ingrediente", "Stock Disponible", "Tiempo Producción");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < numProductos; i++) {
        for (int j = 0; j < numIngredientes; j++) {
            if (cantidadesPorProducto[i][j] > 0) { 
                printf("%-20s%-20s%-20.2f%-20.2f segundos\n", productos[i], ingredientes[j], stock[j], tiemposProduccion[i]);
            }
        }
    }
    printf("\n");
}



void RellenarInventario(char ingredientes[10][30], float *stock, int numIngredientes) {
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        printf("\n--- Inventario Actual ---\n");
        for (int i = 0; i < numIngredientes; i++) {
            printf("%d. %s - %.2f unidades\n", i + 1, ingredientes[i], stock[i]);
        }

        printf("\nIngrese el nombre del ingrediente que desea reabastecer: ");
        char nombre[30];
        fflush(stdin);
        fgets(nombre, 30, stdin);

        int len = strlen(nombre) - 1;
        if (nombre[len] == '\n') {
            nombre[len] = '\0';
        }

        int encontrado = -1;
        for (int i = 0; i < numIngredientes; i++) {
            if (strcmp(nombre, ingredientes[i]) == 0) {
                encontrado = i;
                break;
            }
        }

        if (encontrado != -1) {
            printf("Ingrese la cantidad a agregar para %s: ", ingredientes[encontrado]);
            float cantidad = validarIngreso();
            stock[encontrado] += cantidad;
            printf("Inventario actualizado: %s ahora tiene %.2f unidades.\n", ingredientes[encontrado], stock[encontrado]);
        } else {
            printf("Ingrediente no encontrado.\n");
        }

        printf("\n¿Desea agregar stock a otro ingrediente? (s/n): ");
        fflush(stdin);
        scanf(" %c", &continuar);
    }

    printf("Inventario actualizado correctamente.\n");
}



