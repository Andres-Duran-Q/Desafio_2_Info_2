#ifndef ESTACION_SERVICIO_H
#define ESTACION_SERVICIO_H

// ============================================================
// Librerias
// ============================================================
#include "Surtidor.h"
using namespace std;
// ============================================================
// Estructura para representar un tanque de almacenamiento de combustible
// ============================================================

struct Tanque {
    uint16_t capacidad;                 // Capacidad maxima del tanque
    uint16_t almacenamiento_actual;     // Cantidad de combustible disponible actualmente
    uint16_t cantidad_vendida;          // Cantidad de combustible vendida
};

// ============================================================
// Clase Estacion_servicio
// ============================================================

class Estacion_servicio {

private:
    // Atributos
    string nombre_id;                   // Identificador de la estacion
    uint16_t codigo_id;                 // Codigo unico de la estacion
    string gerente;                     // Nombre del gerente de la estacion
    uint16_t region;                    // Region donde esta ubicada la estacion
    float ubicacion_gps[2];             // Coordenadas GPS de la ubicacion de la estacion
    Tanque tanques[3];                  // Arreglo que almacena los tanques de la estacion
    uint16_t numero_surtidores;         // Cantidad de surtidores en la estacion
    Surtidor** Surtidores;              // Arreglo dinamico de apuntadores a los surtidores

public:
    // Constructor
    Estacion_servicio(string nombre_id, uint16_t codigo_id, string gerente, uint16_t region, float ubicacion_gps[2]);

    // Destructor
    ~Estacion_servicio();

    // Getters (metodos para obtener los valores de los atributos)
    string obtener_nombre() {return nombre_id;}                // Retorna el nombre de la estacion
    uint16_t obtener_codigo() {return codigo_id;}              // Retorna el codigo de la estacion
    string obtener_gerente() {return gerente;}                 // Retorna el nombre del gerente
    uint16_t obtener_region() {return region;}                 // Retorna el codigo de la region
    float* obtener_ubicacion() {return ubicacion_gps;}         // Retorna las coordenadas GPS de la estacion
    uint16_t obtener_numero_surtidores() {return numero_surtidores;}  // Retorna el numero de surtidores
    Surtidor* obtener_surtidor(uint16_t surtidor_id) {return Surtidores[surtidor_id];} // Retorna un surtidor especifico por su ID

    // Otros metodos
    void agregar_surtidor(string modelo_maquina);              // Agrega un nuevo surtidor a la estacion
    void eliminar_surtidor(uint16_t numero_surtidor);          // Elimina un surtidor por su numero
    void activar_surtidor(uint16_t numero_surtidor);           // Activa un surtidor especifico
    void desactivar_surtidor(uint16_t numero_surtidor);        // Desactiva un surtidor especifico
    void historico_transacciones();                            // Muestra el historico de transacciones de la estacion
    void generar_tanque_central();                             // Genera el tanque central de la estacion
    void reporte_ventas_tanque();                              // Reporta las ventas totales de los tanques
    void simular_venta(uint16_t precio_combustible, uint16_t categoria_combustible); // Simula una venta de combustible
    void mostrar_informacion_surtidores();                     // Muestra la informacion de todos los surtidores
};

// ============================================================
// Implementacion de los metodos de la clase Estacion_servicio
// ============================================================

// Constructor de la clase Estacion_servicio
Estacion_servicio::Estacion_servicio(string nombre, uint16_t codigo, string gerente, uint16_t region, float gps[2])
    : nombre_id(nombre), codigo_id(codigo), gerente(gerente), region(region), numero_surtidores(0), Surtidores(nullptr) {

    srand(time(0));  // Inicializa el generador de números aleatorios con la hora actual

    // Copia manual de los valores del array gps al array miembro ubicacion_gps
    ubicacion_gps[0] = gps[0];
    ubicacion_gps[1] = gps[1];

    // Llama a la función para inicializar los tanques
    generar_tanque_central();
}

// Destructor de la clase Estacion_servicio
Estacion_servicio::~Estacion_servicio(){
    // Libera la memoria de cada objeto Surtidor
    for(int i = 0; i < numero_surtidores; i++){
        delete Surtidores[i];
    }
    // Libera la memoria del array de punteros a Surtidores
    delete[] Surtidores;
}

