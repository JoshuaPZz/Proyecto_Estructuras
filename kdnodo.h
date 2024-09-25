#ifndef __KDNODO__H__
#define __KDNODO__H__

using namespace std;


#include <vector>
#include <iostream>

template< class T >
class kdnodo
{
private:
    vector<T> datos;  // Vector que almacena las coordenadas (x, y, z)
    kdnodo<T>* hijoIzq;  // Puntero al hijo izquierdo
    kdnodo<T>* hijoDer;  // Puntero al hijo derecho
    int tag; // Nivel de división (0 para X, 1 para Y, 2 para Z)

  public:
  	kdnodo();
    T& obtenerDato();
    void fijarDato(vector < T > & val);
    kdnodo<T>* obtenerHijoIzq();
    kdnodo<T>* obtenerHijoDer();
    void fijarHijoIzq(kdnodo<T> *izq);
    void fijarHijoDer(kdnodo<T> *der);
    void fijarTag(int value);
    int altura();
    int tamano();
    void insertar(vector < T > & val, int nivel);
    kdnodo<T>* buscar(vector < T > & val, int nivel);
    vector<float> obtenerCoordenadas();
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
    void maximo(int &maxi);
    void minimo(int &mini);
    void imprimir();
    double distanciaEuclidiana(vector<T>& p1, vector<T>& p2) {
        return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2) + pow(p1[2] - p2[2], 2));
    }

};

#include "kdnodo.hxx"
#endif
