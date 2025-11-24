//
// Created by Julio GR on 24/11/2022.
//

#include "ThashMedicam.h"

bool ThashMedicam::esprimo(int n) {

    for (int div = 2; div < (n/2); ++div) {
        if (!(n % div)) {
            return false;
        }
    }
    return true;
}

unsigned long ThashMedicam::primomenFun(int n) {
    unsigned long nuevoprimo = n-1; //no pilla el -- porque eso modificaría n y no esta pasado por ref

    while(esprimo(nuevoprimo) == false){
        nuevoprimo--;
    }
    return nuevoprimo;
}

unsigned long ThashMedicam::primomayFun(int n) {
    unsigned long nuevoprimo = n+1;

    while(esprimo(nuevoprimo) == false){
        nuevoprimo++;
    }
    return nuevoprimo;
}

//Cuadratica modificada.
unsigned int ThashMedicam::hash1(unsigned long clave, int n) const{

    unsigned int hash;
    unsigned long n2=(long)pow(n,3);

    hash = ((clave + n2 )% tamf);

    return hash;
}

//Inventada 1
unsigned int ThashMedicam::hash2(unsigned long clave, int n) const{

    unsigned int hash = (int)pow(clave,2);

    hash = (hash * (n/2))%tamf;

    return hash;
}

//Inventada 2
unsigned int ThashMedicam::hash3(unsigned long clave, int n) const{

    unsigned int hash;
    unsigned long hasheada = (long)(exp(n) - pow(n, 3));

    hash = ((clave + hasheada) % tamf);

    return hash;
}

/**
 * @brief Constructor parametrizado
 * @param tamaño Lo usaremos para construir la tabla
 * @param lambda parametro para dispersar
 * @param tth tabla hash
 */
//col means colision
ThashMedicam::ThashMedicam(unsigned long tamano, double lambda, int tth) :
        th(tth), tamf(dTamaf(tamano, lambda)), taml(0), num_max_col(0), sumacol(0),
        primomen(dTamaf(tamano, lambda)), tablah(dTamaf(tamano, lambda), Entrada()),max10(0)
{}

ThashMedicam::ThashMedicam(const ThashMedicam &orig) :
        th(orig.th), tamf(orig.tamf), taml(orig.taml), num_max_col(orig.num_max_col),
        sumacol(orig.sumacol), primomen(orig.primomen), tablah(orig.tablah),max10(orig.max10)
{}

ThashMedicam &ThashMedicam::operator=(const ThashMedicam &orig) {

    if(this != &orig){
        if (this) { delete[] this; }

        th = orig.th;
        tamf = orig.tamf;
        taml = orig.taml;
        num_max_col = orig.num_max_col;
        sumacol = orig.sumacol;
        primomen = orig.primomen;
        tablah = orig.tablah;
        max10 = orig.max10;
    }
    return *this;
}

bool ThashMedicam::inserta(unsigned long clave, const PaMedicamento &dato) {

    int modificador=0;
    unsigned int hasheo;
    char sigue = 0;

    while(sigue != 1){
        if(this->th==1)
            hasheo= hash1(clave,modificador);
        if(this->th==2)
            hasheo= hash2(clave,modificador);
        if(this->th==3)
            hasheo= hash3(clave,modificador);

        if(tablah.at(hasheo).estado.libre == 1 || tablah.at(hasheo).estado.disponible == 1){
            tablah.at(hasheo).dato=dato;
                tablah.at(hasheo).estado.disponible=0; //ESTADO
                tablah.at(hasheo).estado.libre=0;
                tablah.at(hasheo).estado.ocupado=1;
            tablah.at(hasheo).clave=clave;
            taml++;

            sigue=1;
        }
        else{
            if(tablah.at(hasheo).dato == dato)
                return false;

            modificador++;
        }

    }

    sumacol+=modificador;
    if(modificador > num_max_col)
        this->num_max_col=modificador;
    if(modificador > 10)
        this->max10++;

    return true;
}

PaMedicamento *ThashMedicam::buscar(unsigned long clave) {

    int modificador=0;
    unsigned int hasheo;
    char sigue = 0;

    while(sigue != 1){
        if(this->th==1)
            hasheo=hash1(clave,modificador);
        if(this->th==2)
            hasheo=hash2(clave,modificador);
        if(this->th==3)
            hasheo=hash3(clave,modificador);

        if(tablah.at(hasheo).estado.ocupado == 1 && tablah.at(hasheo).clave == clave){
            return &tablah.at(hasheo).dato;
        }
        else{
            if(tablah.at(hasheo).estado.libre == 1)
                return nullptr;
            else
                modificador++;
        }
    }

    return nullptr;
}

bool ThashMedicam::borra(unsigned long clave) {
    int modificador=0;
    unsigned int hasheo;
    char sigue = 0;

    while(sigue != 1) {
        if (this->th == 1)
            hasheo = hash1(clave, modificador);
        if (this->th == 2)
            hasheo = hash2(clave, modificador);
        if (this->th == 3)
            hasheo = hash3(clave, modificador);

        if(tablah.at(hasheo).clave == clave && tablah.at(hasheo).estado.ocupado == 1){
            tablah.at(hasheo).estado.ocupado=0;
            tablah.at(hasheo).estado.disponible=1;

            taml--;
            sigue=1;
        }
        else{
            if(tablah.at(hasheo).estado.libre == 1){
                return false;
            }
            else{
                modificador++;
            }
        }
    }
    return true;
}