// Función para agregar un nuevo surtidor
void Estacion_servicio::agregar_surtidor(string modelo_maquina) {
    uint16_t cod_surt;
    bool codigo_existente;

    do {
        codigo_existente = false;
        // Genera un código aleatorio para el surtidor
        cod_surt = rand() % 65535 + 1;

        // Verifica si el código ya existe en la lista de surtidores
        for (int i = 0; i < numero_surtidores; ++i) {
            if (Surtidores[i]->obtener_codigo() == cod_surt) {
                codigo_existente = true;
                break;
            }
        }
    } while (codigo_existente);  // Repite hasta generar un código único

    // Crea un nuevo objeto Surtidor
    Surtidor* Nuevo = new Surtidor(cod_surt, modelo_maquina);
    Surtidor** nuevo_surtidores = new Surtidor*[numero_surtidores + 1];

    // Copia los surtidores existentes al nuevo array
    for (int i = 0; i < numero_surtidores; i++) {
        nuevo_surtidores[i] = Surtidores[i];
    }

    // Actualiza el array de surtidores y aumenta el número de surtidores
    delete[] Surtidores;
    nuevo_surtidores[numero_surtidores] = Nuevo;
    Surtidores = nuevo_surtidores;
    numero_surtidores++;

    // Mensaje de éxito
    cout << endl << "El surtidor con codigo " << cod_surt << " se agrego con exito" << endl;
}

// Función para eliminar un surtidor
void Estacion_servicio::eliminar_surtidor(uint16_t numero_surtidor) {
    // Solo elimina si el surtidor está inactivo
    if (!Surtidores[numero_surtidor]->obtener_estado()) {
        delete Surtidores[numero_surtidor];  // Elimina el objeto Surtidor

        // Crea un nuevo array sin el surtidor eliminado
        Surtidor** Nuevo = new Surtidor*[numero_surtidores - 1];
        for (int i = 0; i < numero_surtidores; i++) {
            if (i < numero_surtidor) {
                Nuevo[i] = Surtidores[i];
            } else if (i > numero_surtidor) {
                Nuevo[i - 1] = Surtidores[i];
            }
        }

        // Actualiza el array de surtidores y reduce el número total
        delete[] Surtidores;
        Surtidores = Nuevo;
        numero_surtidores--;

        cout << "Surtidor borrado" << endl;
    } else {
        // Mensaje si el surtidor no puede ser eliminado
        cout << "No se pudo eliminar el surtidor " << Surtidores[numero_surtidor]->obtener_codigo() << " porque esta activo" << endl;
    }
}

// Función para activar un surtidor
void Estacion_servicio::activar_surtidor(uint16_t numero_surtidor){
    if (!Surtidores[numero_surtidor]->obtener_estado()){
        // Cambia el estado del surtidor a activo
        Surtidores[numero_surtidor]->modificar_estado(true);
        std::cout<<"El surtidor "<<Surtidores[numero_surtidor]->obtener_codigo()<<" fue activado"<<std::endl;
    } else {
        // Mensaje si ya estaba activado
        std::cout<<"El surtidor "<<Surtidores[numero_surtidor]->obtener_codigo()<<" ya estaba activado"<<std::endl;
    }
}

// Función para desactivar un surtidor
void Estacion_servicio::desactivar_surtidor(uint16_t numero_surtidor){
    if (Surtidores[numero_surtidor]->obtener_estado()){
        // Cambia el estado del surtidor a inactivo
        Surtidores[numero_surtidor]->modificar_estado(false);
        std::cout << "El surtidor " << Surtidores[numero_surtidor]->obtener_codigo() << " fue desactivado" << std::endl;
    } else {
        // Mensaje si ya estaba desactivado
        std::cout << "El surtidor " << Surtidores[numero_surtidor]->obtener_codigo() << " ya estaba desactivado" << std::endl;
    }
}

