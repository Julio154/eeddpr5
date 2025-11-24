//
// Created by silvi on 17/11/2025.
//

#ifndef PR1_STOCK_H
#define PR1_STOCK_H
#include "PaMedicamento.h"


class Stock {
private:
    PaMedicamento * medicamento_asociado;
    int id_PaMed = medicamento_asociado->get_id_num();
    int num_stock;

public:
    Stock();
    Stock(PaMedicamento *medicamento_asociado, int num_stock);

    ~Stock();

    void decrementa(int n);
    void incrementa(int n);

    int get_id_pa_med() const;
    void set_id_pa_med(const int id_pa_med);
    int get_num_stock() const;
    void set_num_stock(const int num_stock);
    PaMedicamento * get_medicamento_asociado() const;
    void set_medicamento_asociado(PaMedicamento * const medicamento_asociado);

    friend bool operator<(const Stock &lhs, const Stock &rhs);

};


#endif //PR1_STOCK_H