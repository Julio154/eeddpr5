//
// Created by silvi on 18/10/2025.
//

#include "MediExpress.h"

#include <fstream>
#include <iostream>
#include <sstream>

ThashMedicam MediExpress::get_id_medication() const {
    return idMedication;
}

void MediExpress::set_id_medication(const ThashMedicam &id_medication) {
    idMedication = id_medication;
}

MediExpress::MediExpress() {
}

MediExpress::~MediExpress() {
}
/*MediExpress::MediExpress(const std::list<Laboratorio> &labs, const std::vector<PaMedicamento> &medication):
    labs(labs),
    medication(medication)
{}

MediExpress::MediExpress(const std::list<Laboratorio> &labs, const std::vector<PaMedicamento> &medication,
    const std::map<std::string,Farmacia> &pharmacy): labs(labs), medication(medication), pharmacy(pharmacy){
}
*/

MediExpress::MediExpress(std::string fichero1,std::string fichero2,
  std::string fichero3){
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    std::map<std::string,Farmacia> farmacias_avl;

    std::string cif = "";
    std::string provincia="";
    std::string localidad="";
    std::string nombre = "";
    std::string direccion="";
    std::string codPostal="";

    std::cout<<"Lectura de farmacias en avl"<<std::endl;

    //is.open("../farmacias.csv"); //carpeta de proyecto
    is.open(fichero1);
    if ( is.good() ) {
        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: cif;provincia;localidad;nombre;direccion;codPostal;

                getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia,';');
                getline(columnas, localidad,';');
                getline(columnas, nombre, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, direccion,';');
                getline(columnas, codPostal,';');

                fila="";
                columnas.clear();

                Farmacia farmacia(cif,provincia,localidad,nombre,direccion,codPostal);
                pharmacy.insert(std::make_pair(cif,farmacia));
            }
        }
        is.close();
    }
            std::string id_number = "";
            std::string id_alpha="";
         //   is.open("../pa_medicamentos.csv"); //carpeta de proyecto
                idMedication=ThashMedicam(3310, 0.65, 2);
                is.open(fichero2);
                 if ( is.good() ) {
                     clock_t t_ini = clock();

                     while ( getline(is, fila ) ) {

                         //¿Se ha leído una nueva fila?
                         if (fila!="") {

                             columnas.str(fila);

                             //formato de fila: id_number;id_alpha;nombre;

                             getline(columnas, id_number, ';'); //leemos caracteres hasta encontrar y omitir ';'
                             getline(columnas, id_alpha,';');
                             getline(columnas, nombre,';');

                             fila="";
                             columnas.clear();

                             int idNumber=std::stoi(id_number);
                             PaMedicamento medicamento(idNumber,id_alpha,nombre);
                             //medication.push_back(medicamento);


                             idMedication.inserta(idMedication.djb22(std::to_string(medicamento.get_id_num())),medicamento);
                             nombMedication.insert({nombre,&medicamento});
                         }
                     }

                     is.close();
                 }
                std::cout<<"Lectura de Laboratorios:"<<std::endl;
                std::string id;
                std::string nombre_lab;

                is.open(fichero3);
                //is.open("../lab2.csv"); //carpeta de proyecto
                if ( is.good() ) {

                    while ( getline(is, fila ) ) {

                        //¿Se ha leído una nueva fila?
                        if (fila!="") {

                            columnas.str(fila);

                            //formato de fila: id;nombreLab;direccion;codPostal;localidad;

                            getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                            getline(columnas, nombre_lab,';');
                            getline(columnas, direccion,';');
                            getline(columnas, codPostal,';');
                            getline(columnas, localidad,';');

                            fila="";
                            columnas.clear();

                            int idNumberLabs=std::stoi(id);
                            Laboratorio laboratorio (idNumberLabs,nombre_lab,direccion,codPostal,localidad);
                            labs.push_back(laboratorio);
                        }
                    }
                    is.close();
                }

    suministrarMed();

}
/*
MediExpress::MediExpress(const std::map<std::string,Farmacia> &pharmacy)
            : pharmacy(pharmacy) {
}*/

MediExpress::MediExpress(const MediExpress &orig):
    labs(orig.labs),
    idMedication(orig.idMedication),
    pharmacy(orig.pharmacy)
{}


