#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Laboratorio.h"
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "ThashMedicam.h"
#include "Farmacia.h"

/**
 * @authors Julio Gallegos Rojas jgr00087@red.ujaen.es
 * @author Silvia Cruz Román scr00043@red.ujaen.es
 */

/**
 * @brief funcion que nos muestra por pantalla un menu de opciones
 */
void menu2(){
    std::cout<<"------MENU-----"<<std::endl
    <<"1.Farmacias de Sevilla vayan 12 personas a comprar “ÓXIDO DE MAGNESIO” con ID=3640 y si no hay en stock "
<<"que compren “CARBONATO DE MAGNESIO” con ID=3632 y, si no, que compren "
<<"“CLORURO DE MAGNESIO” con ID=3633. Mostrar por pantalla el stock de cada medicamento mencionado en cada farmacia. "<<std::endl
            <<"2.Farmacias de Madrid que proporcianan VIRUS "<<std::endl
            <<"3.Eliminar medicamento con CIANURO , id= 9355 , su stock en farmacias. Buscar para comprobar. Eliminar id=3244"<<std::endl
            <<"4.PAREJAS: Incrementar 20u suministro de medicamento de virus para la gripe, id=997, para las farmacias de CoMadrid. Listar las que tengan mas de 30u"<<std::endl;
}
/**
 * @brief funcion que nos muestra la lista de enteros
 * @param lista
 */
void mostrarEnteros(std::list<int> *lista){
    int c=0;
    for (std::list<int> ::iterator it= lista->begin();c < lista->size() ; it++) {
        std::cout<<" - "<<*it<<"\t";
        c++;
    }
    std::cout<<std::endl;
}

void mostrarLaboratorios(std::list<Laboratorio> *lista){
    for (std::list<Laboratorio> ::iterator it= lista->begin();it!=lista->end() ; it++) {
        std::cout<<" - "<<it->get_nombre_lab()<<"\t"<<it->get_localidad()<<std::endl;
    }
    std::cout<<std::endl;
}
void cargarMedicamentos(ThashMedicam &medicam) {
    std::string id_number = "";
    std::string id_alpha="";
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    std::string nombre;

    is.open("../pa_medicamentos.csv"); //carpeta de proyecto
    //int c=0;
    if ( is.good() ) {
        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, id_number, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha,';');
                getline(columnas, nombre,';');

                fila="";
                columnas.clear();
                int idNumber=std::stoi(id_number);
                PaMedicamento medicamento(idNumber,id_alpha,nombre);
                //medication.push_back(medicamento);
                medicam.inserta(medicam.djb22(std::to_string(medicamento.get_id_num())),medicamento);
    //            c++;
  //              std::cout<<"Insertado dato "<<c<<std::endl;
//                std::cout<<"Dato "<<medicam.buscar(medicam.djb22(std::to_string(medicamento.get_id_num())))->get_nombre()<<std::endl;

            }
        }
    }
}

/**
 * @author Silvia Cruz Roman scr00043@red.ujaen.es
 */
