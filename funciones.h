float validarIngreso();
int menu();
void RegistrarIngredientes(char ingredientes[][30], float cantidades[10], int *contador);
int IngresarProductos(char nombres[][30], float (*cantidadesPorProducto)[10], char ingredientes[][30], int contIngredientes, int contp);
void RegistrarTiempoProduccion(char productos[][30], float *tiemposProduccion, int contp);
void ValidarTiempoPedido(float *tiemposProduccion, int productoIndex, int *cantidadPedido);
void RellenarInventario(char ingredientes[][30], float *stock, int numIngredientes);
void RealizarPedido(char productos[][30], float cantidadesPorProducto[][10], char ingredientes[][30], float stock[10],
                    float tiemposProduccion[5], int numProductos, int numIngredientes);
