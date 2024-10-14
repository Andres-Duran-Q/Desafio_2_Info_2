#include "termax.h"

int main() {
    // Crear un objeto Surtidor
    Surtidor surtidor1(1, 5); // Código 1, Modelo 5

    // Registrar ventas
    surtidor1.nueva_venta(20, 1, 2, 123, 200);  // Venta 1: 20 litros, categoría 1, pago con tarjeta, cliente 123, $500
    surtidor1.nueva_venta(15, 2, 1, 200, 200);  // Venta 2: 15 litros, categoría 2, pago en efectivo, cliente 456, $300

    // Imprimir información básica
    surtidor1.print_codigo_id();               // Imprime el código del surtidor
    surtidor1.print_modelo_maquina();          // Imprime el modelo del surtidor
    surtidor1.print_cantidad_ventas();         // Imprime la cantidad de ventas realizadas

    // Mostrar detalles de ventas
    surtidor1.print_ventas(0);                 // Imprime la primera venta
    surtidor1.print_ventas(1);                 // Imprime la segunda venta

    return 0;
}
