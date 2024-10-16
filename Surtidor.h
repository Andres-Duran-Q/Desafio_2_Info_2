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
    uint16_t cantidad_combustible;
    uint16_t categoria_combustible;
    uint16_t metodo_pago;
    uint32_t id_cliente;
    uint32_t cantidad_dinero;
};

// ============================================================
// Clase Surtidor
// ============================================================

class Surtidor {
private:
    uint16_t codigo_id;
    string modelo_maquina;
    uint16_t cantidad_ventas;
    bool estado;
    Venta* ventas;

public:
    // Constructor
    Surtidor(uint16_t codigo, string modelo);
    // Destructor
    ~Surtidor();
    // Getters
    uint16_t obtener_codigo() { return codigo_id; }
    string obtener_modelo() { return modelo_maquina; }
    uint16_t obtener_cantidad_ventas() { return cantidad_ventas; }
    bool obtener_estado() { return estado; }
    // setters
    void modificar_estado(bool nuevo_estado){estado = nuevo_estado;}
    // Otros
    void nueva_venta(uint16_t cantidad_combustible, uint16_t categoria_combustible, uint16_t metodo_pago, uint32_t id_cliente, uint32_t cantidad_dinero);
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
    if (ventas != nullptr) {
        delete[] ventas;  // Liberar memoria solo si se ha usado
    }
}

// Registrar una nueva venta
void Surtidor::nueva_venta(uint16_t cantidad_combustible, uint16_t categoria_combustible, uint16_t metodo_pago, uint32_t id_cliente, uint32_t cantidad_dinero) {
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
    std::cout << "Codigo: " << codigo_id << std::endl;
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
        cout << "\nEl surtidor con codigo " << codigo_id << " no ha realizado ventas" << endl;
        return;
    }

    for (uint16_t i = 0; i < cantidad_ventas; ++i) {
        const Venta& venta = ventas[i];

        // Traducir el tipo de combustible
        string tipo_combustible;
        switch (venta.categoria_combustible) {
        case 0: tipo_combustible = "Regular"; break;
        case 1: tipo_combustible = "Premium"; break;
        case 2: tipo_combustible = "EcoExtra"; break;
        default: tipo_combustible = "Desconocido"; break;
        }

        // Traducir el metodo de pago
        string metodo_pago;
        switch (venta.metodo_pago) {
        case 0: metodo_pago = "Efectivo"; break;
        case 1: metodo_pago = "Tarjeta de Credito"; break;
        case 2: metodo_pago = "Tarjeta de Debito"; break;
        default: metodo_pago = "Metodo Desconocido"; break;
        }

        // Imprimir factura
        cout << "\n=========================== FACTURA DE VENTA ===========================\n";
        cout << "Surtidor Codigo: " << codigo_id << " | Venta Nro: " << i + 1 << "\n";
        cout << "Fecha: " << venta.ano << "/" << venta.mes << "/" << venta.dia
             << " | Hora: " << venta.hora << ":" << (venta.minuto < 10 ? "0" : "") << venta.minuto << "\n";
        cout << "--------------------------------------------------------------------------\n";
        cout << "Cantidad de combustible: " << venta.cantidad_combustible << " litros\n";
        cout << "Tipo de combustible: " << tipo_combustible << "\n";
        cout << "--------------------------------------------------------------------------\n";
        cout << "Metodo de pago: " << metodo_pago << "\n";
        cout << "ID Cliente: " << venta.id_cliente << "\n";
        cout << "Total: " << venta.cantidad_dinero << " Pesos Col \n";
        cout << "==========================================================================\n";
    }

    cout << "\nSe han mostrado todas las ventas del surtidor con codigo " << codigo_id << endl;
}



#endif // SURTIDOR_H
