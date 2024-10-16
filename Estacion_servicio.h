#ifndef ESTACION_SERVICIO_H
#define ESTACION_SERVICIO_H

// ============================================================
// Librerias
// ============================================================
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <string>
#include "Surtidor.h"

using namespace std;

// ============================================================
// Estructuras
// ============================================================

struct Tanque {
    uint16_t capacidad;
    uint16_t almacenamiento_actual;
    uint16_t cantidad_vendida;
};


// ============================================================
// Clase Estacion_servicio
// ============================================================

class Estacion_servicio {

private:
    // Atributos
    string nombre_id;
    uint16_t codigo_id;
    string gerente;
    uint16_t  region;
    float ubicacion_gps[2];
    Tanque tanques[3];
    uint16_t numero_surtidores;
    Surtidor** Surtidores;

public:
    // Constructor
    Estacion_servicio(string nombre_id, uint16_t codigo_id, string gerente, uint16_t region, float ubicacion_gps[2]);
    // Destructor
    ~Estacion_servicio();
    // Getters
    string obtener_nombre() {return nombre_id;}
    uint16_t obtener_codigo() {return codigo_id;}
    string obtener_gerente() {return gerente;}
    uint16_t obtener_region() {return region;}
    float* obtener_ubicacion() {return ubicacion_gps;}
    uint16_t obtener_numero_surtidores() {return numero_surtidores;}
    Surtidor* obtener_surtidor(uint16_t surtidor_id) {return Surtidores[surtidor_id];}
    // Otros
    void agregar_surtidor(string modelo_maquina);
    void eliminar_surtidor(uint16_t numero_surtidor);
    void activar_surtidor(uint16_t numero_surtidor);
    void desactivar_surtidor(uint16_t numero_surtidor);
    void historico_transacciones();
    void generar_tanque_central();
    void reporte_ventas_tanque();
    void simular_venta(uint32_t precio_combustible, uint16_t categoria_combustible);
    void mostrarInformacionSurtidores();
};

// ============================================================
//
// ============================================================

Estacion_servicio::Estacion_servicio(string nombre, uint16_t codigo, string gerente, uint16_t region, float gps[2])
    : nombre_id(nombre), codigo_id(codigo), gerente(gerente), region(region), numero_surtidores(0), Surtidores(nullptr) {

    //srand(time(0));  // Inicializa el generador de números aleatorios

    // Copia manual de los valores del array gps al array miembro ubicacion_gps
    ubicacion_gps[0] = gps[0];
    ubicacion_gps[1] = gps[1];

    // Inicializar los tanques
    generar_tanque_central();  // Esto inicializa las capacidades, almacenamiento y ventas de los tanques
}


Estacion_servicio::~Estacion_servicio(){
   for(int i = 0; i < numero_surtidores; i++){
        delete[] Surtidores[i];
    }
    delete[] Surtidores;
}

void Estacion_servicio::agregar_surtidor(string modelo_maquina) {
    uint16_t cod_surt;
    bool codigo_existente;

    do {
        codigo_existente = false;
        // Genera un número aleatorio entre 1 y 65535 (el rango máximo de un uint16_t)
        cod_surt = rand() % 65535 + 1;

        // Verificar si el código generado ya existe
        for (int i = 0; i < numero_surtidores; ++i) {
            if (Surtidores[i]->obtener_codigo() == cod_surt) {
                codigo_existente = true;
                break;
            }
        }
    } while (codigo_existente);  // Repetir hasta que se genere un código único

    // Crear el nuevo surtidor
    Surtidor* Nuevo = new Surtidor(cod_surt, modelo_maquina);
    Surtidor** nuevo_surtidores = new Surtidor*[numero_surtidores + 1];

    // Copiar surtidores existentes
    for (int i = 0; i < numero_surtidores; i++) {
        nuevo_surtidores[i] = Surtidores[i];
    }

    delete[] Surtidores;
    nuevo_surtidores[numero_surtidores] = Nuevo;
    Surtidores = nuevo_surtidores;
    numero_surtidores++;

    cout << endl << "El surtidor con codigo " << cod_surt << " se agrego con exito" << endl;
}


