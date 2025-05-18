void RealizarPedido(char productos[5][30], float cantidadesPorProducto[5][10], char ingredientes[10][30], float stock[10],
                    float tiemposProduccion[5], int numProductos, int numIngredientes) {
    if (numIngredientes == 0 || numProductos == 0) {
        printf("No hay ingredientes o productos registrados para realizar un pedido.\n");
        return;
    }

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        // Muestra la tabla de ingredientes disponibles
        printf("\n--- Tabla de Ingredientes ---\n");
        printf("%-20s%-20s\n", "Ingrediente", "Stock Disponible");
        printf("------------------------------------------\n");
        for (int i = 0; i < numIngredientes; i++) {
            printf("%-20s%-20.2f\n", ingredientes[i], stock[i]);
        }

        // Muestra la tabla de productos y sus tiempos
        printf("\n--- Tabla de Productos ---\n");
        printf("%-15s", "Producto");
        for (int j = 0; j < numIngredientes; j++) {
            printf("%-10s", ingredientes[j]);
        }
        printf("%-15s\n", "Tiempo (min)");
        printf("--------------------------------------------------------------------------------\n");

        for (int i = 0; i < numProductos; i++) {
            printf("%-15s", productos[i]);
            for (int j = 0; j < numIngredientes; j++) {
                printf("%-10.2f", cantidadesPorProducto[i][j]);
            }
            printf("%-15.2f\n", tiemposProduccion[i]); 
        }

        // Selección del producto
        char nombreProducto[30];
        int productoIndex = -1;
        printf("\nIngrese el nombre del producto que desea pedir: ");
        fflush(stdin);
        fgets(nombreProducto, 30, stdin);
        int len = strlen(nombreProducto) - 1;
        if (nombreProducto[len] == '\n') nombreProducto[len] = '\0';

        for (int i = 0; i < numProductos; i++) {
            if (strcmp(nombreProducto, productos[i]) == 0) {
                productoIndex = i;
                break;
            }
        }

        if (productoIndex == -1) {
            printf("Producto no encontrado.\n");
            continue;
        }

        // Cantidad del producto a pedir
        int cantidadPedido;
        printf("Ingrese la cantidad de productos que desea: ");
        cantidadPedido = (int)validarIngreso();

        ValidarTiempoPedido(tiemposProduccion, productoIndex, &cantidadPedido);

        // Verificación del stock disponible
        int suficientes = 1;
        printf("\n--- Verificación de ingredientes ---\n");
        for (int j = 0; j < numIngredientes; j++) {
            float requerido = cantidadesPorProducto[productoIndex][j] * cantidadPedido;
            if (requerido > stock[j]) {
                printf("❌ Ingrediente insuficiente: '%s' | Disponible: %.2f | Requerido: %.2f\n", ingredientes[j], stock[j], requerido);
                suficientes = 0;
            }
        }

        // Si faltan ingredientes, pedir reabastecimiento o cancelar pedido
        if (!suficientes) {
            printf("\nIngredientes insuficientes para realizar el pedido.\n");
            char opcion;
            printf("¿Desea reabastecer el inventario? (s/n): ");
            fflush(stdin);
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                RellenarInventario(ingredientes, stock, numIngredientes);
                continue;
            } else {
                printf("Pedido cancelado.\n");
                break;
            }
        }

        // Confirmación del pedido
        char confirmar;
        printf("¿Desea confirmar el pedido de %d unidades de %s? (s/n): ", cantidadPedido, nombreProducto);
        fflush(stdin);
        scanf(" %c", &confirmar);

        if (confirmar == 's' || confirmar == 'S') {
            printf("\n--- Ingredientes descontados del inventario ---\n");
            for (int j = 0; j < numIngredientes; j++) {
                float requerido = cantidadesPorProducto[productoIndex][j] * cantidadPedido;
                if (requerido > 0) {
                    stock[j] -= requerido;
                    printf("✔ '%s' | Descontado: %.2f unidades | Restante: %.2f\n", ingredientes[j], requerido, stock[j]);
                }
            }
            printf("\nPedido confirmado y procesado con éxito.\n");
        } else {
            printf("Pedido cancelado por el usuario.\n");
        }

        printf("\n¿Desea realizar otro pedido? (s/n): ");
        fflush(stdin);
        scanf(" %c", &continuar);
    }
}