void MediExpress::suministrarMed() {

    const std::size_t totalMed = nombMedication.size();
    int medAsignados = 0;

    std::multimap<std::string, PaMedicamento*>::iterator itMed = nombMedication.begin();

    for (list<Laboratorio>::iterator itLab = labs.begin();
         itLab != labs.end() && medAsignados < totalMed;
         ++itLab) {

        for (int i = 0; i < 2 && medAsignados < totalMed; ++i, ++itMed, ++medAsignados) {
            itMed->second->setLab(*itLab);
        }
         }

    std::cout << "Medicamentos enlazados: " << medAsignados
              << " | Sin enlazar: " << (totalMed - medAsignados) << std::endl;

    itMed = nombMedication.begin();

    const int MEDS_POR_FARMACIA = 100;
    const int STOCK_INICIAL = 10;

    for (std::multimap<std::string, Farmacia>::iterator itFarm = pharmacy.begin();
         itFarm != pharmacy.end() && itMed != nombMedication.end();
         ++itFarm) {

        Farmacia& farmaciaActual = itFarm->second;

        farmaciaActual.set_link_medi(this);

        for (int i = 0; i < MEDS_POR_FARMACIA; ++i) { // && medIndex < totalMed
            PaMedicamento* medPtr = itMed->second;
            farmaciaActual.nuevoStock(medPtr, STOCK_INICIAL);
            itMed++;
            if (itMed==nombMedication.end())
                itMed=nombMedication.begin();
        }
    }

    std::cout << "Stock inicial distribuido. Último índice de medicamento asignado: " << &itMed << std::endl;

}

Laboratorio * MediExpress::buscarLab(std::string nombreLab) {
std::list<Laboratorio>::iterator it= labs.begin();
    for (std::list<Laboratorio>::iterator it = labs.begin(); it!=labs.end(); it++) {
        if (it->get_nombre_lab() == nombreLab) {
            return &(*it);
        }
    }
    return nullptr;
}

std::list<Laboratorio*> MediExpress::buscarLabCiudad(std::string nombreCiudad) {
    std::list<Laboratorio*> nuevaLista;
    for (std::list<Laboratorio> ::iterator it= labs.begin();it!=labs.end() ; it++) {
        if (it->get_localidad().find(nombreCiudad)!= std::string::npos) {
            nuevaLista.push_back(&(*it));
        }
    }
    return nuevaLista;

}
std::list<Laboratorio*> MediExpress::buscarLabSoloCiudad(std::string nombreCiudad) {
    std::list<Laboratorio*> nuevaLista;
    for (std::list<Laboratorio> ::iterator it= labs.begin();it!=labs.end() ; it++) {
        if (it->get_localidad().find(nombreCiudad) != std::string::npos) {
            nuevaLista.push_back(&(*it));
        }
    }
    return nuevaLista;

}

std::set<PaMedicamento*> MediExpress::buscarCompuesto(std::string comp) {

    std::istringstream iss(comp);
    std::vector<std::string> palabrasBuscadas;
    std::string palabra;

    // 1. Separar las palabras de la búsqueda
    while (iss >> palabra) {
        if (!palabra.empty()) {
            palabrasBuscadas.push_back(palabra);
        }
    }
    if (palabrasBuscadas.empty()) {
        return {};
    }

    // 2. Realizar la primera búsqueda para inicializar el conjunto "intersección"
    std::set<PaMedicamento*> interseccion;

    // equal_range devuelve un par de iteradores (inicio, fin) de las coincidencias
    std::pair<std::multimap<std::string, PaMedicamento*>::iterator,
        std::multimap<std::string, PaMedicamento*>::iterator> range =
            nombMedication.equal_range(palabrasBuscadas[0]);

    // Insertamos todos los hallazgos de la primera palabra en un set (ordenado y sin duplicados)
    for (multimap<string,PaMedicamento*>::iterator it = range.first; it != range.second; ++it) {
        interseccion.insert(it->second);
    }

    // 3. Procesar el resto de palabras calculando la intersección progresiva
    for (int i = 1; i < palabrasBuscadas.size(); ++i) {
        // Si en algún momento la intersección se queda vacía, paramos (no habrá resultados)
        if (interseccion.empty()) break;

        std::set<PaMedicamento*> matchesPalabraActual;
        std::pair<std::multimap<std::string, PaMedicamento*>::iterator,
            std::multimap<std::string, PaMedicamento*>::iterator> rangePal =
                nombMedication.equal_range(palabrasBuscadas[i]);

        for (multimap<string,PaMedicamento*>::iterator it = rangePal.first; it != rangePal.second; ++it) {
            matchesPalabraActual.insert(it->second);
        }

        // Variable temporal para guardar el resultado de (Intersección_Actual AND Palabra_Nueva)
        std::set<PaMedicamento*> tempResultado;

        // Algoritmo de la STL que calcula la intersección de dos conjuntos ordenados
        std::set_intersection(interseccion.begin(), interseccion.end(),
                              matchesPalabraActual.begin(), matchesPalabraActual.end(),
                              std::inserter(tempResultado, tempResultado.begin()));

        // Actualizamos nuestro conjunto principal con el resultado filtrado
        interseccion = tempResultado;
    }

    return interseccion;
}

