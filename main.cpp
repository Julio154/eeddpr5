#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <chrono>
#include <iomanip> // Para formato de salida

#include "MediExpress.h"
#include "ThashMedicam.h"
#include "PaMedicamento.h"

// Ajusta estas rutas si tus ficheros están en otro sitio
const std::string RUTA_CSV = "../pa_medicamentos.csv";
const int NUM_DATOS_ESTIMADOS = 3310; // Dato del PDF

// Función auxiliar para cargar datos y devolver la tabla llena
void cargarYTestear(double lambda, int tipoHash, std::vector<int>& idsParaBuscar, std::list<PaMedicamento>& listaComparacion, bool llenarLista) {

    ThashMedicam tabla(NUM_DATOS_ESTIMADOS, lambda, tipoHash);

    std::ifstream is(RUTA_CSV);
    if (!is.good()) {
        std::cerr << "ERROR: No se puede abrir " << RUTA_CSV << std::endl;
        return;
    }

    std::string fila, id_num_str, id_alpha, nombre;

    while (getline(is, fila)) {
        if (fila.empty()) continue;
        std::stringstream columnas(fila);

        getline(columnas, id_num_str, ';');
        getline(columnas, id_alpha, ';');
        getline(columnas, nombre, ';');

        try {
            int id = std::stoi(id_num_str);
            PaMedicamento pa(id, id_alpha, nombre);

            // Insertar en Hash
            tabla.inserta(tabla.djb22(std::to_string(id)), pa);

            // Solo la primera vez llenamos la lista y el vector de IDs para las pruebas de tiempo
            if (llenarLista) {
                listaComparacion.push_back(pa);
                idsParaBuscar.push_back(id);
            }

        } catch (...) { continue; }
    }
    is.close();

    // --- IMPRESIÓN DE RESULTADOS EN FORMATO MARKDOWN ---
    std::string nombreHash;
    if (tipoHash == 1) nombreHash = "Cuadratica";
    else if (tipoHash == 2) nombreHash = "Doble A";
    else nombreHash = "Doble B";

    std::cout << "| " << std::left << std::setw(15) << nombreHash
              << " | " << std::setw(20) << tabla.getColisiones()
              << " | " << std::setw(20) << tabla.getMax10()
              << " | " << std::setw(15) << std::fixed << std::setprecision(4) << tabla.getFactorCarga()
              << " | " << std::setw(22) << tabla.getPromedioColisiones() << " |" << std::endl;
}

int main() {
    std::vector<int> idsBusqueda;
    std::list<PaMedicamento> listaLineal;

    // ------------------------------------------------------------------
    // PARTE 1: TABLAS COMPARATIVAS
    // ------------------------------------------------------------------

    // --- BLOQUE 1: Lambda 0.65 ---
    // Calculamos el tamaño primo aproximado para mostrarlo en el título
    ThashMedicam dummy(NUM_DATOS_ESTIMADOS, 0.65, 1);
    std::cout << "## Tamano de tabla (Lambda 0.65): " << dummy.getTamf() << std::endl;
    std::cout << "| funcion         | maximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |" << std::endl;
    std::cout << "|-----------------|:--------------------:|:--------------------:|:---------------:|:----------------------:|" << std::endl;

    cargarYTestear(0.65, 1, idsBusqueda, listaLineal, true);  // Hash 1 (y llenamos lista)
    cargarYTestear(0.65, 2, idsBusqueda, listaLineal, false); // Hash 2
    cargarYTestear(0.65, 3, idsBusqueda, listaLineal, false); // Hash 3
    std::cout << std::endl;

    // --- BLOQUE 2: Lambda 0.68 ---
    ThashMedicam dummy2(NUM_DATOS_ESTIMADOS, 0.68, 1);
    std::cout << "## Tamano de tabla (Lambda 0.68): " << dummy2.getTamf() << std::endl;
    std::cout << "| funcion         | maximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |" << std::endl;
    std::cout << "|-----------------|:--------------------:|:--------------------:|:---------------:|:----------------------:|" << std::endl;

    cargarYTestear(0.68, 1, idsBusqueda, listaLineal, false);
    cargarYTestear(0.68, 2, idsBusqueda, listaLineal, false);
    cargarYTestear(0.68, 3, idsBusqueda, listaLineal, false);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // PARTE 2: COMPARATIVA DE TIEMPOS (HASH vs LISTA)
    // ------------------------------------------------------------------
    std::cout << "## Comparacion de tiempos" << std::endl;

    // Usamos la mejor configuración (ejemplo: Lambda 0.65, Hash 2)
    // Tú puedes cambiar esto según cuál haya salido mejor arriba.
    ThashMedicam tablaOptima(NUM_DATOS_ESTIMADOS, 0.65, 2);

    // Recargar tabla optima
    std::ifstream is(RUTA_CSV);
    std::string fila, id_s, a, n;
    while(getline(is, fila)){
         if(fila.empty()) continue;
         std::stringstream ss(fila);
         getline(ss, id_s, ';'); getline(ss, a, ';'); getline(ss, n, ';');
         try { tablaOptima.inserta(tablaOptima.djb22(id_s), PaMedicamento(stoi(id_s), a, n)); } catch(...){}
    }
    is.close();

    // 1. MEDIR HASH
    auto start = std::chrono::high_resolution_clock::now();
    for (int id : idsBusqueda) {
        tablaOptima.buscar(tablaOptima.djb22(std::to_string(id)));
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationHash = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // 2. MEDIR LISTA
    start = std::chrono::high_resolution_clock::now();
    for (int id : idsBusqueda) {
        // Búsqueda lineal manual
        bool encontrado = false;
        for (const auto& med : listaLineal) {
            if (med.get_id_num() == id) {
                encontrado = true;
                break;
            }
        }
    }
    stop = std::chrono::high_resolution_clock::now();
    auto durationList = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Tiempo en realizar las busquedas en la Tabla Hash: " << durationHash.count() << " microsegundos." << std::endl;
    std::cout << "Tiempo en realizar las busquedas en la Lista: " << durationList.count() << " microsegundos." << std::endl;

    std::cout << "\n(NOTA: 1000 microsegundos = 1 milisegundo. Divide entre 1000 si lo quieres en ms)" << std::endl;


    /**
     * ############################
     * # Empieza la segunda parte #
     * ############################
     */
    MediExpress medi_express("../farmacias.csv","../pa_medicamentos.csv","../lab2.csv");

    medi_express.set_id_medication(tablaOptima);


    return 0;
}