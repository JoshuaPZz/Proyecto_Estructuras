#ifndef KDNODO_H
#define KDNODO_H

#include <vector>
#include <iostream>
#include "Vertices.h"

using namespace std;

template<class T>
class kdnodo {
private:
    Vertices dato;
    kdnodo<T>* hijoIzq;  // Puntero al hijo izquierdo
    kdnodo<T>* hijoDer;  // Puntero al hijo derecho
    int tag; // Nivel de división (0 para X, 1 para Y, 2 para Z)

public:
    kdnodo();
    Vertices& obtenerDato();
    void fijarDato(const Vertices& val);
    kdnodo<T>* obtenerHijoIzq();
    kdnodo<T>* obtenerHijoDer();
    void fijarHijoIzq(kdnodo<T>* izq);
    void fijarHijoDer(kdnodo<T>* der);
    void fijarTag(int value);
    int altura();
    int tamano();
    void insertar(Vertices& val, int nivel);
    kdnodo<T>* buscar(const std::vector<T>& val, int nivel);
    vector<float> obtenerCoordenadas();
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
    void maximo(float& maxi);
    void minimo(float& mini);
    void imprimir();
    double distanciaEuclidiana( Vertices& p1,  Vertices& p2);
};
#include "kdnodo.hxx"
#endif