//
// Created by silvi on 18/10/2025.
//

#ifndef PR1_LABORATORIO_H
#define PR1_LABORATORIO_H
#include <string>


class Laboratorio {
    private:
        int id;
        std::string nombreLab;
        std::string direccion;
        std::string codPostal;
        std::string localidad;

    public:

        Laboratorio();

        Laboratorio(const Laboratorio &otro);

        Laboratorio(int id, const std::string &nombre_lab, const std::string &direccion, const std::string &cod_postal,
                    const std::string &localidad);

        ~Laboratorio();

        int get_id() const;

        void set_id(int id);

        std::string get_nombre_lab() const;

        void set_nombre_lab(const std::string &nombre_lab);

        std::string get_direccion() const;

        void set_direccion(const std::string &direccion);

        std::string get_cod_postal() const;

        void set_cod_postal(const std::string &cod_postal);

        std::string get_localidad() const;

        void set_localidad(const std::string &localidad);
        Laboratorio &operator=(const Laboratorio &v);
};


#endif //PR1_LABORATORIO_H