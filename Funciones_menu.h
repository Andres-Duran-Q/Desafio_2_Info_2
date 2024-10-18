#ifndef FUNCIONES_MENU_H
#define FUNCIONES_MENU_H

#include <iostream>
#include <stdexcept>
#include "Red_nacional.h"

// ============================================================
// Funcion para mostrar el menu principal del sistema
// ============================================================

void mostrar_menu_principal() {
    cout << "\nEscoja una opcion:\n";
    cout << "0. Salir\n";
    cout << "1. Gestion de Red\n";
    cout << "2. Gestion de Estaciones de Servicio\n";
    cout << "3. Simulacion de ventas\n";
    cout << "Opcion: ";
}

// ============================================================
// Funcion para mostrar el menu de gestion de la Red
// ============================================================

void mostrar_menu_gestion_Red() {
    cout << "\nEscoja una opcion:\n";
    cout << "0. Salir\n";
    cout << "1. Agregar Estacion de Servicio\n";
    cout << "2. Eliminar Estaciones de Servicio\n";
    cout << "3. Calcular el monto total de las ventas en cada E/S del pais\n";
    cout << "4. Fijar los precios del combustible para toda la red\n";
    cout << "Opcion: ";
}

// ============================================================
// Funcion para mostrar el menu de gestion de las estaciones de servicio
// ============================================================

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

// ============================================================
// Función para manejar la gestión y flujo del menú de la Red nacional
// ============================================================
void manejar_menu_gestion_Red(Red_nacional& TerMax) {
    uint16_t opcion = 0;
    bool validacion = false;
    bool validar_entrada = false;

    while (!validacion) {
        try {
            mostrar_menu_gestion_Red();
            cin >> opcion;

            // Verificar si la entrada es válida
            if (cin.fail()) {
                throw invalid_argument("Entrada no valida. Por favor ingrese un numero.");
            }

            // Validar que la opción esté dentro del rango
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer

                string Nombre;
                string Gerente;
                uint16_t Region;
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

                // Obtener la región
                do {
                    cout << "\nIngrese la Region de la Estacion:\n1. Norte\n2. Centro\n3. Sur\n";
                    cin >> Region;
                    if (cin.fail() || Region < 1 || Region > 3) {
                        cout << "Region no valida. Por favor ingrese un valor entre 1 y 3.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                        validar_entrada = true;
                    }
                } while (!validar_entrada);

                validar_entrada = false;

                // Obtener la latitud
                do {
                    cout << "\nIngrese la Latitud en grados de la estacion (valor entre -4 y 15)\n";
                    cin >> Lat;
                    if (cin.fail() || Lat < -4 || Lat > 15) {
                        cout << "Latitud no valida. Por favor ingrese un valor entre -4 y 15.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                        validar_entrada = true;
                    }
                } while (!validar_entrada);

                validar_entrada = false;

                // Obtener la longitud
                do {
                    cout << "\nIngrese la Longitud en grados de la estacion (valor entre -77 y -66)\n";
                    cin >> Long;
                    if (cin.fail() || Long < -77 || Long > -66) {
                        cout << "Longitud no valida. Por favor ingrese un valor entre -77 y -66.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                        validar_entrada = true;
                    }
                } while (!validar_entrada);

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

                TerMax.agregar_estacion(Nombre, Gerente, Region - 1, Lat, Long);
                Estacion_servicio* estacion_activa = TerMax.obtener_estacion(TerMax.obtener_numero_estaciones() - 1);
                cout << "\nLa estacion debe poseer al menos 2 surtidores." << endl;


                string Modelo;
                // Limpiar el buffer antes de getline()
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (uint16_t i = 0; i < 2; i++) {
                    validar_entrada = false;
                    cout << "\nIngrese el modelo del surtidor:";
                    while (!validar_entrada) {
                        getline(cin, Modelo);
                        if (Modelo.empty()) {
                            cout << "\nEl modelo no puede estar vacio. Intentelo de nuevo\n";
                        } else {
                            validar_entrada = true;
                        }
                    }
                    estacion_activa->agregar_surtidor(Modelo);
                    cout << "Surtidor " << i + 1 << " agregado con modelo -> " << Modelo << endl;
                }

                break;
            }

            case 2:{

                validar_entrada = false;
                if (TerMax.obtener_numero_estaciones() == 0) {
                    cout << endl << "No hay estaciones creadas.\n";
                } else {
                    cout << endl << "Estaciones disponibles: " << endl;
                    uint16_t Eliminar;

                    for (uint16_t i = 0; i < TerMax.obtener_numero_estaciones(); i++) {
                        cout << i + 1 << ". Nombre:" << TerMax.obtener_estacion(i)->obtener_nombre() << " id(" << TerMax.obtener_estacion(i)->obtener_codigo() << ')' << endl;
                    }
                    cout << "0. " << "No borrar ninguna" << endl;

                    // Bucle para validar la entrada del usuario
                    while (!validar_entrada) {
                        cout << "Ingrese el numero correspondiente a la estacion que desea eliminar" << endl;
                        cin >> Eliminar;

                        if (cin.fail()) {
                            // Si la entrada no es válida, limpiar el flujo y mostrar mensaje de error
                            cin.clear(); // Limpiar el estado de error del flujo
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada no válida
                            cout << "Entrada invalida, por favor ingrese un número.\n";
                        } else if (Eliminar >= 0 && Eliminar <= TerMax.obtener_numero_estaciones()) {
                            // Si el número está en el rango válido, la entrada es válida
                            validar_entrada = true;
                        } else {
                            // Si el número está fuera del rango
                            cout << "Numero fuera de rango. Por favor, ingrese un valor entre 0 y " << TerMax.obtener_numero_estaciones() << "." << endl;
                        }
                    }

                    if (Eliminar > 0) {
                        TerMax.eliminar_estacion(Eliminar - 1); // Eliminar la estación seleccionada
                    }
                }
                validar_entrada = false;

                break;
            }

            case 3:{
                TerMax.ventas_todas_estaciones_pais();
                break;
            }

            case 4: {
                uint16_t Elejir_region = 0;
                uint16_t tipo_combustible = 0;
                uint16_t Elejir_precio = 0;

                // Mostrar precios actuales
                cout << endl << "Precios Actuales:" << endl
                     << "\tRegular\tPremium\tEcoExtra\n";
                const string regiones[] = {"Norte", "Centro", "Sur"};
                for (uint16_t i = 0; i < 3; i++) {
                    cout << regiones[i] << "\t";
                    for (uint16_t j = 0; j < 3; j++) {
                        cout << TerMax.obtener_precio(i, j) << '\t';
                    }
                    cout << endl;
                }

                // Validar entrada de region
                do {
                    cout << "\nEn que region quiere cambiar el precio?\n1. Norte\n2. Centro\n3. Sur\n";
                    cin >> Elejir_region;
                    if (cin.fail() || Elejir_region < 1 || Elejir_region > 3) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada invalida. Intente nuevamente.\n";
                    } else {
                        Elejir_region--;  // Ajuste para indice 0 basado
                        break;
                    }
                } while (true);

                // Validar entrada de tipo de combustible
                do {
                    cout << "\nDe que tipo de combustible desea cambiar el precio?\n1. Regular\n2. Premium\n3. EcoExtra\n";
                    cin >> tipo_combustible;
                    if (cin.fail() || tipo_combustible < 1 || tipo_combustible > 3) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada invalida. Intente nuevamente.\n";
                    } else {
                        tipo_combustible--;  // Ajuste para indice 0 basado
                        break;
                    }
                } while (true);

                // Validar entrada del precio
                do {
                    cout << "\nPonga el nuevo precio: ";
                    cin >> Elejir_precio;
                    if (cin.fail() || Elejir_precio <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada invalida. Intente nuevamente.\n";
                    } else {
                        break;
                    }
                } while (true);

                // Actualizar el precio
                TerMax.fijar_precio(Elejir_region, tipo_combustible, Elejir_precio);

                // Mostrar nuevos precios
                cout << endl << "Precios Nuevos:" << endl
                     << "\tRegular\tPremium\tEcoExtra\n";
                for (uint16_t i = 0; i < 3; i++) {  // Correccion: i empieza desde 0
                    cout << regiones[i] << "\t";    // Usar i en lugar de 1 basado
                    for (uint16_t j = 0; j < 3; j++) {  // Correccion: j empieza desde 0
                        cout << TerMax.obtener_precio(i, j) << '\t';  // Acceder usando i y j
                    }
                    cout << endl;
                }

                break;
            }


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


