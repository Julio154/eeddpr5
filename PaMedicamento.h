//
// Created by silvi on 28/09/2025.
//

#ifndef PR1_2526_PAMEDICAMENTO_H
#define PR1_2526_PAMEDICAMENTO_H
#include <string>

#include "Laboratorio.h"

/**
 * @brief Clase PaMedicamento que representa un medicamento con atributos id_num, id_alpha y nombre.
 */
class PaMedicamento {
private:
    int id_num;
    std::string id_alpha;
    std::string nombre;
    Laboratorio *lab;

public:
    /**
     * @brief Constructor por defecto y parametrizado
     */
    PaMedicamento();
    PaMedicamento(int id_num, const std::string &id_alpha, const std::string &nombre);
    /**
     * @brief Destructor
     */
    ~PaMedicamento();

    /**
     * Getters y Setters
     */
    int get_id_num() const;
    void set_id_num(int id_num);
    std::string get_id_alpha() const;
    void set_id_alpha(const std::string &id_alpha);
    std::string get_nombre() const;
    void set_nombre(const std::string &nombre);
    void setLab(Laboratorio &lab);
    std::string servidoPor();

    /** Sobrecarga de operadores para comparar objetos PaMedicamento */
    bool operator==(const PaMedicamento &rhs) const;
    bool operator!=(const PaMedicamento &rhs) const;
    bool operator<(const PaMedicamento &rhs) const;
    bool operator>(const PaMedicamento &rhs) const;
    bool operator<=(const PaMedicamento &rhs) const;
    bool operator>=(const PaMedicamento &rhs) const;

    PaMedicamento &operator=(const PaMedicamento &v);



};


#endif //PR1_2526_PAMEDICAMENTO_H