int main(int argc, const char * argv[]) {
    try{

        int opcion;
        MediExpress medi_express("../farmacias.csv","../pa_medicamentos.csv","../lab2.csv");

        ThashMedicam medicam068_1(3310, 0.68, 1);


        ThashMedicam medicam068_2(3310, 0.68, 2);
        cargarMedicamentos(medicam068_2);
        ThashMedicam medicam068_3(3310, 0.68, 3);
        cargarMedicamentos(medicam068_3);


        ThashMedicam medicam065_1(3310, 0.68, 1);
        cargarMedicamentos(medicam065_1);
        ThashMedicam medicam065_2(3310, 0.68, 2);
        cargarMedicamentos(medicam065_2);
        ThashMedicam medicam065_3(3310, 0.68, 3);
        cargarMedicamentos(medicam065_3);


        medi_express.set_id_medication(medicam068_1);
        medi_express.mostrarEstadoTabla();
        medi_express.set_id_medication(medicam068_2);
        medi_express.mostrarEstadoTabla();

        medi_express.set_id_medication(medicam068_3);
        medi_express.mostrarEstadoTabla();


        medi_express.set_id_medication(medicam065_1);
        medi_express.mostrarEstadoTabla();

        medi_express.set_id_medication(medicam065_2);
        medi_express.mostrarEstadoTabla();

        medi_express.set_id_medication(medicam065_3);
        medi_express.mostrarEstadoTabla();


       /* std::vector<PaMedicamento*> meds_sin_lab = medi_express.getMedicamSinLab();
        std::list<Laboratorio> labs_madrid2 = medi_express.buscarLabSoloCiudad("Madrid");

        std::cout << "Medicamentos sin laboratorio antes de: " << meds_sin_lab.size() << std::endl;
        std::cout << "Laboratorios en Madrid: " << labs_madrid2.size() << std::endl;

        int contador2 = 0;

        for (std::list<Laboratorio>::iterator it = labs_madrid2.begin();
             it != labs_madrid2.end() && contador2 < meds_sin_lab.size();
             ++it) {
            if (contador2 < meds_sin_lab.size()) {
                meds_sin_lab[contador2]->setLab(*it);
                contador2++;
            }
             }

        std::map<std::string,Farmacia> *farmacias = medi_express.get_pharmacy();

        do {
            menu2();
            std::cin>>opcion;
            switch (opcion) {
                case 1: {
                    std::cout<<"1.Farmacias de Sevilla vayan 12 personas a comprar “ÓXIDO DE MAGNESIO” con ID=3640 y si no hay en stock "
                    <<"que compren “CARBONATO DE MAGNESIO” con ID=3632 y, si no, que compren "
                    <<"“CLORURO DE MAGNESIO” con ID=3633. Mostrar por pantalla el stock de cada medicamento mencionado en cada farmacia. "<<std::endl<<std::endl;

                    std::vector<Farmacia*> farSevilla=medi_express.buscarFarmacias("SEVILLA");
                    PaMedicamento aux;
                    for (int i=0;i<farSevilla.size();i++) {
                        for (int j=0;j<12;j++){
                            std::cout<<"Farmacia: "<<farSevilla[i]->get_nombre()<<std::endl;
                            if (farSevilla[i]->comprarMedicam(3640,1,aux)==0) {
                                std::cout<<" no hay stock de oxido de magnesio"<<std::endl;
                                if (farSevilla[i]->comprarMedicam(3632,1,aux)==0) {
                                    std::cout<<" no hay stock de CARBONATO DE MAGNESIO"<<std::endl;
                                    if (farSevilla[i]->comprarMedicam(3633,1,aux)==0) {
                                        std::cout<<" no hay stock de CLORURO DE MAGNESIO"<<std::endl;
                                    }else {
                                        std::cout<<"Compra 1 CLORURO DE MAGNESIO"<<std::endl;
                                        std::cout<<"Stock restante:"<<farSevilla[i]->buscaMedicamID(3633)<<std::endl;
                                    }
                                }else {
                                    std::cout<<"Compra 1 CARBONATO DE MAGNESIO"<<std::endl;
                                    std::cout<<"Stock restante:"<<farSevilla[i]->buscaMedicamID(3632)<<std::endl;
                                }
                            }else {
                                std::cout<<"Compra 1 OXIDO DE MAGNESIO"<<std::endl;
                                std::cout<<"Stock restante:"<<farSevilla[i]->buscaMedicamID(3640)<<std::endl;
                            }
                        }
                    }
                    break;
                    }

                    case 2: {
                    std::cout<<"2.Farmacias de Madrid que proporcionan VIRUS "<<std::endl;
                    std::vector<Farmacia*> farMadrid=medi_express.buscarFarmacias("MADRID");
                    std::cout<<"Se han encontrado "<<farMadrid.size()<<" farmacias en Madrid"<<std::endl;
                    int cFarMadVirus=0;
                    for (int i=0;i<farMadrid.size();i++) {
                        if (!farMadrid[i]->buscaMedicamNombre("VIRUS").empty()){
                            cFarMadVirus++;
                        }
                    }
                    std::cout<<"Hay un total de "<<cFarMadVirus<<" que dispensan VIRUS en Madrid"<<std::endl;
                    break;
                    }
                    case 3: {
                    std::cout<<"3.Eliminar medicamento con CIANURO , id= 9355 , su stock en farmacias. Buscar para comprobar. Eliminar id=3244"<<std::endl;

                    int idsABorrar[] = {9355, 3244};

                        for (int id : idsABorrar) {
                            std::cout << "\n--- Eliminando medicamento: " << id << " ---" << std::endl;

                            // A) COMPROBACIÓN PREVIA (¿Existe antes de borrar?)
                            PaMedicamento* ptrPre = medi_express.buscarCompuesto(id);
                            if (ptrPre != nullptr) {
                                std::cout << "VERIFICACION PREVIA: El medicamento SI existe en el sistema." << std::endl;
                            } else {
                                std::cout << "VERIFICACION PREVIA: El medicamento NO existe (o ya fue borrado)." << std::endl;
                            }

                            std::cout << ">> Llamando a eliminarTotalmente(" << id << ")..." << std::endl;
                            bool resultado = medi_express.eliminarMedicamento(id);

                            if (resultado) {
                                std::cout << ">> La funcion retorno TRUE (Borrado correcto)." << std::endl;
                            } else {
                                std::cout << ">> La funcion retorno FALSE (No encontrado)." << std::endl;
                            }

                            PaMedicamento* ptrPost = medi_express.buscarCompuesto(id);
                            if (ptrPost == nullptr) {
                                std::cout << "EXITO: El medicamento ya no aparece en las busquedas de MediExpress." << std::endl;
                            } else {
                                std::cout << "ERROR: El medicamento sigue apareciendo en MediExpress." << std::endl;
                            }

                            if (!farmacias->empty()) {
                                Farmacia& f = farmacias->begin()->second;
                                int stock = f.buscaMedicamID(id);
                                if (stock == 0) {
                                    std::cout << "VERIFICACION STOCK: En farmacia '" << f.get_nombre() << "' el stock es 0 (Correcto)." << std::endl;
                                } else {
                                    std::cout << "ALERTA: La farmacia '" << f.get_nombre() << "' aun tiene " << stock << " unidades!" << std::endl;
                                }
                            }
                        }

                    break;
                    }
                    case 4: {
                    std::cout<<"4.PAREJAS: Incrementar 20u suministro de medicamento de virus para la gripe, id=997, para las farmacias de CoMadrid. Listar las que tengan mas de 30u"<<std::endl;
                    const int ID_GRIPE = 997;
                    const int INCREMENTO = 20;
                    // El stock inicial es 10 (de suministrarMed) + 20 (de ahora)
                    const int STOCK_FINAL_BUSCADO = 30;

                    // 1. Buscamos el objeto PaMedicamento* con ID 997
                    PaMedicamento* medGripe = medi_express.buscarCompuesto(ID_GRIPE);

                    if (medGripe == nullptr) {
                        std::cerr << "Error: No se pudo encontrar el medicamento con ID " << ID_GRIPE << std::endl;
                        break;
                    }

                    // 2. Recorremos el mapa de farmacias
                    for (std::map<std::string, Farmacia>::iterator it = farmacias->begin(); it != farmacias->end(); ++it) {

                        // it->second es el objeto Farmacia

                        // CORREGIDO: Pasamos el puntero 'medGripe', NO el objeto '*medGripe'
                        it->second.nuevoStock(medGripe, INCREMENTO);
                    }

                    std::cout << "Incremento completado." << std::endl;

                    // 3. Listar las farmacias que ahora tengan 30 unidades
                    std::cout << "--- Farmacias con " << STOCK_FINAL_BUSCADO << " unidades de ID " << ID_GRIPE << " ---" << std::endl;

                    int farmaciasEncontradas = 0;

                    // Volvemos a recorrer el mapa para comprobar
                    for (std::map<std::string, Farmacia>::iterator it = farmacias->begin(); it != farmacias->end(); ++it) {

                        Farmacia& farmaciaActual = it->second;

                        // Usamos buscaMedicamID (que ahora es público)
                        int stockActual = farmaciaActual.buscaMedicamID(ID_GRIPE);

                        if (stockActual == STOCK_FINAL_BUSCADO) {
                            std::cout << " - " << farmaciaActual.get_nombre()
                                      << " (CIF: " << farmaciaActual.get_cif() << ")" << std::endl;
                            farmaciasEncontradas++;
                        }
                    }

                    if (farmaciasEncontradas == 0) {
                        std::cout << "Ninguna farmacia encontrada con " << STOCK_FINAL_BUSCADO << " unidades." << std::endl;
                    }

                    std::cout << "------------------------------------------" << std::endl;
                    break;
                    }

                }
        }while(opcion>0 && opcion<5);*/
    } catch (std::exception) {
            std::cerr<<"ERROR";
    }
     return 0;
}