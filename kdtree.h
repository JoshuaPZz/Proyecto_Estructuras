#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <cmath>
#include "kdnodo.h"

template<class T>
class kdtree {
protected:
    kdnodo<T>* raiz;

public:
    kdtree();
    bool esVacio();
    T& datoRaiz();
    int altura();
    int tamano();
    void insertar(Vertices& vertice);
    bool eliminar(std::vector<T>& val);
    kdnodo<T>* buscar(std::vector<T>& val);
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
    void maximo(int &maxi);
    void minimo(int &mini);
    double distanciaEuclidiana(Vertices& puntoFig, const std::vector<float>& puntoComp);
    Vertices encontrarMasCercano( Vertices& punto_buscado, double& menor_distancia);

private:
    kdnodo<T>* insertarRec(kdnodo<T>* nodo, Vertices& vertice, int profundidad);
    void encontrarMasCercanoRec(kdnodo<T>* nodo, const std::vector<float>& punto, double& menor_distancia, Vertices& vertice_cercano);
};

#include "kdtree.hxx"
#endif
