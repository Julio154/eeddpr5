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

void menu() {

    cout<<"1. Buscar los siguientes compuesto por nombre completo y mostrarlos en pantalla "<<endl;
    cout<<"2. Los sevillanos compran magnesio , 12 personas a todas las farmacias"<<endl;
    cout<<"3. Mostrar stock farmacia Ubeda antes y despues de pedir “ANTIGENO OLIGOSACARIDO” en todas sus formas, pedir 10u "<<endl;
    cout<<"4. Eliminar CIANURO y BISMUTO en las farmacias "<<endl;
    cout<<"5.PAREJAS: Redispersar"<<endl;

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

    std::cout << "Tiempo en realizar las busquedas en la Tabla Hash: " << (float)durationHash.count()/1000 << " ms." << std::endl;
    std::cout << "Tiempo en realizar las busquedas en la Lista: " << (float)durationList.count()/1000 << " ms." << std::endl;

    /**
     * ############################
     * # Empieza la segunda parte #
     * ############################
     */


    MediExpress medi_express("../farmacias.csv","../pa_medicamentos.csv","../lab2.csv");
    int opcion;
    do {
    menu();
        std::cin >> opcion;
        switch (opcion) {

            case 1: {
                cout<<"1. Buscar los siguientes compuesto por nombre completo y mostrarlos en pantalla "<<endl;
                set<PaMedicamento*> magclohe=medi_express.buscarCompuesto("MAGNESIO CLORURO HEXAHIDRATO");

                cout<<"BUSQUEDA :  MAGNESIO CLORURO HEXAHIDRATO --------"<<endl;
                if (!magclohe.empty()) {
                    for (PaMedicamento* medicamento : magclohe) {
                            std::cout << "-Nombre: " << medicamento->get_nombre() << std::endl;
                            std::cout << "-Num: " << medicamento->get_id_num() << std::endl;
                            std::cout << "-Alpha: " << medicamento->get_id_alpha() << std::endl;
                    }
                }
                cout<<"BUSQUEDA :   CLORURO --------"<<endl;

                set<PaMedicamento*>cloruro= medi_express.buscarCompuesto("CLORURO");
                if (!cloruro.empty()) {
                    for (PaMedicamento* medicamento : cloruro) {
                            std::cout << "-Nombre: " << medicamento->get_nombre() << std::endl;
                            std::cout << "-Num: " << medicamento->get_id_num() << std::endl;
                            std::cout << "-Alpha: " << medicamento->get_id_alpha() << std::endl;
                    }
                }
                cout<<"BUSQUEDA :  ANHIDRO CALCIO CLORURO --------"<<endl;

                set<PaMedicamento*>anhcalclo= medi_express.buscarCompuesto("ANHIDRO CALCIO CLORURO");
                if (!anhcalclo.empty()) {
                    for (PaMedicamento* medicamento : anhcalclo) {
                            std::cout << "-Nombre: " << medicamento->get_nombre() << std::endl;
                            std::cout << "-Num: " << medicamento->get_id_num() << std::endl;
                            std::cout << "-Alpha: " << medicamento->get_id_alpha() << std::endl;
                    }
                }

                cout<<"BUSQUEDA :  LIDOCAINA HIDROCLORURO --------"<<endl;

                set<PaMedicamento*>lidohidro= medi_express.buscarCompuesto("LIDOCAINA HIDROCLORURO");
                if (!lidohidro.empty()) {
                    for (PaMedicamento* medicamento : lidohidro) {
                            std::cout << "-Nombre: " << medicamento->get_nombre() << std::endl;
                            std::cout << "-Num: " << medicamento->get_id_num() << std::endl;
                            std::cout << "-Alpha: " << medicamento->get_id_alpha() << std::endl;
                    }
                }
                cout<<"BUSQUEDA :  MENTA PIPERITA --------"<<endl;

                set<PaMedicamento*>mentapipe= medi_express.buscarCompuesto("MENTA PIPERITA");
                if (!mentapipe.empty()) {
                    for (PaMedicamento* medicamento : mentapipe) {
                            std::cout << "-Nombre: " << medicamento->get_nombre() << std::endl;
                            std::cout << "-Num: " << medicamento->get_id_num() << std::endl;
                            std::cout << "-Alpha: " << medicamento->get_id_alpha() << std::endl;
                    }
                }


                cout<<"BUSQUEDA :  VIRUS GRIPE --------"<<endl;

                set<PaMedicamento*>virusgripe=medi_express.buscarCompuesto("VIRUS GRIPE ");
                if (!virusgripe.empty()) {
                    for (PaMedicamento* medicamento : virusgripe) {
                            std::cout << "-Nombre: " << medicamento->get_nombre() << std::endl;
                            std::cout << "-Num: " << medicamento->get_id_num() << std::endl;
                            std::cout << "-Alpha: " << medicamento->get_id_alpha() << std::endl;
                    }
                }

                break;
            }
            case 2: {
                cout<<"2. Los sevillanos compran magnesio , 12 personas a todas las farmacias"<<endl;
                vector<Farmacia*> sevilla=medi_express.buscarFarmacias("SEVILLA");
                set<PaMedicamento*> magnesio=medi_express.buscarCompuesto("MAGNESIO");
                int s;
                int compra=0;
                for (int cliente=0;cliente<12;cliente++) {
                    cout<<"CLIENTE : "<<cliente<<endl;
                    for (int i = 0; i < sevilla.size(); ++i) {
                        cout<<"Compra en Farmacia "<<i<<" : "<<sevilla[i]->get_nombre()<<"Ubicada en "<<sevilla[i]->get_provincia()<<endl;
                        for (PaMedicamento* medicamento : magnesio) {
                            cout<<"Intentando comprar: "<<medicamento->get_nombre()<<endl;
                            s=sevilla[i]->comprarMedicam(medicamento->get_id_num(),1,*medicamento);
                            cout<<"Stock: "<<s<<endl;
                            if (s!=0) {
                                compra=1;
                                break;
                            }
                        }
                        if (compra==0) {
                            cout<<"No hay ningun tipo de magnesio, pedimos OXIDO DE MAGNESIO"<<endl;
                            PaMedicamento* oxMg=medi_express.buscarCompuesto(3640);
                            sevilla[i]->nuevoStock(oxMg,10);
                            cout<<"Stock OXIDO MAGNESIO: "<<sevilla[i]->comprarMedicam(3640,1,*oxMg)<<endl;
                        }
                        compra=0;
                    }
                }
                break;
            }
            case 3: {
                cout<<"3. Mostrar stock farmacia Ubeda antes y despues de pedir ANTIGENO OLIGOSACARIDO en todas sus formas, pedir 10u "<<endl;
                vector<Farmacia*> jaen=medi_express.buscarFarmacias("JAEN");
                cout<<"Farmacia ubicada en la localidad: "<<jaen[0]->get_localidad()<<endl;
                set<PaMedicamento*> antigeno=medi_express.buscarCompuesto("ANTIGENO OLIGOSACARIDO");
                for (PaMedicamento* medicamento : antigeno) {
                    cout<<"NOMBRE:"<<medicamento->get_nombre()<<endl;
                    cout<<"STOCK:"<<jaen[0]->buscaMedicamID(medicamento->get_id_num())<<endl;
                }
                cout<<"Realizando pedido ...." <<endl;
                for (PaMedicamento* medicamento : antigeno) {
                    cout<<"NOMBRE:"<<medicamento->get_nombre()<<endl;
                    jaen[0]->nuevoStock(medicamento,10);
                    cout<<"STOCK:"<<jaen[0]->buscaMedicamID(medicamento->get_id_num())<<endl;
                }
                break;
            }
            case 4: {
                cout<<"4. Eliminar CIANURO y BISMUTO en las farmacias "<<endl;
                set<PaMedicamento*> cianuro=medi_express.buscarCompuesto("CIANURO");
                set<PaMedicamento*> bismuto=medi_express.buscarCompuesto("BISMUTO");
                cout<<"Hay "<<cianuro.size()<<" medicamentos con CIANURO"<<endl;
                cout<<"Hay "<<bismuto.size()<<" medicamentos con BISMUTO"<<endl;
                for (PaMedicamento* medicamento : cianuro) {
                    cout<<"Eliminando "<<medicamento->get_nombre()<<endl;
                    medi_express.eliminarMedicamento(medicamento->get_id_num());
                }
                for (PaMedicamento* medicamento : bismuto) {
                    cout<<"Eliminando "<<medicamento->get_nombre()<<endl;
                    medi_express.eliminarMedicamento(medicamento->get_id_num());
                }
                break;
            }
            case 5:
                cout<<"PAREJAS: Redispersar"<<endl;
                break;
        }
    }while (opcion>0);
    return 0;
}