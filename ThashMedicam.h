//
// Created by Julio GR on 24/11/2025.
//

#ifndef PRACTICA3_THASHMEDICAM_H
#define PRACTICA3_THASHMEDICAM_H

#include "PaMedicamento.h"
#include <deque>
#include <algorithm>
#include <cmath>
using namespace std;

struct Estado{
    char libre=1, ocupado=0, disponible=0;
    Estado() = default;
    ~Estado(){};
};

class ThashMedicam {
private:
    class Entrada{
    public:
        unsigned long clave;
        Estado estado;
        PaMedicamento dato;
        Entrada(): estado(),clave(0),dato(PaMedicamento()){};
        ~Entrada(){};
    };

    int th=0;
    unsigned long tamf=0;
    unsigned long taml=0;
    unsigned long num_max_col=0;
    unsigned long sumacol=0;
    unsigned long max10=0;
    unsigned long primomen=0;
    deque<Entrada> tablah;

    unsigned long djb2(const string &cad){
        unsigned long hash = 5381;
        for (auto c : cad) {
            hash = ((hash << 5) + hash + c);
        }
        return hash;
    }

    bool esprimo(int n);
    unsigned long primomenFun(int n);
    unsigned long primomayFun(int n);

    unsigned int hash1(unsigned long clave, int n)const;//Función de dispersión básica
    unsigned int hash2(unsigned long clave, int n)const;
    unsigned int hash3(unsigned long clave, int n)const;
    unsigned long dTamaf(unsigned long tam, double lambda){
        return primomayFun((unsigned long)(tam/lambda)); // NOLINT
    };

public:
    ThashMedicam() = default;
    ThashMedicam(unsigned long tamano, double lambda, int tth);
    ThashMedicam(const ThashMedicam &orig);
    ~ThashMedicam() = default;
    ThashMedicam &operator=(const ThashMedicam &orig);

    bool inserta(unsigned long clave, const PaMedicamento &dato);
    PaMedicamento *buscar(unsigned long clave);
    bool borra(unsigned long clave);

    //gets respectivos
    unsigned long getTaml()const {return taml;};
    unsigned long getTamf()const {return tamf;};
    unsigned long getColisiones()const {return num_max_col;};
    unsigned long getSumaColisiones()const{return sumacol;};
    unsigned long getPrimomenor()const{return primomen;};

    //gets para el .md
    float getFactorCarga()const{return (float)(taml/tamf);}; // NOLINT
    float getPromedioColisiones()const{return (float)(sumacol/taml);}; // NOLINT
    unsigned int getMax10()const{return max10;};

};


#endif //PRACTICA3_THASHMEDICAM_H
