//
// Created by Julio GR on 24/11/2022.
//

#include "ThashMedicam.h"

#include <iostream>
#include <ostream>

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

void ThashMedicam::redimensionar(bool expandir) {

    unsigned long tam_antiguo = tablah.size();
    unsigned long tam_nuevo;

    // CALCULAR NUEVO TAMAÑO
    if (expandir) {
        tam_nuevo = primomayFun(tam_antiguo * 2);
    } else {
        if (tam_antiguo < 20) return;
        tam_nuevo = primomenFun(tam_antiguo / 2);
    }

    // CREAR TABLA NUEVA VACÍA
    std::deque<Entrada> nueva_tabla(tam_nuevo);

    this->tamf = tam_nuevo;
    this->tablah.clear();
    this->tablah.resize(tam_nuevo);

    // Inicializar estados de la nueva tabla
    for (unsigned long i = 0; i < tam_nuevo; i++) {
        nueva_tabla[i].estado.libre = 1;
        nueva_tabla[i].estado.ocupado = 0;
        nueva_tabla[i].estado.disponible = 0;
    }

    // REHASHING
    for (unsigned long i = 0; i < tam_antiguo; i++) {

        // Solo movemos las casillas que están OCUPADAS (ignoramos libres y disponibles/borradas)
        if (tablah[i].estado.ocupado == 1) {

            unsigned long clave = tablah[i].clave;
            unsigned int intento = 0;
            bool insertado = false;

            // Bucle de resolución de colisiones en la NUEVA tabla
            while (!insertado) {
                unsigned int pos_nueva;

                // Seleccionamos la función hash según la configuración de la clase (th)
                if (this->th == 1) {
                    pos_nueva = hash1(clave, intento);
                } else if (this->th == 2) {
                    pos_nueva = hash2(clave, intento);
                } else {
                    pos_nueva = hash3(clave, intento);
                }

                if (nueva_tabla[pos_nueva].estado.libre == 1) {
                    // Copiar todos los datos de la casilla
                    nueva_tabla[pos_nueva] = tablah[i];

                    // Asegurar que los estados son correctos en la nueva
                    nueva_tabla[pos_nueva].estado.libre = 0;
                    nueva_tabla[pos_nueva].estado.ocupado = 1;
                    nueva_tabla[pos_nueva].estado.disponible = 0;

                    insertado = true;
                } else {
                    intento++; // Colisión en la nueva tabla, probamos siguiente salto
                }
            }
        }
    }

    // 4. ACTUALIZAR LA CLASE
    tablah = nueva_tabla; // El vector viejo se destruye aquí
    // taml (cantidad de elementos) se queda igual, no cambia.
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

    unsigned int hash;

    hash = ((clave) + n*(clave*5)) % tamf;

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
      //  if (this) { delete[] this; }

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
            else
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

            modificador++;
        }
    }
}

bool ThashMedicam::borra(unsigned long clave) {
    int modificador = 0;
    unsigned int hasheo;

    while (true) {
        // 1. Calcular Hash según la configuración actual
        if (th == 1)
            hasheo = hash1(clave, modificador);
        else if (th == 2)
            hasheo = hash2(clave, modificador);
        else
            hasheo = hash3(clave, modificador);

        // Referencia rápida a la celda actual
        Entrada &celda = tablah.at(hasheo);

        if (celda.estado.libre == 1) {
            return false;
        }

        // ENCONTRADO (Coincide clave y está ocupado)
        if (celda.estado.ocupado == 1 && celda.clave == clave) {

            // Borrado lógico (Lazy Deletion)
            celda.estado.ocupado = 0;
            celda.estado.disponible = 1; // Marcamos como "hueco sucio"
            // No tocamos 'libre', sigue siendo 0

            taml--; // Decrementamos número de elementos

            // REDIMENSIÓN (SHRINK)
            if (tamf > 50 && (float)taml / tamf < 0.2) {
                redimensionar(false);
            }

            return true;
        }

        modificador++;

        if (modificador > tamf) return false;
    }
}

void ThashMedicam::set_th(int th) {
    this->th = th;
}

void ThashMedicam::set_tamf(unsigned long tamf) {
    this->tamf = tamf;
}

