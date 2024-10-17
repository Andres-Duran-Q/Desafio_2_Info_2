// ============================================================
// Librerias
// ============================================================
#include <iostream>
#include <string>
#include <stdexcept>  // Necesaria para lanzar y manejar excepciones estandar
#include "Red_nacional.h"  // Asegurate de que este archivo exista y esté correctamente implementado

using namespace std;


// ============================================================
// Funciones
// ============================================================

// Plantilla de función para validar que una opción está dentro de un rango específico
template <typename T>
bool OpcionValida(T valor, T max, T min) {
    return (valor >= min && valor <= max);
}

// Funcion para mostrar el menu principal del sistema
void mostrar_menu_principal() {
    cout << "\nEscoja una opcion:\n";
    cout << "0. Salir\n";
    cout << "1. Gestion de Red\n";
    cout << "2. Gestion de Estaciones de Servicio\n";
    cout << "3. Simulacion de ventas\n";
    cout << "Opcion: ";
}

// Funcion para mostrar el menu de gestion de la Red
void mostrar_menu_gestion_Red() {
    cout << "\nEscoja una opcion:\n";
    cout << "0. Salir\n";
    cout << "1. Agregar Estacion de Servicio\n";
    cout << "2. Eliminar Estaciones de Servicio\n";
    cout << "3. Calcular el monto total de las ventas en cada E/S del pais\n";
    cout << "4. Fijar los precios del combustible para toda la red\n";
    cout << "Opcion: ";
}

// Funcion para mostrar el menu de gestion de las estaciones de servicio
void mostrar_menu_estaciones_servicio() {
    cout << "\nEscoja una opcion:\n";
    cout << "0. Salir\n";
    cout << "1. Agregar Surtidor\n";
    cout << "2. Eliminar Surtidor\n";
    cout << "3. Activar Surtidor\n";
    cout << "4. Desactivar Surtidor\n";
    cout << "5. Consultar el historico de transacciones\n";
    cout << "6. Reportar la cantidad de litros vendida\n";
    cout << "Opcion: ";
}


void manejar_menu_gestion_Red() {
    uint16_t opcion = 0;
    bool validacion = false;
    bool entradaValida = false;  // Variable para controlar las entradas validas

    while (!validacion) {
        try {
            mostrar_menu_gestion_Red();
            cin >> opcion;

            // Verificar si la entrada es válida
            if (cin.fail()) {
                throw invalid_argument("Entrada no valida. Por favor ingrese un numero.");
            }

            // Validar que la opcion esté dentro del rango
            if (opcion > 4) {
                throw out_of_range("Opcion fuera de rango. Por favor ingrese un numero entre 0 y 4.");
            }

            validacion = true;  // Si la opción es correcta, salir del ciclo

            // Procesar la opción seleccionada
            switch (opcion) {
            case 0:
                cout << "Saliendo de gestion de Red..." << endl;
                break;
            case 1: {
                // Limpiar el buffer antes de usar getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string Nombre;
                string Gerente;
                unsigned short int Region;
                float Lat;
                float Long;

                // Obtener el nombre de la estación
                cout << "\nIngrese el Nombre de la Estacion: ";
                do {
                    getline(cin, Nombre);
                    if (Nombre.empty())
                        cout << "\nEl nombre no puede estar vacio. Intentelo de nuevo: ";
                } while (Nombre.empty());

                // Obtener el nombre del gerente
                cout << "\nIngrese el Nombre del Gerente: ";
                do {
                    getline(cin, Gerente);
                    if (Gerente.empty())
                        cout << "\nEl nombre no puede estar vacio. Intentelo de nuevo: ";
                } while (Gerente.empty());

                entradaValida = false;

                // Obtener la region
                while (!entradaValida) {
                    cout << "\nIngrese la Region de la Estacion:\n1. Norte\n2. Centro\n3. Sur\n";
                    cin >> Region;
                    entradaValida = OpcionValida<short unsigned int>(Region, 3, 1);
                }

                entradaValida = false;

                // Obtener la latitud
                while (!entradaValida) {
                    cout << "\nIngrese la Latitud en grados de la estacion (valor entre -180 y 180)\n";
                    cin >> Lat;
                    entradaValida = OpcionValida<float>(Lat, 180, -180);
                }

                entradaValida = false;

                // Obtener la longitud
                while (!entradaValida) {
                    cout << "\nIngrese la Longitud en grados de la estacion (valor entre -180 y 180)\n";
                    cin >> Long;
                    entradaValida = OpcionValida<float>(Long, 180, -180);
                }

                entradaValida = false;

                // Mostrar los datos ingresados
                cout << "Estos son los datos de la estacion a agregar:\n"
                     << "\nNombre: " << Nombre << endl
                     << "Gerente: " << Gerente << endl;

                cout << "Region: ";
                switch (Region) {
                case 1:
                    cout << "Norte\n";
                    break;
                case 2:
                    cout << "Centro\n";
                    break;
                case 3:
                    cout << "Sur\n";
                    break;
                }

                cout << "\nCoordenadas:\n"
                     << "\tLatitud: " << Lat << endl
                     << "\tLongitud: " << Long << endl;

                short unsigned int Agregar;

                // Confirmación de agregar la estación
                while (!entradaValida) {
                    cout << "\nEsta seguro que desea agregar esta estacion?\n1. Si, Agregar\n2. No, Cancelar\n";
                    cin >> Agregar;
                    entradaValida = OpcionValida<short unsigned int>(Agregar, 2, 1);
                }

                // Dependiendo de la confirmación, mostrar el resultado
                if (Agregar == 1) {
                    cout << "Agregando la estacion..." << endl;
                } else {
                    cout << "Cancelando la operacion..." << endl;
                }
                break;  // Importante: Salir del `switch` después de procesar la opción
            }

            case 2:
                cout << "Eliminando Estacion de Servicio" << endl;
                break;
            case 3:
                cout << "Calculando el monto total de las ventas" << endl;
                break;
            case 4:
                cout << "Fijando los precios del combustible" << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
            }

        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
        }
    }
}

