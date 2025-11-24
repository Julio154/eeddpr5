//
// Created by silvi on 18/10/2025.
//

#include "MediExpress.h"

#include <fstream>
#include <iostream>
#include <sstream>

MediExpress::MediExpress() {
}

MediExpress::~MediExpress() {
}
MediExpress::MediExpress(const std::list<Laboratorio> &labs, const std::vector<PaMedicamento> &medication):
    labs(labs),
    medication(medication)
{}

MediExpress::MediExpress(const std::list<Laboratorio> &labs, const std::vector<PaMedicamento> &medication,
    const std::map<std::string,Farmacia> &pharmacy): labs(labs), medication(medication), pharmacy(pharmacy){
}


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
                        medication.push_back(medicamento);
                    }
                }

                is.close();

                std::cout<<"Lectura de Laboratorios:"<<std::endl;
                std::string id;
                std::string nombre_lab;
                std::string direccion;
                std::string codPostal;
                std::string localidad;

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
            }

    suministrarMed();

}
MediExpress::MediExpress(const std::map<std::string,Farmacia> &pharmacy)
            : pharmacy(pharmacy) {
}

MediExpress::MediExpress(const MediExpress &orig):
    labs(orig.labs),
    medication(orig.medication),
    pharmacy(orig.pharmacy)
{}


void MediExpress::suministrarMed() {
    unsigned int totalMed = medication.size();
    unsigned int medIndex = 0;

    for (std::list<Laboratorio>::iterator it = labs.begin();
         it!=labs.end() && medIndex < totalMed;it++) {

        for (int i = 0; i < 2 && medIndex < totalMed; ++i) {
            medication[medIndex].setLab(*it);
            ++medIndex;
        }
    }

    std::cout << "Medicamentos enlazados: " << medIndex
              << " | Sin enlazar: " << (totalMed - medIndex) << std::endl;

    medIndex = 0;

    const int MEDS_POR_FARMACIA = 100;
    const int STOCK_INICIAL = 10;

    for (std::map<std::string, Farmacia>::iterator itFarm = pharmacy.begin();
         itFarm != pharmacy.end() && medIndex < totalMed;
         ++itFarm) {

        Farmacia& farmaciaActual = itFarm->second;

        farmaciaActual.set_link_medi(this);

        for (int i = 0; i < MEDS_POR_FARMACIA; ++i) { // && medIndex < totalMed
            PaMedicamento* medPtr = &medication[medIndex];
            farmaciaActual.nuevoStock(medPtr, STOCK_INICIAL);
            medIndex++;
            if (medIndex==totalMed)medIndex=0;
        }
    }

    std::cout << "Stock inicial distribuido. Último índice de medicamento asignado: " << medIndex << std::endl;

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

std::vector<PaMedicamento*> MediExpress::buscarCompuesto(std::string comp) {
    std::vector<PaMedicamento*> vmedicamento;
    for (unsigned int i = 0; i < medication.size(); ++i) {
        if (medication[i].get_nombre().find(comp) != std::string::npos) {
            vmedicamento.push_back(&medication[i]);
            std::cout<<"Medicamento encontrado: "<<medication[i].get_nombre()<<std::endl;
        }
    }
    return vmedicamento;
}

std::vector<PaMedicamento *> MediExpress::getMedicamSinLab() {
    std::vector<PaMedicamento*> vmedicamento;
    for (unsigned int i = 0; i < medication.size(); ++i) {
        if (medication[i].servidoPor() == "") {
            vmedicamento.push_back(&medication[i]);
        }
    }
    return vmedicamento;
}

std::list<Laboratorio>& MediExpress::get_labs()  {
    return labs;
}

std::vector<PaMedicamento *> MediExpress::get_medication() {
    std::vector<PaMedicamento*> meds;
    for (int i = 0; i < medication.size(); i++)
        meds[meds.size()] = &medication[i];
    return meds;
}

PaMedicamento *MediExpress::buscarCompuesto(int id_num) {
    for (unsigned i = 0; i < medication.size(); ++i) {
        if (medication[i].get_id_num() == id_num) {
            return &medication[i];
        }
    }
    return nullptr;
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
    return &pharmacy;
}

bool MediExpress::eliminarMedicamento(int id_num) {
    bool encontradoEnCentral = false;

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

    return encontradoEnCentral;
}


