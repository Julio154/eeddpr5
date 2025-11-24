//
// Created by silvi on 25/10/2025.
//


#include "Farmacia.h"
#include "MediExpress.h"


Farmacia::Farmacia()=default;

Farmacia::Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
                   const std::string &nombre, const std::string &direccion, const std::string &cod_postal)
        :cif(cif),
        provincia(provincia),
        localidad(localidad),
        nombre(nombre),
        direccion(direccion),
        codPostal(cod_postal),
        linkMedi(nullptr),
        order()
{}

Farmacia::Farmacia(const Farmacia &other):
    cif(other.cif),
    provincia(other.provincia),
    localidad(other.localidad),
    nombre(other.nombre),
    direccion(other.direccion),
    codPostal(other.codPostal),
    linkMedi(other.linkMedi),
    order(other.order)
{}

std::set<Stock*> Farmacia::buscaMedicamNombre(std::string nombreMed) {
    std::set<Stock*> aux;
    for (std::set<Stock*>::iterator it = order.begin(); it != order.end(); ++it) {
        if ((*it)->get_medicamento_asociado()->get_nombre().find(nombreMed) != std::string::npos) {
            aux.insert(*it);
        }
    }
    return aux;
}

int Farmacia::buscaMedicamID(int id_num) {

    for (std::set<Stock*>::iterator it = order.begin(); it != order.end(); ++it) {
        if ((*it)->get_id_pa_med() == id_num) {
            return (*it)->get_num_stock();
        }
    }
    return 0;
}
/*
std::vector<PaMedicamento*> Farmacia::buscaMedicamNombre(std::string nombreMed) {
    std::vector<PaMedicamento*> medicamentos;
    for (int i = 0; i < dispense.size(); i++) {
        if (dispense[i]->get_nombre().find(nombreMed) != std::string::npos) {
            medicamentos.push_back(dispense[i]);
        }
    }
    return medicamentos;
}
*/
void Farmacia::pedidoMedicam(int id_num, int n) {
    linkMedi->suministrarFarmacia(*this,id_num, n);
}
/**
void Farmacia::dispensaMedicam(PaMedicamento *pa) {
    dispense.push_back(pa);
}
*/

int Farmacia::comprarMedicam(int id_num, int n, PaMedicamento &result) {

    int num_med_disp = buscaMedicamID(id_num);
    if (num_med_disp > n) {
        Stock *aux;
        for (std::set<Stock*>::iterator it = order.begin(); it != order.end(); ++it) {
            if ((*it)->get_id_pa_med() == id_num) {
                aux = (*it);
                break;
            }
        }
        aux->decrementa(n);
    }else {
        pedidoMedicam(id_num, n);
    }

    return num_med_disp;
}

std::string Farmacia::get_cif() const {
    return cif;
}

void Farmacia::set_cif(const std::string &cif) {
    this->cif = cif;
}

std::string Farmacia::get_provincia() const {
    return provincia;
}

void Farmacia::set_provincia(const std::string &provincia) {
    this->provincia = provincia;
}

std::string Farmacia::get_localidad() const {
    return localidad;
}

void Farmacia::set_localidad(const std::string &localidad) {
    this->localidad = localidad;
}

std::string Farmacia::get_nombre() const {
    return nombre;
}

void Farmacia::set_nombre(const std::string &nombre) {
    this->nombre = nombre;
}

std::string Farmacia::get_direccion() const {
    return direccion;
}

void Farmacia::set_direccion(const std::string &direccion) {
    this->direccion = direccion;
}

std::string Farmacia::get_cod_postal() const {
    return codPostal;
}

void Farmacia::set_cod_postal(const std::string &cod_postal) {
    codPostal = cod_postal;
}

MediExpress * Farmacia::get_link_medi() const {
    return linkMedi;
}

void Farmacia::set_link_medi(MediExpress *link_medi) {
    linkMedi = link_medi;
}

void Farmacia::nuevoStock(PaMedicamento *pa, int n) {
    Stock *aux = new Stock(pa, n);

    std::set<Stock*>::iterator it;
    for (it=order.begin(); it!=order.end(); ++it) {
        if ((*it)->get_id_pa_med() == pa->get_id_num()) {
            (*it)->incrementa(n);
            break;
        }
    }
    if (it == order.end()) {
        order.insert(aux);
    }
}

bool Farmacia::eliminarStock(int id_num) {
    std::set<Stock*>::iterator it;
    for (it=order.begin(); it!=order.end(); ++it) {
        if ((*it)->get_id_pa_med() == id_num) {
            order.erase(it);
            return true;
        }
    }
    return false;
}

bool operator<(const Farmacia &lhs, const Farmacia &rhs) {
    return rhs.cif > lhs.cif;
}

bool operator<=(const Farmacia &lhs, const Farmacia &rhs) {
    return !(rhs.cif < lhs.cif);
}

bool operator>(const Farmacia &lhs, const Farmacia &rhs) {
    return rhs.cif < lhs.cif;
}

bool operator>=(const Farmacia &lhs, const Farmacia &rhs) {
    return !(lhs.cif < rhs.cif);
}

