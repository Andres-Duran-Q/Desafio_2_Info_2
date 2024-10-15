#ifndef ESTACION_SERVICIO_H
#define ESTACION_SERVICIO_H

// ============================================================
//
// ============================================================
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <string>
#include "Surtidor.h"

using namespace std;

// ============================================================
//
// ============================================================

class Estacion_servicio {

    friend void AsignarCapTC(Estacion_servicio& Est);

private:
    // Atributos
    string nombre_id;
    uint16_t codigo_id;
    string gerente;
    string  region;
    float ubicacion_gps[2];
    uint8_t numero_surtidores;
    Surtidor** Surtidores;

public:
    // Constructor
    Estacion_servicio(string nombre_id, uint16_t codigo_id, string gerente, string region, float ubicacion_gps[2]);
    ~Estacion_servicio();

    // Getters
    string obtener_nombre() {return nombre_id;}
    uint16_t obtener_codigo() {return codigo_id;}
    string obtener_gerente() {return gerente;}
    string obtener_region() {return region;}
    float* obtener_ubicacion() {return ubicacion_gps;}
    uint8_t obtener_numero_surtidores() {return numero_surtidores;}
    Surtidor* obtener_surtidor(uint16_t sutidor_id) {return Surtidores[sutidor_id];}

    // Otros
    void agregar_surtidor(string modelo_maquina);
    void eliminar_surtidor(uint16_t sutidor_id);
    void activar_surtidor(uint16_t sutidor_id);
    void desactivar_surtidor(uint16_t sutidor_id);
};

// ============================================================
//
// ============================================================

// Implementación de agregar_surtidor
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

    cout << endl << "El surtidor con código " << cod_surt << " se agregó con éxito" << endl;
}

void Estacion_servicio::eliminar_surtidor(uint16_t num_surt) {
    // Verificamos que el numero esté dentro del rango válido
    if (num_surt >= numero_surtidores) {
        cout << "Error: El surtidor con ID " << num_surt << " no existe." << endl;
        return;
    }

    // Verificamos que el surtidor no esté activado antes de eliminarlo
    if (Surtidores[num_surt]->obtener_estado()) {
        cout << "Error: No se puede eliminar el surtidor con ID " << num_surt << " porque está activado." << endl;
        return;
    }

    // Creamos un nuevo arreglo dinámico para los surtidores, con un tamaño reducido
    Surtidor** SurtidoresNew = new Surtidor*[numero_surtidores - 1];

    // Copiamos todos los surtidores excepto el que vamos a eliminar
    for (int i = 0, j = 0; i < numero_surtidores; ++i) {
        if (i != num_surt) {  // Saltamos el surtidor que vamos a eliminar
            SurtidoresNew[j] = Surtidores[i];
            j++;
        }
    }

    // Eliminamos el surtidor especificado
    delete Surtidores[num_surt];

    // Liberamos la memoria del arreglo anterior
    delete[] Surtidores;

    // Actualizamos el puntero para que apunte al nuevo arreglo
    Surtidores = SurtidoresNew;

    // Disminuimos el número de surtidores
    numero_surtidores--;

    cout << "El surtidor con ID " << surtidor_id << " se ha eliminado exitosamente." << endl;
}


#endif // ESTACION_SERVICIO_H
