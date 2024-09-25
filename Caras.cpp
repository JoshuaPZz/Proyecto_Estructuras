#include "Caras.h"
using namespace std;

Caras::Caras() : cantVertices(0) {}

Caras::Caras(int cantVertices, const vector<int> &indiceVertices)
    : cantVertices(cantVertices), indiceVertices(indiceVertices) {}

int Caras::obtenerCantidadVertices() const { return cantVertices; }

vector<int> Caras::obtenerIndiceVertices() const { return indiceVertices; }

void Caras::fijarCantidadVertices(int cantidadVertices) {
  cantVertices = cantidadVertices;
}

void Caras::fijarIndiceVertices(const vector<int> &indiceVertices) {
  this->indiceVertices = indiceVertices;
}
void Caras::CargarCara(ifstream& entrada) {
    entrada >> cantVertices;
    indiceVertices.clear();
    for (int i = 0; i < cantVertices; ++i) {
        int indiceVertice;
        entrada >> indiceVertice;
        indiceVertices.push_back(indiceVertice);
    }
}