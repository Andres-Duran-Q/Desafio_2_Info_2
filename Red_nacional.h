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

    // Getters (metodos de acceso)
    uint16_t obtener_numero_estaciones(){return numero_estaciones;}
    Estacion_servicio* obtener_estacion(int numero_estacion){return Estaciones[numero_estacion];}
    uint16_t obtener_precio (int Region, int Tipo) {
        switch(Tipo) {
        case 0:  // Regular
            return Precios_region[Region].Regular;
        case 1:  // Premium
            return Precios_region[Region].Premium;
        case 2:  // EcoExtra
            return Precios_region[Region].EcoExtra;
        default: // Tipo no valido
            return 0; // Se puede manejar con una excepcion o un valor predeterminado
        }
    }

    // Otros metodos
    void agregar_estacion(string nombre, string gerente, uint16_t region, float Latitud, float Longitud);
    void eliminar_estacion(uint16_t estacion);
    void fijar_precio(uint16_t Region, uint16_t Tipo, uint16_t NuevoPrecio);
    void Ventas();
};

// ============================================================
// Implementacion de los metodos de la clase Red_nacional
// ============================================================

Red_nacional::Red_nacional() : numero_estaciones(0), Estaciones(nullptr) {
    // se iniciliza con un precio de combustible base
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


void Red_nacional::agregar_estacion(string nombre, string gerente, uint16_t region, float Latitud, float Longitud) {
    float gps[2]{Latitud, Longitud};
    uint16_t codigo_id_estacion;
    bool crear = true;

    // Inicializamos el generador de números aleatorios solo una vez
    static bool inicializar = false;
    if (!inicializar) {
        srand(time(0));
        inicializar = true;
    }

    // Generar un código aleatorio y verificar que sea único
    do {
        codigo_id_estacion = rand() % 65535 + 1; // Genera un número aleatorio entre 1 y 65535 (uint16_t)
        crear = true;  // Asumimos que se puede crear hasta que se pruebe lo contrario

        for (uint16_t i = 0; i < numero_estaciones; i++) {
            if (Estaciones[i]->obtener_codigo() == codigo_id_estacion) {
                crear = false;  // Si el código ya existe, volver a generar
                break;
            }
        }
    } while (!crear);  // Repetir hasta que se obtenga un código único

    // Verificar que el nombre y la ubicación sean únicos
    for (uint16_t i = 0; i < numero_estaciones; i++) {
        if (Estaciones[i]->obtener_nombre() == nombre) {
            crear = false;
            cout << endl << "El nombre de la estacion no puede coincidir con el de otra estacion" << endl;
            break;
        }
        else if (Estaciones[i]->obtener_ubicacion()[0] == gps[0] && Estaciones[i]->obtener_ubicacion()[1] == gps[1]) {
            crear = false;
            cout << endl << "Las ubicacion de la estacion no pueden coincidir con las de otras ubicaciones" << endl;
            break;
        }
    }

    if (crear) {
        Estacion_servicio* Nueva = new Estacion_servicio(nombre, codigo_id_estacion, gerente, region, gps);
        Estacion_servicio** Nueva_Estaciones = new Estacion_servicio*[numero_estaciones + 1];
        Nueva_Estaciones[numero_estaciones] = Nueva;
        for (uint16_t i = 0; i < numero_estaciones; i++) {
            Nueva_Estaciones[i] = Estaciones[i];
        }

        delete[] Estaciones;
        Estaciones = Nueva_Estaciones;
        numero_estaciones++;
        cout << endl << "La estacion se agrego exitosamente con el codigo " << codigo_id_estacion << endl;
    }
    else {
        cout << endl << "No se pudo agregar la estacion" << endl;
    }
}

void Red_nacional::eliminar_estacion(uint16_t estacion){
    for (uint16_t i = 0; i<Estaciones[estacion]->obtener_numero_surtidores(); i++){
        if (Estaciones[estacion]->obtener_surtidor(i)->obtener_estado()){
            cout<<std::endl<<"La estacion no se puede eliminar ya que todavia posee surtidores activos"<<std::endl;
            return;
        }
    }
    Estacion_servicio** Eliminar = new Estacion_servicio* [numero_estaciones+1];
    for (uint16_t i = 0; i<numero_estaciones; i++){
        if (i<estacion) Eliminar[i]=Estaciones[i];
        else if (i>estacion) Eliminar[i-1]=Estaciones[i];
    }
    delete [] Estaciones;
    numero_estaciones--;
    Estaciones = Eliminar;
    cout<<endl<<"La estacion fue eliminada con exito"<<endl;
}

void Red_nacional::fijar_precio(uint16_t region, uint16_t tipo, uint16_t nuevo_precio) {
    switch (tipo) {
    case 1:
        Precios_region[region].Regular = nuevo_precio;
        break;
    case 2:
        Precios_region[region].Premium = nuevo_precio;
        break;
    case 3:
        Precios_region[region].EcoExtra = nuevo_precio;
        break;
    default:
        // Manejo de error en caso de tipo de combustible incorrecto
        break;
    }
}

void Red_nacional::Ventas() {
    tipos_combustible litros_pais{0, 0, 0};  // Acumuladores de litros para todo el país
    tipos_combustible dinero_pais{0, 0, 0};  // Acumuladores de dinero para todo el país

    tipos_combustible litros_estacion{0, 0, 0};  // Acumuladores de litros por estación
    tipos_combustible dinero_estacion{0, 0, 0};  // Acumuladores de dinero por estación

    tipos_combustible litros_surtidor{0, 0, 0};  // Acumuladores de litros por surtidor
    tipos_combustible dinero_surtidor{0, 0, 0};  // Acumuladores de dinero por surtidor

    std::cout << "Ventas en cada E/S del pais\n";

    // Recorre todas las estaciones
    for (short unsigned int i = 0; i < numero_estaciones; i++) {
        std::cout << "_______________________________________\nEstación "
                  << Estaciones[i]->obtener_nombre() << " (" << Estaciones[i]->obtener_codigo() << ")\n";
        std::cout << "Surtidor | Litros Regular | $ Regular | Litros Premium | $ Premium | Litros EcoExtra | $ EcoExtra\n";

        // Recorre todos los surtidores de la estación
        for (short unsigned int j = 0; j < Estaciones[i]->obtener_numero_surtidores(); j++) {
            std::cout << Estaciones[i]->obtener_surtidor(j)->obtener_codigo() << "\t|";

            // Resetear acumuladores por surtidor
            litros_surtidor = {0, 0, 0};
            dinero_surtidor = {0, 0, 0};

            // Recorre todas las ventas del surtidor
            for (short unsigned int k = 0; k < Estaciones[i]->obtener_surtidor(j)->obtener_cantidad_ventas(); k++) {
                uint16_t litros_vendidos = Estaciones[i]->obtener_surtidor(j)->datos_venta(k, 10);  // Litros vendidos
                uint16_t tipo_combustible = Estaciones[i]->obtener_surtidor(j)->datos_venta(k, 7);  // Tipo de combustible
                uint32_t cantidad_vendida = Estaciones[i]->obtener_surtidor(j)->datos_venta(k, 11); // Dinero generado

                // Acumular litros y dinero según el tipo de combustible
                switch (tipo_combustible) {
                case 0: // Regular
                    litros_surtidor.Regular += litros_vendidos;
                    dinero_surtidor.Regular += cantidad_vendida;
                    break;
                case 1: // Premium
                    litros_surtidor.Premium += litros_vendidos;
                    dinero_surtidor.Premium += cantidad_vendida;
                    break;
                case 2: // EcoExtra
                    litros_surtidor.EcoExtra += litros_vendidos;
                    dinero_surtidor.EcoExtra += cantidad_vendida;
                    break;
                }
            }

            // Imprimir ventas por surtidor (litros y dinero)
            std::cout << litros_surtidor.Regular << " L\t| $" << dinero_surtidor.Regular << "\t| "
                      << litros_surtidor.Premium << " L\t| $" << dinero_surtidor.Premium << "\t| "
                      << litros_surtidor.EcoExtra << " L\t| $" << dinero_surtidor.EcoExtra << "\n";

            // Acumular al total por estación
            litros_estacion.Regular += litros_surtidor.Regular;
            dinero_estacion.Regular += dinero_surtidor.Regular;
            litros_estacion.Premium += litros_surtidor.Premium;
            dinero_estacion.Premium += dinero_surtidor.Premium;
            litros_estacion.EcoExtra += litros_surtidor.EcoExtra;
            dinero_estacion.EcoExtra += dinero_surtidor.EcoExtra;
        }

        // Imprimir total por estación (litros y dinero)
        std::cout << "Total\t| " << litros_estacion.Regular << " L\t| $" << dinero_estacion.Regular
                  << "\t| " << litros_estacion.Premium << " L\t| $" << dinero_estacion.Premium
                  << "\t| " << litros_estacion.EcoExtra << " L\t| $" << dinero_estacion.EcoExtra << "\n";

        // Acumular al total del país
        litros_pais.Regular += litros_estacion.Regular;
        dinero_pais.Regular += dinero_estacion.Regular;
        litros_pais.Premium += litros_estacion.Premium;
        dinero_pais.Premium += dinero_estacion.Premium;
        litros_pais.EcoExtra += litros_estacion.EcoExtra;
        dinero_pais.EcoExtra += dinero_estacion.EcoExtra;

        // Resetear acumuladores por estación
        litros_estacion = {0, 0, 0};
        dinero_estacion = {0, 0, 0};
    }

    // Imprimir total acumulado del país (litros y dinero)
    std::cout << "_______________________________________________________________________________\nPais\t| " << litros_pais.Regular << " L\t| $"
              << dinero_pais.Regular << "\t| " << litros_pais.Premium << " L\t| $" << dinero_pais.Premium
              << "\t| " << litros_pais.EcoExtra << " L\t| $" << dinero_pais.EcoExtra << "\n";
}


#endif // RED_NACIONAL_H
