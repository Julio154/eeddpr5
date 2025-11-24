//
// Created by silvi on 28/09/2025.
//

#include "PaMedicamento.h"

/** @brief Constructor por defecto */
PaMedicamento:: PaMedicamento() = default;

/**
 * @brief Constructor parametrizado
 * @param id_num id numérico
 * @param id_alpha id alfanumérico
 * @param nombre nombre del medicamento
 */
PaMedicamento::PaMedicamento(int id_num, const std::string &id_alpha, const std::string &nombre)
        : id_num(id_num),
          id_alpha(id_alpha),
          nombre(nombre) {
}
/** @brief Destructor */
PaMedicamento::~PaMedicamento() = default;
int PaMedicamento::get_id_num() const {
    return id_num;
}

/**
 * @brief Setter del id numérico
 * @param id_num id numérico
 */
void PaMedicamento::set_id_num(int id_num) {
    this->id_num = id_num;
}

/**
 * @brief Getter del id alfanumérico
 * @return id alfanumérico
 */
std::string PaMedicamento::get_id_alpha() const {
    return id_alpha;
}

/**
 * @brief Setter del id alfanumérico
 * @param id_alpha id alfanumérico
 */
void PaMedicamento::set_id_alpha(const std::string &id_alpha) {
    this->id_alpha = id_alpha;
}

/**
 * @brief Getter del nombre del medicamento
 * @return nombre del medicamento
 */
std::string PaMedicamento::get_nombre() const {
    return nombre;
}

/**
 * @brief Setter del nombre del medicamento
 * @param nombre nombre del medicamento
 */
void PaMedicamento::set_nombre(const std::string &nombre) {
    this->nombre = nombre;
}

void PaMedicamento::setLab(const Laboratorio lab) {
    this->lab=lab;
}

std::string PaMedicamento::servidoPor() {
    return lab.get_nombre_lab();
}

/**
 * @brief Sobrecarga del operador de igualdad
 * @param rhs objeto a comparar
 * @return true si son iguales, false en caso contrario
 */
bool PaMedicamento::operator==(const PaMedicamento &rhs) const {
    return id_num == rhs.id_num;
}

/**
 * @brief Sobrecarga del operador de desigualdad
 * @param rhs objeto a comparar
 * @return true si son diferentes, false en caso contrario
 */
bool PaMedicamento::operator!=(const PaMedicamento &rhs) const {
    return !(rhs == *this);
}

/**
 * @brief Sobrecarga del operador menor que
 * @param rhs objeto a comparar
 * @return true si el objeto actual es menor que el objeto a comparar, false en caso contrario
 */
bool PaMedicamento::operator<(const PaMedicamento &rhs) const {
    if (id_num < rhs.id_num)
        return true;

    return false;
}

/**
 * @brief Sobrecarga del operador mayor que
 * @param rhs objeto a comparar
 * @return true si el objeto actual es mayor que el objeto a comparar, false en caso contrario
 */
bool PaMedicamento::operator>(const PaMedicamento &rhs) const {
    return rhs < *this;
}

/**
 * @brief Sobrecarga del operador menor o igual que
 * @param rhs objeto a comparar
 * @return true si el objeto actual es menor o igual que el objeto a comparar, false en caso contrario
 */
bool PaMedicamento::operator<=(const PaMedicamento &rhs) const {
    return !(rhs < *this);
}

/**
 * @brief Sobrecarga del operador mayor o igual que
 * @param rhs objeto a comparar
 * @return true si el objeto actual es mayor o igual que el objeto a comparar, false en caso contrario
 */
bool PaMedicamento::operator>=(const PaMedicamento &rhs) const {
    return !(*this < rhs);
}

PaMedicamento &PaMedicamento::operator=(const PaMedicamento &v) {
id_num=v.id_num;
    id_alpha=v.id_alpha;
    nombre=v.nombre;
    return *this;;
}
