#ifndef FIGURAS_H
#define FIGURAS_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include "Caras.h"
#include "kdtree.h"
using namespace std;

struct Figuras {
private:
  string nombre;
  long int nvertices;
  list<Vertices> lvertices;
  list<Caras> lcaras;
  kdtree<Vertices> arbol;


public:
  Figuras();
  Figuras(const string &nombre, int nvertices, const list<Vertices> &lvertices, const list<Caras> &lcaras);

  Figuras CargarFigura(const string &);
  void MostrarListado(list<Figuras> &);
  void GuardarFigura(const string &, const string &, list<Figuras> &);
  void Descargar(const string &, list<Figuras> &);
  void Envolvente (list<Figuras> &,const string &);
  void Vcercano(list<Figuras>,const string &,const string &,const string &,const string &);
  void insertarVerticeArbol(Vertices& v);
  void Vcercano_Caja(list<Figuras> & figura,const string & nombre);


  string ObtenerNombre() const;
  int ObtenerNVertices() const;
  list<Vertices> ObtenerVertices() const;
  list<Caras> ObtenerCaras() const;



  void FijarNombre(const string &nombre);
  void FijarNVertices(int nvertices);
  void FijarVertices(const list<Vertices> &lvertices);
  void FijarCaras(const list<Caras> &lcaras);
};

#endif // FIGURAS_H