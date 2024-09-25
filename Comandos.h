#ifndef COMANDOS_H
#define COMANDOS_H

#include "Figuras.h"
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
using namespace std;

struct Comandos {
private:
  string nombrede;
  string descripcion;

public:
  Comandos();
  Comandos(const string &nombrede, const string &descripcion);
  void leerComandos(vector<Comandos> &);
  bool validarArgumentos(const string &, int, const string &, const string &,const string &, const string &,list<Figuras> &);
  void mostrarMensajeFaltanArgumentos(const string &);
  string ObtenerNombrede() const;
  string ObtenerDescripcion() const;
  void FijarNombrede(const string &nombrede);
  void FijarDescripcion(const string &descripcion);
};

#endif // COMANDOS_H
