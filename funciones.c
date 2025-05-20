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
     while (getchar() != '\n'); 
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
    printf("3. Ingrese tiempo estimado por producto\n");
    printf("4. Ingrese el pedido\n");
    printf("5. Editar nombre del producto y cantidades\n");
    printf("6. Eliminacion de productos\n");
    printf("7. Salir\n");
    printf(">> ");
    opc=validarIngreso();
    return opc;
}

void RegistrarIngredientes(char ingredientes[10][30], float cantidades[10], int *contador) {
    if (*contador < 10) {
        printf("Ingrese el nombre del ingrediente %d: ", *contador + 1);
        fflush(stdin);
        fgets(ingredientes[*contador], 30, stdin);
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
    if (contp >= 5) {
        printf("No se pueden ingresar mas productos. El limite es 5.\n");
        return contp;
    }

    printf("Ingrese el nombre del producto %d: ", contp + 1);
    fflush(stdin);
    fgets(nombres[contp], 30, stdin);

    int len = strlen(nombres[contp]) - 1;
    if (nombres[contp][len] == '\n') {
        nombres[contp][len] = '\0';
    }

    printf("Cuantos ingredientes necesita '%s'? ", nombres[contp]);
    int numIng = (int)validarIngreso();

    for (int i = 0; i < numIng; i++) {
        int encontrado = -1;
        char nombreIng[30];

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
        cantidadesPorProducto[contp][encontrado] = cantidad;
    }

    return contp + 1;
}

void RegistrarTiempoProduccion(char productos[5][30], float *tiemposProduccion, int contp) {
    if (contp == 0) {
        printf("No hay productos registrados aun.\n");
        return;
    }

    printf("\n--- Productos Registrados ---\n");
    for (int i = 0; i < contp; i++) {
        printf("%d. %s\n", i + 1, productos[i]);
    }

    int seleccion;
    printf("Seleccione el numero del producto al que desea asignar tiempo de produccion: ");
    seleccion = (int)validarIngreso();

    if (seleccion < 1 || seleccion > contp) {
        printf("Seleccion invalida.\n");
        return;
    }

    int index = seleccion - 1;
    float tiempoMin;

    do {
        printf("Ingrese el tiempo estimado de produccion (en minutos) para '%s': ", productos[index]);
        tiempoMin = validarIngreso();

        if (tiempoMin < 0.1) {
            printf("El tiempo ingresado es muy corto. Ingrese un tiempo mayor a 0.1 minutos.\n");
        }
    } while (tiempoMin < 0.1);

    tiemposProduccion[index] = tiempoMin; 
    printf("Tiempo registrado correctamente para '%s' (%.2f minutos).\n", productos[index], tiempoMin);
}

void RellenarInventario(char ingredientes[10][30], float *stock, int numIngredientes) {
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        printf("\n--- Inventario Actual ---\n");
        for (int i = 0; i < numIngredientes; i++) {
            printf("%d. %s - %.2f unidades\n", i + 1, ingredientes[i], stock[i]);
        }

        int seleccion;
        printf("\nSeleccione el numero del ingrediente que desea reabastecer: ");
        seleccion = (int)validarIngreso();

        if (seleccion < 1 || seleccion > numIngredientes) {
            printf("Seleccion invalida. Intente nuevamente.\n");
        } else {
            int index = seleccion - 1;
            printf("Ingrese la cantidad a agregar para %s: ", ingredientes[index]);
            float cantidad = validarIngreso();
            stock[index] += cantidad;
            printf("Inventario actualizado: %s ahora tiene %.2f unidades.\n", ingredientes[index], stock[index]);
        }

        printf("\nDesea agregar stock a otro ingrediente? (s/n): ");
        fflush(stdin);
        scanf(" %c", &continuar);
    }

    printf("Inventario actualizado correctamente.\n");
}

