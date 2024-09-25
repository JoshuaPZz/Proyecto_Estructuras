#ifndef VERTICES_H
#define VERTICES_H

#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Vertices{
private: 
  int indiceVert;
  float coorX;
  float coorY;
  float coorZ;

public:
  Vertices();
  Vertices(int indiceVert, float coorX, float coorY, float coorZ);
  void CargarVertice(ifstream& entrada, int&);
  int ObtenerIndice() const;
  float ObtenerCoorX();
  float ObtenerCoorY() const;
  float ObtenerCoorZ() const;
  void FijarIndice(int indice);
  void FijarCoorX(float coordenadaX);
  void FijarCoorY(float coordenadaY);
  void FijarCoorZ(float coordenadaZ);

};


#endif // VERTICES_H