// Función para mostrar el histórico de transacciones de los surtidores
void Estacion_servicio::historico_transacciones() {
    bool ventas_realizada = false;

    // Itera sobre los surtidores y muestra las ventas si hay alguna
    for (int i = 0; i < numero_surtidores; i++) {
        if (Surtidores[i]->obtener_cantidad_ventas() > 0) {
            Surtidores[i]->print_ventas();
            ventas_realizada = true;
        }
    }

    // Mensaje si no se realizaron ventas
    if (!ventas_realizada) {
        std::cout << std::endl << "Esta estacion no ha realizado ninguna venta" << std::endl;
    }
}

// Función para inicializar los tanques de combustible
void Estacion_servicio::generar_tanque_central() {
    // Inicializa tres tanques con capacidad entre 100 y 200 litros
    for (int i = 0; i < 3; i++) {
        tanques[i].capacidad = (rand()%101)+100;
        tanques[i].almacenamiento_actual = tanques[i].capacidad;
        tanques[i].cantidad_vendida = 0;
    }
}

// Función para mostrar un reporte de ventas por tanque
void Estacion_servicio::reporte_ventas_tanque() {
    cout << endl << "Se ha vendido:" << endl;
    cout << "Regular\t\tPremium\t\tEcoExtra" << endl;

    // Muestra la cantidad vendida de cada categoria
    for (int i = 0; i < 3; i++) {
        cout << tanques[i].cantidad_vendida << " Litros\t";
    }
    cout << endl;
}

// Función para simular una venta
void Estacion_servicio::simular_venta(uint16_t precio_combustible, uint16_t categoria_combustible){
    uint16_t cantidad_combustible = (rand()%18)+3;  // Genera una cantidad aleatoria de combustible
    int* surtidores_activos = new int [numero_surtidores];  // Lista de surtidores activos
    uint16_t contador_surtidor = 0;

    // Verifica qué surtidores están activos
    for (int i = 0; i<numero_surtidores; i++){
        if (Surtidores[i]->obtener_estado()){
            surtidores_activos[contador_surtidor]=i;
            contador_surtidor++;
        }
    }

    if (contador_surtidor>0){
        uint16_t Surt = rand()%contador_surtidor;  // Selecciona un surtidor aleatorio de los activos

        // Ajusta la cantidad de combustible si es mayor al almacenamiento del tanque
        if (cantidad_combustible>tanques[categoria_combustible].almacenamiento_actual)
            cantidad_combustible = tanques[categoria_combustible].almacenamiento_actual;

        // Realiza la venta en el surtidor seleccionado
        Surtidores[surtidores_activos[Surt]]->nueva_venta(cantidad_combustible, categoria_combustible, rand()%3,
                                                          (rand()%999999999)+1000000000, cantidad_combustible*precio_combustible);
        Surtidores[surtidores_activos[Surt]]->print_ventas();

        // Actualiza el almacenamiento del tanque
        tanques[categoria_combustible].almacenamiento_actual -= cantidad_combustible;
        tanques[categoria_combustible].cantidad_vendida += cantidad_combustible;
    }
    else {
        // Mensaje si no hay surtidores activos
        cout<<endl<<"No hay surtidores activos en esta Estacion"<<endl;
    }

    delete[] surtidores_activos;  // Libera la memoria de la lista de surtidores activos
}

// Función para mostrar la información de todos los surtidores
void Estacion_servicio::mostrar_informacion_surtidores() {
    cout << "=============================" << endl;
    cout << "Numero total de surtidores: " << numero_surtidores << endl;
    cout << "=============================" << endl;

    // Itera sobre cada surtidor y muestra su información
    for (int i = 0; i < numero_surtidores; i++) {
        cout << "Surtidor " << i + 1 << ":" << endl;
        cout << "  - ID: " << Surtidores[i]->obtener_codigo() << endl;
        cout << "  - Modelo: " << Surtidores[i]->obtener_modelo() << endl;
        cout << "  - Estado: " << (Surtidores[i]->obtener_estado() ? "Activo" : "Inactivo") << endl;
        cout << "  - Cantidad de ventas: " << Surtidores[i]->obtener_cantidad_ventas() << endl;
        cout << "-----------------------------" << endl;
    }
}



#endif // ESTACION_SERVICIO_H
