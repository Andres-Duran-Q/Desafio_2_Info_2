#ifndef RED_NACIONAL_H
#define RED_NACIONAL_H
// ============================================================
// Librerias
// ============================================================
#include "Estacion_servicio.h"
using namespace std;

// ============================================================
// Estructura para representar un tanque de almacenamiento de combustible
// ============================================================
struct tipos_combustible {
    uint16_t Regular;   // Precio del combustible Regular
    uint16_t Premium;   // Precio del combustible Premium
    uint16_t EcoExtra;  // Precio del combustible EcoExtra
};

// ============================================================
// Clase Red_nacional
// ============================================================
class Red_nacional
{
private:
    tipos_combustible Precios_region[3];
    uint16_t numero_estaciones;
    Estacion_servicio** Estaciones;

public:
    // Constructor
    Red_nacional();

    // Destructor
    ~Red_nacional();

    // Otros metodos
    void agregar_estacion(string nombre, string gerente, uint16_t region, float Lat, float Long);
    void eliminar_estacion(uint16_t estacion);
    void fijar_precio(uint16_t Region, uint16_t Tipo, uint16_t NuevoPrecio);
};

// ============================================================
// Implementacion de los metodos de la clase Red_nacional
// ============================================================

Red_nacional::Red_nacional() : numero_estaciones(0), Estaciones(nullptr) {
    uint16_t precio = 10000;
    for (uint16_t i = 0; i < 3; i++) {
        Precios_region[i].Regular = precio;
        Precios_region[i].Premium = precio + 2000;
        Precios_region[i].EcoExtra = precio + 3000;
        precio += 1000; // Aumenta el precio base por región
    }
}

Red_nacional::~Red_nacional() {
    delete[] Estaciones;
}

void Red_nacional::fijar_precio(uint16_t Region, uint16_t Tipo, uint16_t NuevoPrecio) {
    switch (Tipo) {
    case 1:
        Precios_region[Region].Regular = NuevoPrecio;
        break;
    case 2:
        Precios_region[Region].Premium = NuevoPrecio;
        break;
    case 3:
        Precios_region[Region].EcoExtra = NuevoPrecio;
        break;
    default:
        // Manejo de error en caso de tipo de combustible incorrecto
        break;
    }
}

#endif // RED_NACIONAL_H
