// ============================================================
// Librerias
// ============================================================
#include <iostream>
#include <stdexcept>  // Necesaria para lanzar y manejar excepciones estandar
#include "Red_nacional.h"  // Asegurate de que este archivo exista y esté correctamente implementado
#include "Funciones_menu.h"
using namespace std;

// ============================================================
// Funciones para el menu
// ============================================================
void mostrar_menu_principal();
void mostrar_menu_gestion_Red();
void mostrar_menu_estaciones_servicio();

void manejar_menu_gestion_Red(Red_nacional &TerMax);
void manejar_menu_estaciones_servicio(Estacion_servicio* estacion_actual);

// ============================================================
// Main
// ============================================================

int main() {
    // Instancia de la clase Red_nacional (debe estar definida en el archivo "Red_nacional.h")
    Red_nacional TerMax;

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
            manejar_menu_gestion_Red(TerMax);
            break;

        case 2: {
            if (TerMax.obtener_numero_estaciones() == 0) {
                cout << "\nNo hay estaciones creadas, no se puede acceder a estas opciones\n";
            } else {
                cout << endl << "Estaciones disponibles: " << endl;
                uint16_t Est = -1;

                // Mostrar estaciones disponibles
                for (uint16_t i = 0; i < TerMax.obtener_numero_estaciones(); i++) {
                    cout << i + 1 << ". " << TerMax.obtener_estacion(i)->obtener_nombre()
                    << " (" << TerMax.obtener_estacion(i)->obtener_codigo() << ')' << endl;
                }

                // Validar la entrada del usuario
                while (true) {
                    cout << "\nIngrese el numero que corresponde a la estacion a la que desea acceder:" << endl;
                    cin >> Est;

                    if (cin.fail() || Est < 1 || Est > TerMax.obtener_numero_estaciones()) {
                        cin.clear(); // Limpia el estado de error de cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la entrada
                        cout << "Entrada invalida. Intente nuevamente.\n";
                    } else {
                        break; // Entrada válida
                    }
                }

                // Acceder al menú de la estación seleccionada
                do {
                    Estacion_servicio* estacion_actual = TerMax.obtener_estacion(Est - 1);
                    manejar_menu_estaciones_servicio(estacion_actual);
                    break;
                } while (false);
            }
            break;
        }


        case 3: {
            if (TerMax.obtener_numero_estaciones() == 0) {
                cout << endl << "No se puede simular una venta ya que no hay estaciones creadas." << endl;
            } else {
                uint16_t estacion_simular = -1;

                // Mostrar la lista de estaciones disponibles
                cout << endl << "Estaciones Disponibles:" << endl;
                for (uint16_t i = 0; i < TerMax.obtener_numero_estaciones(); i++) {
                    cout << i + 1 << ". " << TerMax.obtener_estacion(i)->obtener_nombre() << " (" << TerMax.obtener_estacion(i)->obtener_codigo() << ')' << endl;
                }

                // Solicitar el número de la estación y validar la entrada
                do {
                    cout << "\nIngrese el numero que corresponde a la estacion a la que desea acceder:" << endl;
                    cin >> estacion_simular;

                    // Validar que la opción esté dentro del rango permitido
                    if (estacion_simular < 1 || estacion_simular > TerMax.obtener_numero_estaciones()) {
                        cout << "Opcion invalida. Intentelo de nuevo." << endl;
                    }

                } while (estacion_simular < 1 || estacion_simular > TerMax.obtener_numero_estaciones());

                // Obtener la estación seleccionada
                Estacion_servicio* estacion_actual = TerMax.obtener_estacion(estacion_simular - 1);

                // Verificar si hay surtidores en la estación
                if (estacion_actual->obtener_numero_surtidores() == 0) {
                    cout << endl << "No se puede simular una venta ya que no hay surtidores en esta estacion." << endl;
                } else {
                    // Simular una venta aleatoria de uno de los tres tipos de combustible
                    uint16_t categoria_combustible = rand() % 3;
                    estacion_actual->simular_venta(TerMax.obtener_precio(estacion_actual->obtener_region(), categoria_combustible), categoria_combustible);
                }
            }
            break;  // Salir del case
        }


        default:
            cout << "Opcion invalida. Esto no deberia ocurrir." << endl;
            break;
        }

    } while (!salir);

    return 0;  // Fin del programa
}

