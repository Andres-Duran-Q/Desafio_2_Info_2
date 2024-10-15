#ifndef SURTIDOR_H
#define SURTIDOR_H

// ============================================================
// Librerías
// ============================================================

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

// ============================================================
// Estructura
// ============================================================

struct Venta {
    int ano, mes, dia, hora, minuto;
    uint8_t cantidad_combustible;
    string categoria_combustible;
    string metodo_pago;
    uint32_t id_cliente;
    uint16_t cantidad_dinero;
};

// ============================================================
// Clase Surtidor
// ============================================================

class Surtidor {
private:
    uint16_t codigo_id;
    string modelo_maquina;
    uint8_t cantidad_ventas;
    bool estado;
    Venta* ventas;

public:

    Surtidor(uint16_t codigo, string modelo);
    ~Surtidor();

    uint16_t obtener_codigo() { return codigo_id; }
    string obtener_modelo() { return modelo_maquina; }
    uint8_t obtener_cantidad_ventas() { return cantidad_ventas; }
    bool obtener_estado() { return estado; }


    void modificar_estado(bool nuevo_estado){estado = nuevo_estado;}

    void nueva_venta(uint8_t cantidad_combustible, string categoria_combustible, string metodo_pago, uint32_t id_cliente, uint16_t cantidad_dinero);
    void print_codigo_id();
    void print_modelo_maquina();
    void print_cantidad_ventas();
    void print_ventas();
    void print_estado();
};

// ============================================================
// Implementacion de los metodos
// ============================================================

// Constructor
Surtidor::Surtidor(uint16_t codigo, string modelo)
    : codigo_id(codigo), modelo_maquina(modelo), cantidad_ventas(0), estado(true), ventas(nullptr) {}

// Destructor
Surtidor::~Surtidor() {
    delete[] ventas; // Liberar memoria
}

// Registrar una nueva venta
void Surtidor::nueva_venta(uint8_t cantidad_combustible, string categoria_combustible, string metodo_pago, uint32_t id_cliente, uint16_t cantidad_dinero) {
    Venta* ventas_anteriores = ventas;
    ventas = new Venta[cantidad_ventas + 1];

    for (int i = 0; i < cantidad_ventas; i++) {
        ventas[i] = ventas_anteriores[i]; // Copiar ventas anteriores
    }

    // Obtener la fecha y hora actual
    auto hora = std::chrono::system_clock::now();
    std::time_t tiempo_actual = std::chrono::system_clock::to_time_t(hora);
    std::tm tm_struct;
    localtime_s(&tm_struct, &tiempo_actual);

    // Añadir nueva venta
    ventas[cantidad_ventas] = {
        tm_struct.tm_year + 1900, tm_struct.tm_mon + 1, tm_struct.tm_mday,
        tm_struct.tm_hour, tm_struct.tm_min, cantidad_combustible,
        categoria_combustible, metodo_pago, id_cliente, cantidad_dinero
    };

    cantidad_ventas++;
    delete[] ventas_anteriores; // Liberar memoria anterior
}


// Imprimir código ID
void Surtidor::print_codigo_id() {
    std::cout << "Codigo: " << static_cast<int>(codigo_id) << std::endl;
}

// Imprimir modelo de la máquina
void Surtidor::print_modelo_maquina() {
    std::cout << "Modelo: " << (modelo_maquina) << std::endl;
}

// Imprimir cantidad de ventas
void Surtidor::print_cantidad_ventas() {
    std::cout << "Cantidad de Ventas: " << static_cast<int>(cantidad_ventas) << std::endl;
}

// Imprimir todas las ventas realizadas
void Surtidor::print_ventas() {
    if (cantidad_ventas < 1) {
        std::cout << "\nEl surtidor con codigo " << static_cast<int>(codigo_id) << " no ha realizado ventas" << std::endl;
        return;
    }

    for (uint8_t i = 0; i < cantidad_ventas; ++i) {
        const Venta& venta = ventas[i];
        std::cout << "\nVenta Numero " << i + 1 << " del Surtidor con Codigo " << static_cast<int>(codigo_id) << std::endl;
        std::cout << "Fecha y Hora: " << venta.ano << "/" << venta.mes << "/" << venta.dia
                  << " " << venta.hora << ":" << venta.minuto << std::endl;
        std::cout << "Combustible: " << static_cast<int>(venta.cantidad_combustible)
                  << " litros, Tipo: " << venta.categoria_combustible << std::endl;
        std::cout << "Metodo de pago: " << venta.metodo_pago
                  << ", Cliente ID: " << static_cast<int>(venta.id_cliente)
                  << ", Cantidad de dinero: " << venta.cantidad_dinero << std::endl;
        std::cout << "____________________________________________________________________________________________________" << std::endl;
    }

    std::cout << "\nSe han mostrado todas las ventas del surtidor con codigo " << static_cast<int>(codigo_id) << std::endl;
}


#endif // SURTIDOR_H
