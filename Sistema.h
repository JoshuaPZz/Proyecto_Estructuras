#ifndef SISTEMA_H
#define SISTEMA_H

#include "Comandos.h"
#include "Figuras.h"
#include <list>
#include <string>
#include <vector>

class Sistema {
private:
    std::vector<Comandos> comandos;
    std::list<Figuras> figura;
    bool salida;
    void leerEntrada();
    void mostrarAyuda(const std::string& argumento1);
public:
    Sistema();
    void Iniciar();

};

#endif // SISTEMA_H