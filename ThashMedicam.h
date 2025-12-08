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

    int th=2;
    unsigned long tamf=0;
    unsigned long taml=0;
    unsigned long num_max_col=0;
    unsigned long sumacol=0;
    unsigned long max10=0;
    unsigned long primomen=0;
    deque<Entrada> tablah;

    //Parejas
    double lambdaMax = 0.75;
    unsigned int redisps = 0;

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

    void redimensionar(bool expandir);

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
    unsigned long djb22(const std::string &cad){return djb2(cad);};


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
    float getFactorCarga()const{return (float)taml / (float)tamf;;}; // NOLINT
    float getPromedioColisiones()const{return (float)sumacol / (float)taml;}; // NOLINT
    unsigned int getMax10()const{return max10;};

    void set_th(int th);

    void set_tamf(unsigned long tamf);

    //parejas
    void redispersar(unsigned long nuevoTam);
    void setLambda(double lambda) { lambdaMax = lambda; }
    double getLambda() const { return lambdaMax; }
    unsigned int getRedisps() const { return redisps; }
};


#endif //PRACTICA3_THASHMEDICAM_H