void Estacion_servicio:: eliminar_surtidor(uint16_t numero_surtidor) {
    if (!Surtidores[numero_surtidor]->obtener_estado()) {
        delete Surtidores[numero_surtidor];  // Elimina el surtidor específico

        Surtidor** Nuevo = new Surtidor*[numero_surtidores - 1];
        for (int i = 0; i < numero_surtidores; i++) {
            if (i < numero_surtidor) {
                Nuevo[i] = Surtidores[i];
            } else if (i > numero_surtidor) {
                Nuevo[i - 1] = Surtidores[i];
            }
        }
        delete[] Surtidores;
        Surtidores = Nuevo;
        numero_surtidores--;

        cout << "Surtidor borrado" << endl;
    } else {
        cout << "No se pudo eliminar el surtidor " << Surtidores[numero_surtidor]->obtener_codigo() << " porque esta activo" << endl;
    }
}


void Estacion_servicio::activar_surtidor(uint16_t numero_surtidor){
    if (!Surtidores[numero_surtidor]->obtener_estado()){
        Surtidores[numero_surtidor]->modificar_estado(true);
        std::cout<<"El surtidor "<<Surtidores[numero_surtidor]->obtener_codigo()<<" fue activado"<<std::endl;
    }
    else{
        std::cout<<"El surtidor "<<Surtidores[numero_surtidor]->obtener_codigo()<<" ya estaba activado"<<std::endl;
    }
}

void Estacion_servicio::desactivar_surtidor(uint16_t numero_surtidor){
    if (Surtidores[numero_surtidor]->obtener_estado()){
        Surtidores[numero_surtidor]->modificar_estado(false);
        std::cout << "El surtidor " << Surtidores[numero_surtidor]->obtener_codigo() << " fue desactivado" << std::endl;
    }
    else {
        std::cout << "El surtidor " << Surtidores[numero_surtidor]->obtener_codigo() << " ya estaba desactivado" << std::endl;
    }
}

void Estacion_servicio::historico_transacciones() {
    bool ventas_realizada = false;

    for (int i = 0; i < numero_surtidores; i++) {
        if (Surtidores[i]->obtener_cantidad_ventas() > 0) {
            Surtidores[i]->print_ventas();
            ventas_realizada = true;
        }
    }

    if (!ventas_realizada) {
        std::cout << std::endl << "Esta estacion no ha realizado ninguna venta" << std::endl;
    }
}

void Estacion_servicio::generar_tanque_central() {

    for (int i = 0; i < 3; i++) {
        tanques[i].capacidad = (rand()%101)+100;
        tanques[i].almacenamiento_actual = tanques[i].capacidad;
        tanques[i].cantidad_vendida = 0;
    }
}

void Estacion_servicio::reporte_ventas_tanque() {
    cout << endl << "Se ha vendido:" << endl;
    cout << "Regular\t\tPremium\t\tEcoExtra" << endl;

    // Asegúrate de que el array 'tanques' tiene al menos 3 elementos
    for (int i = 0; i < 3; i++) {
        cout << tanques[i].cantidad_vendida << " Litros\t";
    }
    cout << endl;
}

void Estacion_servicio::simular_venta(uint32_t precio_combustible, uint16_t categoria_combustible){
    uint16_t cantidad_combustible = (rand()%18)+3;
    int* surtidores_activos = new int [numero_surtidores];
    uint16_t contador_surtidor = 0;
    for (int i = 0; i<numero_surtidores; i++){
        if (Surtidores[i]->obtener_estado()){
            surtidores_activos[contador_surtidor]=i;
            contador_surtidor++;
        }
    }
    if (contador_surtidor>0){
        uint16_t Surt = rand()%contador_surtidor;
        if (cantidad_combustible>tanques[categoria_combustible].almacenamiento_actual) cantidad_combustible=tanques[categoria_combustible].almacenamiento_actual;
        Surtidores[surtidores_activos[Surt]]->nueva_venta(cantidad_combustible, categoria_combustible, rand()%3, (rand()%1000000000)+1000000000, cantidad_combustible*precio_combustible);
        Surtidores[surtidores_activos[Surt]]->print_ventas();
       tanques[categoria_combustible].almacenamiento_actual-=cantidad_combustible;
        tanques[categoria_combustible].cantidad_vendida+=cantidad_combustible;
    }
    else{
        cout<<endl<<"No hay surtidores activos en esta Estacion"<<endl;
    }
    delete[] surtidores_activos;
}

void Estacion_servicio::mostrarInformacionSurtidores() {
    cout << "=============================" << endl;
    cout << "Numero total de surtidores: " << numero_surtidores << endl;
    cout << "=============================" << endl;

    // Iterar sobre cada surtidor y mostrar la información
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
