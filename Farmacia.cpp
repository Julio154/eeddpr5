//
// Created by silvi on 25/10/2025.
//


#include "Farmacia.h"

#include <iostream>

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
/*
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
    if (num_med_disp >= n) {
        Stock *aux;
        for (auto it = order.begin(); it != order.end(); ++it) {
            if ((*it).second->get_id_pa_med() == id_num) {
                aux = (*it).second;
                break;
            }
        }
        aux->decrementa(n);
    }else {
       // pedidoMedicam(id_num, 10);
    }

    return num_med_disp;
}

int Farmacia::buscaMedicamID(int id_num) {

    auto it = order.find(id_num);
    if (it != order.end()) {
            return it->second->get_num_stock();
    } else {
        return 0;
    }


/*    if (it != order.end()) {
        if (  it->second->get_num_stock()>0) {
            it->second->decrementa(1);
            cout<<"Se ha realizado una venta de medicamento"<<endl;
            return it->second->get_num_stock();
        }else {
            it->second->incrementa(10);
            cout<<"Se ha realizado un pedido de 10u "<<endl;
            return it->second->get_num_stock();
        }
    } else {
        return 0;
    }*/
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
    const int id = pa->get_id_num();
    map<int,Stock*>::iterator it = order.find(id);
    if (it != order.end()) {
        it->second->incrementa(n);
    } else {
        order.insert({id, new Stock(pa, n)});
    }
}

bool Farmacia::eliminarStock(int id_num) {
    map<int,Stock*>::iterator it = order.find(id_num);
    if (it == order.end()) {
        return false;
    }

    order.erase(it);
    return true;
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

