float validarIngreso();
int menu();
void RegistrarIngredientes(char ingredientes[][30], float cantidades[10], int *contador);
int IngresarProductos(char nombres[][30], float (*cantidadesPorProducto)[10], char ingredientes[][30], int contIngredientes, int contp);
void RealizarPedido(char ingredientes[10][30], float cantidades[10], int contador);