std::vector<PaMedicamento *> MediExpress::getMedicamSinLab() {
    std::vector<PaMedicamento*> vmedicamento;
    for (std::multimap<std::string,PaMedicamento*>::iterator it = nombMedication.begin();
        it != nombMedication.end();
        ++it) {
        if (it->second->servidoPor() == "") {
            vmedicamento.push_back(it->second);
        }
    }
    return vmedicamento;
}

std::list<Laboratorio>& MediExpress::get_labs()  {
    return labs;
}

std::vector<PaMedicamento *> MediExpress::get_medication() {
    /*
    std::vector<PaMedicamento*> meds;
    for (int i = 0; i < medication.size(); i++)
        meds[meds.size()] = &medication[i];
    return meds;*/
}

PaMedicamento *MediExpress::buscarCompuesto(int id_num) {
    PaMedicamento *medi = idMedication.buscar(id_num);
    return medi;
}

std::vector<Farmacia*> MediExpress::buscarFarmacias(std::string nombre) {
    std::vector<Farmacia*> farmacias;
    for (std::map<std::string,Farmacia>::iterator it=pharmacy.begin(); it!=pharmacy.end(); ++it) {
        if (it->second.get_provincia().find(nombre) != std::string::npos) {
            farmacias.push_back(&it->second);
        }
    }
    return farmacias;
}

void MediExpress::suministrarFarmacia(Farmacia &f, int id_num, int n) {
    PaMedicamento *medicam = buscarCompuesto(id_num);
    if (medicam != nullptr)
        f.nuevoStock(medicam,n);

}

std::list<Laboratorio*> MediExpress::buscarLabs(PaMedicamento med) {
    std::list<Laboratorio*> nuevaLista;
    for (std::list<Laboratorio> ::iterator it= labs.begin();it!=labs.end() ; it++) {
        if (it->get_nombre_lab().find(med.get_nombre()) != std::string::npos) {
            nuevaLista.push_back(&(*it));
        }
    }
    return nuevaLista;
}

std::map<std::string,Farmacia> *MediExpress::get_pharmacy() {
    //return &pharmacy;
}

bool MediExpress::eliminarMedicamento(int id_num) {
    bool encontradoEnCentral = false;
/*
    for (auto it = medication.begin(); it != medication.end(); ) {
        if (it->get_id_num() == id_num) {
            it = medication.erase(it);
            encontradoEnCentral = true;
            break;
        } else {
            ++it;
        }
    }

    int conteoFarmacias = 0;
    // Recorremos el mapa de farmacias
    for (auto& par : pharmacy) {
        if (par.second.eliminarStock(id_num)) {
            conteoFarmacias++;
        }
    }

    if (encontradoEnCentral) {
        std::cout << "Exito: Medicamento ID=" << id_num
                  << " eliminado del catalogo central y retirado de "
                  << conteoFarmacias << " farmacias." << std::endl;
    } else {
        std::cout << "Aviso: El medicamento ID=" << id_num
                  << " no se encontro en el catalogo central." << std::endl;
    }

    return encontradoEnCentral;*/
}

unsigned int MediExpress::maxColisiones() {
    return idMedication.getSumaColisiones();
}

unsigned int MediExpress::numMax10() {
    return idMedication.getMax10();

}
unsigned int MediExpress::promedioColisiones() {

    return idMedication.getPromedioColisiones();
}
float MediExpress::factorCarga() {

    return idMedication.getFactorCarga();
}

void MediExpress::mostrarEstadoTabla() {
    std::cout << std::endl;
    std::cout <<"ESTADO DE LA TABLA:"<< std::endl;
    std::cout <<"max colisiones "<<maxColisiones()<< std::endl;
    std::cout <<"numMax10: "<<numMax10()<< std::endl;
    //std::cout <<"promedio colisiones "<<promedioColisiones()<< std::endl;
    std::cout <<"factorCarga "<<factorCarga()<< std::endl;
    std::cout <<"Tamano Logico "<<idMedication.getTaml()<< std::endl;
    std::cout <<"Tamano fisico "<<idMedication.getTamf()<< std::endl;
}


