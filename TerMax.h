#ifndef TERMAX_H
#define TERMAX_H

// ============================================================
// Librerías
// ============================================================

#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

// ============================================================
// Estructuras
// ============================================================

struct Venta {
    int anio, mes, dia, hora, minuto;
    uint8_t cantidad_combustible;
    uint8_t categoria_combustible;
    uint8_t metodo_pago;
    uint8_t id_cliente;
    uint16_t cantidad_dinero;
};

// ============================================================
// Clases
// ============================================================

class Surtidor {
private:
    uint8_t codigo_id;
    uint8_t modelo_maquina;
    uint8_t cantidad_ventas;
    bool estado;
    Venta* ventas;

    void generar_codigo_id(uint8_t codigo_id_nuevo) { codigo_id = codigo_id_nuevo; }
    void generar_modelo_maquina(uint8_t modelo_maquina_nuevo) { modelo_maquina = modelo_maquina_nuevo; }
    void generar_estado(bool nuevo_estado) { estado = nuevo_estado; }

public:
    Surtidor(uint8_t codigo, uint8_t modelo);
    ~Surtidor();
    uint8_t obtener_codigo() const { return codigo_id; }
    uint8_t obtener_modelo() const { return modelo_maquina; }
    uint8_t obtener_cantidad_ventas() const { return cantidad_ventas; }
    bool obtener_estado() const { return estado; }
    Venta obtener_datos_venta(uint8_t id_venta) const;

    void nueva_venta(uint8_t cantidad_combustible, uint8_t categoria_combustible, uint8_t metodo_pago, uint8_t id_cliente, uint16_t cantidad_dinero);
    void print_codigo_id() const;
    void print_modelo_maquina() const;
    void print_cantidad_ventas() const;
    void print_ventas(uint8_t ventas_anteriores) const;
    void print_estado() const;
};

// Constructor
Surtidor::Surtidor(uint8_t codigo, uint8_t modelo)
    : codigo_id(codigo), modelo_maquina(modelo), cantidad_ventas(0), estado(true), ventas(nullptr) {}

// Destructor
Surtidor::~Surtidor() {
    delete[] ventas; // Liberar memoria
}

// Registrar una nueva venta
void Surtidor::nueva_venta(uint8_t cantidad_combustible, uint8_t categoria_combustible, uint8_t metodo_pago, uint8_t id_cliente, uint16_t cantidad_dinero) {
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

// Obtener los datos de una venta
Venta Surtidor::obtener_datos_venta(uint8_t id_venta) const {
    if (id_venta < cantidad_ventas) {
        return ventas[id_venta];
    } else {
        return {}; // Devolver una venta vacía si el índice es inválido
    }
}

// Imprimir código ID
void Surtidor::print_codigo_id() const {
    std::cout << "Código: " << static_cast<int>(codigo_id) << std::endl;
}

// Imprimir modelo de la máquina
void Surtidor::print_modelo_maquina() const {
    std::cout << "Modelo: " << static_cast<int>(modelo_maquina) << std::endl;
}

// Imprimir cantidad de ventas
void Surtidor::print_cantidad_ventas() const {
    std::cout << "Cantidad de Ventas: " << static_cast<int>(cantidad_ventas) << std::endl;
}

// Imprimir ventas
void Surtidor::print_ventas(uint8_t ventas_anteriores) const {
    if (cantidad_ventas < 1) {
        std::cout << "\nEl surtidor con código " << static_cast<int>(codigo_id) << " no ha realizado ventas" << std::endl;
        return;
    }

    if (ventas_anteriores >= cantidad_ventas) {
        std::cout << "\nYa se mostraron todas las ventas del surtidor con código " << static_cast<int>(codigo_id) << std::endl;
        return;
    }

    const Venta& venta = ventas[ventas_anteriores];
    std::cout << "\nVenta Número " << ventas_anteriores + 1 << " del Surtidor con Código " << static_cast<int>(codigo_id) << std::endl;
    std::cout << "Fecha y Hora: " << venta.anio << "/" << venta.mes << "/" << venta.dia
              << " " << venta.hora << ":" << venta.minuto << std::endl;
    std::cout << "Combustible: " << static_cast<int>(venta.cantidad_combustible)
              << " litros, Tipo: " << static_cast<int>(venta.categoria_combustible) << std::endl;
    std::cout << "Método de pago: " << static_cast<int>(venta.metodo_pago)
              << ", Cliente ID: " << static_cast<int>(venta.id_cliente)
              << ", Cantidad de dinero: " << venta.cantidad_dinero << std::endl;
    std::cout << "_________________________________________" << std::endl;
}

#endif // TERMAX_H
