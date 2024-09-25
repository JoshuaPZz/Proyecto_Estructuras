#ifndef __KDTREE__H__
#define __KDTREE__H__

#include "kdtree.h"
#include "kdnodo.h"

using namespace std;

template<class T>
class kdtree {
  protected:
    kdnodo<T> *raiz;
public:
	kdtree();
    bool esVacio();
    T& datoRaiz();
    int altura();
    int tamano();
    void insertar(Vertices& vertice) ;
    bool eliminar(vector<T>& val);  // Cambiar T& a vector<T>&
    kdnodo<T>* buscar(vector<T>& val);
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
    void maximo(int &maxi);
    void minimo(int &mini);
    double distanciaEuclidiana(kdnodo<T>* puntoFig, const std::vector<float>& puntoComp);


    Vertices encontrarMasCercano(const Vertices& punto_buscado, double& menor_distancia) {

    kdnodo<T>* insertarRec(kdnodo<T>* nodo, const std::vector<float>& punto, int profundidad);
    void encontrarMasCercanoRec(kdnodo<T>* nodo, const std::vector<float>& punto, double& menor_distancia, Vertices& vertice_cercano);
};

#include "kdtree.hxx"
#endif
