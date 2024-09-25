#include "Vertices.h"
using namespace std;

Vertices::Vertices() : indiceVert(0), coorX(0), coorY(0), coorZ(0) {}
Vertices::Vertices(int indiceVert, float coorX, float coorY, float coorZ)
    : indiceVert(indiceVert), coorX(coorX), coorY(coorY), coorZ(coorZ) {}

void Vertices::CargarVertice(ifstream& entrada, int& indice) {
    entrada >> coorX >> coorY >> coorZ;
    indiceVert = indice;
    indice++;
}

int Vertices::ObtenerIndice() const { return indiceVert; }

float Vertices::ObtenerCoorX()   { return coorX; }

float Vertices::ObtenerCoorY() const { return coorY; }

float Vertices::ObtenerCoorZ() const { return coorZ; }

void Vertices::FijarIndice(int indice) { indiceVert = indice; }

void Vertices::FijarCoorX(float coordenadaX) { coorX = coordenadaX; }

void Vertices::FijarCoorY(float coordenadaY) { coorY = coordenadaY; }

void Vertices::FijarCoorZ(float coordenadaZ) { coorZ = coordenadaZ; }