void ValidarTiempoPedido(float *tiemposProduccion, int productoIndex, int *cantidadPedido) {
    float tiempoIngresado;
    
    printf("Ingrese el tiempo estimado para producir %d unidades del producto: ", *cantidadPedido);
    tiempoIngresado = validarIngreso();

    while (tiempoIngresado < (*cantidadPedido * tiemposProduccion[productoIndex])) {
        printf("El tiempo ingresado es insuficiente para producir %d unidades.\n", *cantidadPedido);
        printf("Opciones:\n");
        printf("1. Aumentar el tiempo de produccion\n");
        printf("2. Disminuir la cantidad de productos\n");
        printf("Seleccione una opcion: ");
        
        int opcion = (int)validarIngreso();
        if (opcion == 1) {
            printf("Ingrese un nuevo tiempo estimado: ");
            tiempoIngresado = validarIngreso();
        } else if (opcion == 2) {
            printf("Ingrese una nueva cantidad de productos: ");
            *cantidadPedido = (int)validarIngreso();
        } else {
            printf("Opción invalida.\n");
        }
    }
    
    printf("Tiempo de produccion validado. Procediendo con el pedido.\n");
}
void RealizarPedido(char productos[5][30], float cantidadesPorProducto[5][10], char ingredientes[10][30], float stock[10],
                    float tiemposProduccion[5], int numProductos, int numIngredientes) {
    if (numIngredientes == 0 || numProductos == 0) {
        printf("No hay ingredientes o productos registrados para realizar un pedido.\n");
        return;
    }

    char nombreProducto[30];
    int productoIndex = -1;
    printf("\nIngrese el nombre del producto que desea pedir: ");
    fflush(stdin);
    fgets(nombreProducto, 30, stdin);
    int len = strlen(nombreProducto) - 1;
    if (nombreProducto[len] == '\n') {
        nombreProducto[len] = '\0';
    }

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombreProducto, productos[i]) == 0) {
            productoIndex = i;
            break;
        }
    }

    if (productoIndex == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    int cantidadPedido;
    printf("Ingrese la cantidad de productos que desea: ");
    cantidadPedido = (int) validarIngreso();

    ValidarTiempoPedido(tiemposProduccion, productoIndex, &cantidadPedido);
    int suficientes = 1;
    printf("\n--- Verificacion de ingredientes ---\n");
    for (int j = 0; j < numIngredientes; j++) {
        float requerido = cantidadesPorProducto[productoIndex][j] * cantidadPedido;
        if (requerido > stock[j]) {
            printf(" Ingrediente insuficiente: '%s' | Disponible: %.2f | Requerido: %.2f\n", ingredientes[j], stock[j], requerido);
            suficientes = 0;
        }
    }
    while (!suficientes) {
        printf("\nIngredientes insuficientes para realizar el pedido.\n");
        printf("Opciones:\n");
        printf("1. Modificar la cantidad de productos a pedir\n");
        printf("2. Reabastecer el inventario\n");
        printf("Seleccione una opción: ");
        
        int opcion = (int) validarIngreso();

        if (opcion == 1) {
            printf("Ingrese una nueva cantidad de productos: ");
            cantidadPedido = (int) validarIngreso();

     
            suficientes = 1;
            printf("\n--- Verificacion actualizada de ingredientes ---\n");
            for (int j = 0; j < numIngredientes; j++) {
                float requerido = cantidadesPorProducto[productoIndex][j] * cantidadPedido;
                if (requerido > stock[j]) {
                    printf(" Ingrediente insuficiente: '%s' | Disponible: %.2f | Requerido: %.2f\n", ingredientes[j], stock[j], requerido);
                    suficientes = 0;
                }
            }
        } else if (opcion == 2) {
            RellenarInventario(ingredientes, stock, numIngredientes);
            suficientes = 1;
        } else {
            printf("Opcion inválida. Intente nuevamente.\n");
        }
    }

    char confirmar;
    printf("Desea confirmar el pedido de %d unidades de %s? (s/n): ", cantidadPedido, nombreProducto);
    fflush(stdin);
    scanf(" %c", &confirmar);

    if (confirmar == 's' || confirmar == 'S') {
        printf("\n--- Ingredientes descontados del inventario ---\n");
        for (int j = 0; j < numIngredientes; j++) {
            float requerido = cantidadesPorProducto[productoIndex][j] * cantidadPedido;
            if (requerido > 0) {
                stock[j] -= requerido;
                printf(" '%s' | Descontado: %.2f unidades | Restante: %.2f\n", ingredientes[j], requerido, stock[j]);
            }
        }
        printf("\nPedido confirmado y procesado con exito.\n");
    } else {
        printf("Pedido cancelado por el usuario.\n");
    }
}

void EditarProducto(char nombres[5][30], float cantidadesPorProducto[5][10], int contp) {
    if (contp == 0) {
        printf("No hay productos registrados aun.\n");
        return;
    }

    printf("\n--- Productos Registrados ---\n");
    for (int i = 0; i < contp; i++) {
        printf("%d. %s\n", i + 1, nombres[i]);
    }

    int seleccion;
    printf("Seleccione el numero del producto que desea editar: ");
    seleccion = (int)validarIngreso();

    if (seleccion < 1 || seleccion > contp) {
        printf("Seleccion invalida.\n");
        return;
    }

    int index = seleccion - 1;
    printf("Ingrese el nuevo nombre del producto: ");
    fflush(stdin);
    fgets(nombres[index], 30, stdin);
    int len = strlen(nombres[index]) - 1;
    if (nombres[index][len] == '\n') {
        nombres[index][len] = '\0';
    }

    printf("Ingrese la nueva cantidad de ingredientes para el producto: ");
    int numIng = (int)validarIngreso();

    for (int i = 0; i < 10; i++) {
        cantidadesPorProducto[index][i] = 0; // Reiniciar cantidades
    }

    for (int i = 0; i < numIng; i++) {
        printf("Ingrese la nueva cantidad del ingrediente %d: ", i + 1);
        cantidadesPorProducto[index][i] = validarIngreso();
    }

    printf("Producto editado correctamente.\n");
}
void EliminarProducto(char nombres[5][30], float cantidadesPorProducto[5][10], int *contp) {
    if (*contp == 0) {
        printf("No hay productos registrados aun.\n");
        return;
    }

    printf("\n--- Productos Registrados ---\n");
    for (int i = 0; i < *contp; i++) {
        printf("%d. %s\n", i + 1, nombres[i]);
    }

    int seleccion;
    printf("Seleccione el numero del producto que desea eliminar: ");
    seleccion = (int)validarIngreso();

    if (seleccion < 1 || seleccion > *contp) {
        printf("Seleccion invalida.\n");
        return;
    }

    int index = seleccion - 1;
    for (int i = index; i < *contp - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        for (int j = 0; j < 10; j++) {
            cantidadesPorProducto[i][j] = cantidadesPorProducto[i + 1][j];
        }
    }

    (*contp)--;
    printf("Producto eliminado correctamente.\n");
}
