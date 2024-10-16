#include <iostream>
#include "Estacion_servicio.h"
#include "Surtidor.h"

using namespace std;
// prueba surtidor
/*int main() {
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
                surtidor1->nueva_venta(20, 0, 1, 1117554456, 500);
                surtidor1->nueva_venta(15, 1, 2, 40079781, 600);
                surtidor1->nueva_venta(15, 2, 0, 123456789, 800);

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
}*/

// prueba estacion de servicio
/*
int main() {
    // Inicializa el generador de números aleatorios
    srand(time(0));

    // Crea un arreglo de ubicación GPS
    float ubicacion_gps[2] = {19.4326, -99.1332};

    // Crea una estación de servicio
    Estacion_servicio estacion("Estacion 1", 12345, "Juan Perez", 1, ubicacion_gps);

    int opcion;

    while (true) {
        // Muestra el menú de opciones
        cout << "\n--- Menu de Estacion de Servicio ---" << endl;
        cout << "1. Agregar surtidor" << endl;
        cout << "2. Eliminar surtidor" << endl;
        cout << "3. Activar surtidor" << endl;
        cout << "4. Desactivar surtidor" << endl;
        cout << "5. Simular venta" << endl;
        cout << "6. Reporte de ventas del tanque" << endl;
        cout << "7. Mostrar historico de transacciones" << endl;
        cout << "8. Mostrar informacion de surtidores" << endl; // Nueva opción
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        // Maneja la entrada del usuario
        switch (opcion) {
        case 1: {
            string modelo_maquina;
            cout << "Ingrese el modelo del surtidor: ";
            cin >> modelo_maquina;
            estacion.agregar_surtidor(modelo_maquina);
            break;
        }
        case 2: {
            int id_surtidor;
            cout << "Ingrese el surtidor a eliminar: ";
            cin >> id_surtidor;
            estacion.eliminar_surtidor(id_surtidor-1);
            break;
        }
        case 3: {
            int id_surtidor;
            cout << "Ingrese el surtidor a activar: ";
            cin >> id_surtidor;
            estacion.activar_surtidor(id_surtidor-1);
            break;
        }
        case 4: {
            int id_surtidor;
            cout << "Ingrese el surtidor a desactivar: ";
            cin >> id_surtidor;
            estacion.desactivar_surtidor(id_surtidor-1);
            break;
        }
        case 5: {
            uint32_t precio_combustible;
            uint16_t categoria_combustible;
            cout << "Ingrese el precio del combustible: ";
            cin >> precio_combustible;
            cout << "Ingrese la categoria de combustible (0, 1 o 2): ";
            cin >> categoria_combustible;

            // Verificar que la categoría esté dentro de los límites
            if (categoria_combustible >= 0 && categoria_combustible <= 2) {
                estacion.simular_venta(precio_combustible, categoria_combustible);
            } else {
                cout << "Categoria invalida. Debe ser 0, 1 o 2." << endl;
            }
            break;
        }
        case 6:
            estacion.reporte_ventas_tanque();
            break;
        case 7:
            estacion.historico_transacciones();
            break;
        case 8:
            estacion.mostrarInformacionSurtidores(); // Llamada a la nueva función
            break;
        case 0:
            cout << "Saliendo del programa." << endl;
            return 0;  // Sale del programa
        default:
            cout << "Opcion no valida, por favor elija de nuevo." << endl;
            break;
        }

        // Limpiar el buffer de entrada
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}*/
