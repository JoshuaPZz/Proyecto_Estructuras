#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <cmath>
#include "kdnodo.h"

template <typename T>
class kdtree {
protected:
    kdnodo<T>* raiz;
public:
    kdtree();
    bool esVacio();
    T& datoRaiz();
    int altura();
    int tamano();
    void insertar(T& vertice);
    bool eliminar(const T& val);
    kdnodo<T>* buscar(const T& val);
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
    void maximo(T& maxi);
    void minimo(T& mini);
    double distanciaEuclidiana(T& puntoFig, const std::vector<float>& puntoComp);
    T encontrarMasCercano(T& punto_buscado, double& menor_distancia);

private:
    kdnodo<T>* insertarRec(kdnodo<T>* nodo, T& vertice, int profundidad);
    void encontrarMasCercanoRec(kdnodo<T>* nodo, const std::vector<float>& punto, double& menor_distancia, T& vertice_cercano, int indice); // Cambiado de Vertices a T
};

#include "kdtree.hxx"
#endif
