#ifndef CARAS_H
#define CARAS_H

#include "Vertices.h"
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Caras {
private:
  int cantVertices;
  vector<int> indiceVertices;

public:
  Caras();
  Caras(int cantVertices, const vector<int> &indiceVertices);

  int obtenerCantidadVertices() const;
  vector<int> obtenerIndiceVertices() const;

  void fijarCantidadVertices(int cantidadVertices);
  void fijarIndiceVertices(const vector<int> &indiceVertices);

  void CargarCara(ifstream& entrada);
};

#endif // CARAS_H
