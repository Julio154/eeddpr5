//
// Created by silvi on 17/11/2025.
//

#include "Stock.h"

Stock::Stock() {
}

Stock::Stock(PaMedicamento *medicamento_asociado,int num_stock)
    : id_PaMed(medicamento_asociado->get_id_num()),
      medicamento_asociado(medicamento_asociado),
      num_stock(num_stock)
{}

Stock::~Stock() {
}

void Stock::decrementa(int n) {
    num_stock=num_stock-n;
}

void Stock::incrementa(int n) {
    num_stock=num_stock+n;
}

int Stock::get_id_pa_med() const {
    return id_PaMed;
}

void Stock::set_id_pa_med(const int id_pa_med) {
    id_PaMed = id_pa_med;
}

int Stock::get_num_stock() const {
    return num_stock;
}

void Stock::set_num_stock(const int num_stock) {
    this->num_stock = num_stock;
}

PaMedicamento * Stock::get_medicamento_asociado() const {
    return medicamento_asociado;
}

void Stock::set_medicamento_asociado(PaMedicamento * const medicamento_asociado) {
    this->medicamento_asociado = medicamento_asociado;
}

 bool operator<(const Stock &lhs, const Stock &rhs) {
    return lhs.id_PaMed < rhs.id_PaMed;
}