// ============================================================
//  Función para manejar la gestión y flujo del menú de la Estacion de servicio
// ============================================================

void manejar_menu_estaciones_servicio(Estacion_servicio* estacion_actual) {
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

            case 0:{
                cout << "Saliendo de gestion de Estaciones de Servicio..." << endl;
                break;
            }

            case 1: {
                if (estacion_actual->obtener_numero_surtidores() == 12) {
                    cout << "Hay 12 surtidores. No se pueden agregar mas." << endl;
                } else {
                    string Modelo;

                    // Limpiar el buffer de entrada
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Solicitar el modelo del surtidor y validar la entrada
                    do {
                        cout << "Ingrese el modelo del surtidor: ";
                        getline(cin, Modelo);  // Leer la entrada del modelo

                        if (Modelo.empty()) {
                            cout << "El modelo no puede estar vacio. Intentelo de nuevo." << endl;
                        }
                    } while (Modelo.empty());  // Continuar hasta que se ingrese un modelo valido

                    // Agregar el surtidor a la estacion
                    estacion_actual->agregar_surtidor(Modelo);
                }
                break;  // Salir del case
            }


            case 2: {
                // Verificar si hay más de 2 surtidores para eliminar
                if (estacion_actual->obtener_numero_surtidores() <= 2) {
                    cout << endl << "Hay 2 surtidores o menos, no se puede eliminar ninguno." << endl;
                } else {

                    short unsigned int Eliminar;

                    // Mostrar la lista de surtidores

                    for (int i = 0; i < estacion_actual->obtener_numero_surtidores(); i++) {
                        cout << i + 1 << ". " << estacion_actual->obtener_surtidor(i)->obtener_codigo() << endl;
                    }
                    cout << "0. Cancelar" << endl;

                    // Solicitar el número del surtidor a eliminar
                    do {
                        cout << "Ingrese el número correspondiente al surtidor que desea eliminar: ";
                        cin >> Eliminar;

                        // Validar que la opción esté dentro del rango permitido
                        if (Eliminar < 0 || Eliminar > estacion_actual->obtener_numero_surtidores()) {
                            cout << "Opción inválida. Inténtelo de nuevo." << endl;
                        }

                    } while (Eliminar < 0 || Eliminar > estacion_actual->obtener_numero_surtidores());

                    // Si la opción no es cancelar, eliminar el surtidor
                    if (Eliminar > 0) {
                        estacion_actual->eliminar_surtidor(Eliminar - 1);
                    }
                }
                break;  // Salir del case
            }

            case 3: {
                short unsigned int* SurtidoresInactivos = new short unsigned int[estacion_actual->obtener_numero_surtidores()];
                short unsigned int CantSurtsIna = 0;

                // Mostrar la lista de surtidores inactivos
                cout << "Surtidores Inactivos:" << endl;
                for (short unsigned int i = 0; i < estacion_actual->obtener_numero_surtidores(); i++) {
                    if (!estacion_actual->obtener_surtidor(i)->obtener_estado()) {
                        cout << CantSurtsIna + 1 << ". " << estacion_actual->obtener_surtidor(i)->obtener_codigo() << endl;
                        SurtidoresInactivos[CantSurtsIna] = i;  // Guardar el índice del surtidor inactivo
                        CantSurtsIna++;
                    }
                }

                // Si hay surtidores inactivos, permitir la activación
                if (CantSurtsIna > 0) {
                    cout << "0. Cancelar" << endl;
                    short unsigned int Activar;

                    // Solicitar la activación de un surtidor inactivo
                    do {
                        cout << "Ingrese el numero que corresponde al surtidor que desea activar: ";
                        cin >> Activar;

                        // Validar que la opción esté dentro del rango permitido
                        if (Activar < 0 || Activar > CantSurtsIna) {
                            cout << "Opcion invalida. Intentelo de nuevo." << endl;
                        }

                    } while (Activar < 0 || Activar > CantSurtsIna);

                    // Si la opción no es cancelar, activar el surtidor
                    if (Activar > 0) {
                        estacion_actual->activar_surtidor(SurtidoresInactivos[Activar - 1]);
                    }
                } else {
                    cout << "No hay surtidores inactivos. Ninguno puede ser activado." << endl;
                }

                // Limpiar memoria
                delete[] SurtidoresInactivos;
                break;  // Salir del case
            }

            case 4: {
                short unsigned int* SurtidoresActivos = new short unsigned int[estacion_actual->obtener_numero_surtidores()];
                short unsigned int CantSurtsAct = 0;

                // Mostrar la lista de surtidores activos
                cout << "Surtidores Activos:" << endl;
                for (short unsigned int i = 0; i < estacion_actual->obtener_numero_surtidores(); i++) {
                    if (estacion_actual->obtener_surtidor(i)->obtener_estado()) {
                        cout << CantSurtsAct + 1 << ". " << estacion_actual->obtener_surtidor(i)->obtener_codigo() << endl;
                        SurtidoresActivos[CantSurtsAct] = i;  // Guardar el índice del surtidor activo
                        CantSurtsAct++;
                    }
                }

                // Si hay surtidores activos, permitir la desactivación
                if (CantSurtsAct > 0) {
                    cout << "0. Cancelar" << endl;
                    short unsigned int Desactivar;

                    // Solicitar la desactivación de un surtidor activo
                    do {
                        cout << "Ingrese el numero que corresponde al surtidor que desea desactivar: ";
                        cin >> Desactivar;

                        // Validar que la opción esté dentro del rango permitido
                        if (Desactivar < 0 || Desactivar > CantSurtsAct) {
                            cout << "Opcion invalida. Intentelo de nuevo." << endl;
                        }

                    } while (Desactivar < 0 || Desactivar > CantSurtsAct);

                    // Si la opción no es cancelar, desactivar el surtidor
                    if (Desactivar > 0) {
                        estacion_actual->desactivar_surtidor(SurtidoresActivos[Desactivar - 1]);
                    }
                } else {
                    cout << "No hay surtidores activos. Ninguno puede ser desactivado." << endl;
                }

                // Limpiar memoria
                delete[] SurtidoresActivos;
                break;  // Salir del case
            }

            case 5:
                estacion_actual->historico_transacciones();
                break;
            case 6:
                estacion_actual->reporte_ventas_tanque();
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


#endif // FUNCIONES_MENU_H