void manejar_menu_estaciones_servicio() {
    uint16_t opcion = 0;
    bool validacion = false;

    while (!validacion) {
        try {
            mostrar_menu_estaciones_servicio();
            cin >> opcion;

            // Verificar si la entrada es válida
            if (cin.fail()) {
                throw invalid_argument("Entrada no valida. Por favor ingrese un numero.");
            }

            // Validar que la opcion esté dentro del rango
            if (opcion > 6) {
                throw out_of_range("Opcion fuera de rango. Por favor ingrese un numero entre 0 y 6.");
            }

            validacion = true;  // Si la opción es correcta, salir del ciclo

            // Procesar la opción seleccionada
            switch (opcion) {
            case 0:
                cout << "Saliendo de gestion de Estaciones de Servicio..." << endl;
                break;
            case 1:
                cout << "Agregando Surtidor" << endl;
                break;
            case 2:
                cout << "Eliminando Surtidor" << endl;
                break;
            case 3:
                cout << "Activando Surtidor" << endl;
                break;
            case 4:
                cout << "Desactivando Surtidor" << endl;
                break;
            case 5:
                cout << "Consultando el historico de transacciones" << endl;
                break;
            case 6:
                cout << "Reportando la cantidad de litros vendida" << endl;
                break;
            default:
                // No deberia ocurrir, pero por seguridad
                cout << "Opcion invalida." << endl;
                break;
            }

        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
        }
    }
}

// ============================================================
// Main
// ============================================================

int main() {
    // Instancia de la clase Red_nacional (debe estar definida en el archivo "Red_nacional.h")
    Red_nacional Red;

    // Variables para controlar el flujo del programa
    bool salir = false;              // Bandera para salir del programa
    uint16_t opcion = 0;             // Almacena la opcion seleccionada por el usuario

    // Titulo del sistema
    cout << "=================== Sistema de la red TerMax ===================" << endl;

    // Ciclo principal del menu
    do {
        bool validacion = false;  // Bandera para validar que la entrada sea correcta

        // Mostrar el menu y solicitar entrada hasta que sea valida
        while (!validacion) {
            try {
                mostrar_menu_principal();  // Llamamos a la funcion que muestra el menu
                cin >> opcion;  // Capturamos la opcion ingresada por el usuario

                // Verificar si la entrada fue exitosa
                if (cin.fail()) {  // Si la entrada no es un numero valido
                    throw invalid_argument("Entrada no valida. Por favor ingrese un numero.");
                }

                // Validar si la opcion esta dentro del rango permitido
                if (opcion > 3) {
                    throw out_of_range("Opcion fuera de rango. Por favor ingrese un numero entre 0 y 3.");
                }

                // Si todo es correcto, marcar la validacion como exitosa
                validacion = true;

            } catch (const invalid_argument& e) {  // Capturar la excepcion por entrada no numerica
                cout << e.what() << endl;
                cin.clear();  // Limpiar el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            } catch (const out_of_range& e) {  // Capturar excepciones por valores fuera de rango
                cout << e.what() << endl;
            }
        }

        // Procesar la opcion seleccionada
        switch (opcion) {
        case 0:
            salir = true;
            cout << "Saliendo del sistema..." << endl;
            break;

        case 1:
            manejar_menu_gestion_Red();
            break;

        case 2:
            manejar_menu_estaciones_servicio();
            break;

        case 3:
            cout << "Simulacion de ventas" << endl;
            break;

        default:
            cout << "Opcion invalida. Esto no deberia ocurrir." << endl;
            break;
        }

    } while (!salir);  // Repetir hasta que el usuario elija salir

    return 0;  // Fin del programa
}
