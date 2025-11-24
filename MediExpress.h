//
// Created by silvi on 18/10/2025.
//

#ifndef PR1_MEDIEXPRESS_H
#define PR1_MEDIEXPRESS_H
#include "map"
#include "Farmacia.h"
#include "Laboratorio.h"
#include "list"
#include "PaMedicamento.h"
#include "vector"


class MediExpress
{
    private:
        std::list<Laboratorio> labs;
        std::vector<PaMedicamento> medication;
        std::map<std::string,Farmacia> pharmacy;
    public:
        MediExpress();
        ~MediExpress();

        MediExpress(const std::map<std::string,Farmacia> &pharmacy);

        MediExpress(const std::list<Laboratorio> &labs, const std::vector<PaMedicamento> &medication);

        MediExpress(const std::list<Laboratorio> &labs, const std::vector<PaMedicamento> &medication, const std::map<std::string,Farmacia> &pharmacy);

        MediExpress(std::string fichero1, std::string fichero2, std::string fichero3);

        MediExpress(const MediExpress &orig);

        void suministrarMed();
        Laboratorio* buscarLab(std::string nombreLab);

        std::list<Laboratorio*> buscarLabCiudad(std::string nombreCiudad);
        std::list<Laboratorio*> buscarLabSoloCiudad(std::string nombreCiudad);
        std::vector<PaMedicamento*> buscarCompuesto(std::string comp);
        std::vector<PaMedicamento*> getMedicamSinLab();

        std::list<Laboratorio>& get_labs() ;

        void set_labs(const std::list<Laboratorio> &labs);

        std::vector<PaMedicamento*> get_medication();

        PaMedicamento *buscarCompuesto(int id_num); //para enlazar un medicamento a una farmacia
        std::vector<Farmacia*> buscarFarmacias(std::string nombre);
        void suministrarFarmacia(Farmacia &f, int id_num, int n);
        std::list<Laboratorio*> buscarLabs(PaMedicamento med);

        std::map<std::string,Farmacia> *get_pharmacy();

        bool eliminarMedicamento(int id_num);

};


#endif //PR1_MEDIEXPRESS_H