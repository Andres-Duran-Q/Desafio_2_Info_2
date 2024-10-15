#include "Surtidor.h"

int main() {
    int opcion;
    bool surtidor_creado = false;
    Surtidor* surtidor1 = nullptr; // Puntero para el surtidor

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Crear surtidor\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            if (!surtidor_creado) {
                // Crear un objeto Surtidor
                surtidor1 = new Surtidor(1, "addq1234");
                surtidor_creado = true;
                std::cout << "\nSurtidor creado exitosamente.\n";

                // Registrar algunas ventas
                surtidor1->nueva_venta(20, "Regular", "Efectivo", 1117554456, 500);
                surtidor1->nueva_venta(15, "Premium", "TDebito", 40079781, 600);
                surtidor1->nueva_venta(15, "EcoExtra", "TCredito", 123456789, 800);

                // Imprimir información básica del surtidor
                surtidor1->print_codigo_id();
                surtidor1->print_modelo_maquina();
                surtidor1->print_ventas();
            } else {
                std::cout << "El surtidor ya ha sido creado.\n";
            }
        } else if (opcion == 0) {
            std::cout << "Saliendo del programa...\n";
            break;
        } else {
            std::cout << "Opcion invalida. Por favor, seleccione 1 o 0.\n";
        }
    }

    // Liberar memoria del surtidor si fue creado
    if (surtidor1 != nullptr) {
        delete surtidor1;
    }

    return 0;
}
