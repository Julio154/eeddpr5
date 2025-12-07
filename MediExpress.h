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
#include "ThashMedicam.h"


class MediExpress
{
    private:
        std::list<Laboratorio> labs;
        std::multimap<std::string,Farmacia> pharmacy;
        std::multimap<std::string,PaMedicamento*> nombMedication;
        ThashMedicam idMedication; //Clave id del PaMedicamento
        std::vector<int> vMedi;
    public:
        ThashMedicam get_id_medication() const;

        void set_id_medication(const ThashMedicam &id_medication);

        // Una estructura trabaja con los pamedicamentos por clave string que sera
        // su nombre y el otro por su id (el cual se usará para alojarlo en la estructura)

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
        std::set<PaMedicamento*> buscarCompuesto(std::string comp); // Busca en el multimap
        PaMedicamento *buscarCompuesto(int id_num); // Busca en la tabla hash
        std::vector<PaMedicamento*> getMedicamSinLab();

        std::list<Laboratorio>& get_labs() ;

        void set_labs(const std::list<Laboratorio> &labs);

        std::vector<PaMedicamento*> get_medication();

         //para enlazar un medicamento a una farmacia
        std::vector<Farmacia*> buscarFarmacias(std::string nombre);
        void suministrarFarmacia(Farmacia &f, int id_num, int n);
        std::list<Laboratorio*> buscarLabs(PaMedicamento med);

        std::map<std::string,Farmacia> *get_pharmacy();

        bool eliminarMedicamento(int id_num);
        unsigned int maxColisiones();

        unsigned int numMax10();

        unsigned int promedioColisiones();

        float factorCarga();

        void mostrarEstadoTabla();
};


#endif //PR1_MEDIEXPRESS_H