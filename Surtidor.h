#ifndef SURTIDOR_H
#define SURTIDOR_H

// ============================================================
// Librerias
// ============================================================
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <iostream>
#include <chrono>
#include <string>
using namespace std;
// ============================================================
// Estructura para representar una venta
// ============================================================

struct Venta {
    uint16_t ano, mes, dia, hora, minuto;        // Fecha y hora de la venta
    uint16_t cantidad_combustible;               // Cantidad de combustible vendido en litros
    uint16_t categoria_combustible;              // Categoria del combustible (0: Regular, 1: Premium, 2: EcoExtra)
    uint16_t metodo_pago;                        // Metodo de pago (0: Efectivo, 1: Tarjeta de Credito, 2: Tarjeta de Debito)
    uint32_t id_cliente;                         // Identificador del cliente
    uint32_t cantidad_dinero;                    // Total de dinero pagado por la venta
};

// ============================================================
// Clase Surtidor: gestiona el estado y las ventas de un surtidor de combustible
// ============================================================

class Surtidor {
private:
    uint16_t codigo_id;                          // Codigo unico del surtidor
    string modelo_maquina;                       // Modelo de la maquina del surtidor
    uint16_t cantidad_ventas;                    // Numero de ventas realizadas
    bool estado;                                 // Estado del surtidor (true: activo, false: inactivo)
    Venta* ventas;                               // Arreglo dinamico que almacena las ventas realizadas

public:
    // Constructor
    Surtidor(uint16_t codigo, string modelo);

    // Destructor
    ~Surtidor();

    // Getters (metodos para obtener los valores de los atributos)
    uint16_t obtener_codigo() const { return codigo_id; }
    string obtener_modelo() const { return modelo_maquina; }
    uint16_t obtener_cantidad_ventas() const { return cantidad_ventas; }
    bool obtener_estado() const { return estado; }

    // Setters (metodos para modificar los valores de los atributos)
    void modificar_estado(bool nuevo_estado){ estado = nuevo_estado; }

    // Otros metodos
    void nueva_venta(uint16_t cantidad_combustible, uint16_t categoria_combustible, uint16_t metodo_pago, uint32_t id_cliente, uint32_t cantidad_dinero);
    void print_codigo_id();                      // Imprime el codigo del surtidor
    void print_modelo_maquina();                 // Imprime el modelo de la maquina
    void print_cantidad_ventas();                // Imprime la cantidad total de ventas realizadas
    void print_ventas();                         // Imprime el detalle de todas las ventas realizadas
    void print_estado();                         // Imprime el estado actual del surtidor
};

// ============================================================
// Implementacion de los metodos de la clase Surtidor
// ============================================================

// Constructor: inicializa el surtidor con el codigo, modelo, sin ventas y con el estado activo
Surtidor::Surtidor(uint16_t codigo, string modelo)
    : codigo_id(codigo), modelo_maquina(modelo), cantidad_ventas(0), estado(true), ventas(nullptr) {}

// Destructor: libera la memoria asignada al arreglo de ventas
Surtidor::~Surtidor() {
    delete[] ventas;  // Liberar memoria solo si se ha usado
}

// Registrar una nueva venta
void Surtidor::nueva_venta(uint16_t cantidad_combustible, uint16_t categoria_combustible, uint16_t metodo_pago, uint32_t id_cliente, uint32_t cantidad_dinero) {
    // Guardar el arreglo de ventas anteriores
    Venta* ventas_anteriores = ventas;
    // Crear un nuevo arreglo que incluya la nueva venta
    ventas = new Venta[cantidad_ventas + 1];

    // Copiar las ventas anteriores al nuevo arreglo
    for (int i = 0; i < cantidad_ventas; i++) {
        ventas[i] = ventas_anteriores[i];
    }

    // Obtener la fecha y hora actual
    auto hora = chrono::system_clock::now();
    time_t tiempo_actual = chrono::system_clock::to_time_t(hora);
    tm tm_struct;
    localtime_s(&tm_struct, &tiempo_actual);

    // Registrar la nueva venta en el arreglo
    ventas[cantidad_ventas] = {
        static_cast<uint16_t>(tm_struct.tm_year + 1900), static_cast<uint16_t>(tm_struct.tm_mon + 1),
        static_cast<uint16_t>(tm_struct.tm_mday), static_cast<uint16_t>(tm_struct.tm_hour),
        static_cast<uint16_t>(tm_struct.tm_min), cantidad_combustible,
        categoria_combustible, metodo_pago, id_cliente, cantidad_dinero
    };

    // Incrementar el contador de ventas
    cantidad_ventas++;
    // Liberar la memoria del arreglo anterior
    delete[] ventas_anteriores;
}

// Imprimir el codigo del surtidor
void Surtidor::print_codigo_id() {
    cout << "Codigo: " << codigo_id << std::endl;
}

// Imprimir el modelo de la maquina del surtidor
void Surtidor::print_modelo_maquina() {
    cout << "Modelo: " << modelo_maquina << std::endl;
}

// Imprimir la cantidad de ventas realizadas
void Surtidor::print_cantidad_ventas() {
    cout << "Cantidad de Ventas: " << cantidad_ventas << std::endl;
}

// Imprimir el detalle de todas las ventas realizadas
void Surtidor::print_ventas() {
    // Verificar si no se han realizado ventas
    if (cantidad_ventas < 1) {
        cout << "\nEl surtidor con codigo " << codigo_id << " no ha realizado ventas" << endl;
        return;
    }

    // Recorrer e imprimir cada venta
    for (uint16_t i = 0; i < cantidad_ventas; ++i) {
        const Venta& venta = ventas[i];

        // Traducir el tipo de combustible a una cadena
        string tipo_combustible;
        switch (venta.categoria_combustible) {
        case 0: tipo_combustible = "Regular"; break;
        case 1: tipo_combustible = "Premium"; break;
        case 2: tipo_combustible = "EcoExtra"; break;
        default: tipo_combustible = "Desconocido"; break;
        }

        // Traducir el metodo de pago a una cadena
        string metodo_pago;
        switch (venta.metodo_pago) {
        case 0: metodo_pago = "Efectivo"; break;
        case 1: metodo_pago = "Tarjeta de Credito"; break;
        case 2: metodo_pago = "Tarjeta de Debito"; break;
        default: metodo_pago = "Metodo Desconocido"; break;
        }

        // Imprimir la factura de la venta
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

    // Confirmar que se han mostrado todas las ventas
    cout << "\nSe han mostrado todas las ventas del surtidor con codigo " << codigo_id << endl;
}

#endif // SURTIDOR_H
