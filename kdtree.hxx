#include "kdtree.h"
#include "kdnodo.h"
#include <cmath>

using namespace std;


template<class T>
kdtree<T>::kdtree(){
	this->raiz=NULL;
}


template<class T>
bool kdtree<T>::esVacio()
{
	return raiz == NULL; // Cambia this por raiz
}

template<class T>
T& kdtree<T>::datoRaiz()
{
   return this->raiz->obtenerDato();
}

template<class T>
int kdtree<T>::altura()
{
   return this->raiz->altura();
}

template<class T>
int kdtree<T>::tamano()
{
	return this->raiz->tamano() ;
}

template<class T>
void kdtree<T>::insertar(Vertices& vertice) {
	// Crear un vector con las coordenadas del vértice
	vector<float> val = { vertice.ObtenerCoorX(), vertice.ObtenerCoorY(), vertice.ObtenerCoorZ() };

	// Comprobar si el árbol está vacío
	if (!raiz) {
		raiz = new kdnodo<T>();
		raiz->fijarDato(val);
	} else {
		raiz->insertar(val, 0);
	}
}



template<class T>
bool kdtree<T>::eliminar(vector<T>& val) {
	if (!raiz) {
		return false;  // No se puede eliminar si el árbol está vacío
	}
	bool eliminado = false;
	raiz = eliminarRec(raiz, val, 0, eliminado);
	return eliminado;
}

template<class T>
kdnodo<T>* kdtree<T>::buscar(vector<T>& val) {
	if (!raiz) {
		return nullptr;  // Si el árbol está vacío, devuelve nullptr
	}
	return raiz->buscar(val, 0);  // Llama al metodo buscar del nodo raíz, comenzando en nivel 0
}


template<class T>
void kdtree<T>::preOrden()
{
	this->raiz->preOrden();
}

template<class T>
void kdtree<T>::inOrden()
{
	this->raiz->inOrden();
}

template<class T>
void kdtree<T>::posOrden()
{
	this->raiz->posOrden();
}

template<class T>
void kdtree<T>::nivelOrden()
{
	this->raiz->nivelOrden();
}

template<class T>
void kdtree<T>::maximo(int &maxi)
{
	this->raiz->maximo(maxi);
}

template<class T>
void kdtree<T>::minimo(int &mini)
{
	this->raiz->minimo(mini);
}

template<class T>
double distanciaEuclidiana(kdnodo<T>* puntoFig, const std::vector<float>& puntoComp) {

	double suma = 0.0;
	std::vector<float> coordsFig = puntoFig->obtenerDato(); // Especificamos el tipo explícitamente.

	for (size_t i = 0; i < puntoComp.size(); ++i) {
		suma += pow(coordsFig[i] - puntoComp[i], 2);
	}

	return sqrt(suma);
}

template<class T>
Vertices kdtree<T>::encontrarMasCercano(const Vertices& punto_buscado, double& menor_distancia) {
	Vertices vertice_cercano; // Variable para almacenar el vértice más cercano
	std::vector<float> punto = { punto_buscado.ObtenerCoorX(), punto_buscado.ObtenerCoorY(), punto_buscado.ObtenerCoorZ() };
	encontrarMasCercanoRec(raiz, punto, menor_distancia, vertice_cercano);
	return vertice_cercano;
}

template<class T>
kdnodo<T>* kdtree<T>::insertarRec(kdnodo<T>* nodo, const Vertices& vertice, int profundidad) {
	std::vector<float> punto = { vertice.ObtenerCoorX(), vertice.ObtenerCoorY(), vertice.ObtenerCoorZ() };
	if (nodo == nullptr) {
		nodo = new kdnodo<T>();
		nodo->fijarDato(punto);
		return nodo;
	}

	// Determinar la dimensión a comparar
	int dim = profundidad % punto.size();

	// Comparar los valores y decidir si ir a la izquierda o derecha
	if (punto[dim] < nodo->obtenerDato()[dim]) {
		nodo->fijarHijoIzq(insertarRec(nodo->obtenerHijoIzq(), vertice, profundidad + 1));
	} else {
		nodo->fijarHijoDer(insertarRec(nodo->obtenerHijoDer(), vertice, profundidad + 1));
	}

	return nodo;
}

template<class T>
void kdtree<T>::encontrarMasCercanoRec(kdnodo<T>* nodo, const std::vector<float>& punto, double& menor_distancia, Vertices& vertice_cercano) {
	if (nodo == nullptr) return;

	// Calcular la distancia euclidiana
	double distancia = distanciaEuclidiana(nodo->obtenerDato(), punto);
	if (distancia < menor_distancia) {
		menor_distancia = distancia;
		vertice_cercano = Vertices(nodo->obtenerDato()[0], nodo->obtenerDato()[1], nodo->obtenerDato()[2]); // Suponiendo que Vertices tiene un constructor que toma x, y, z
	}

	int dim = punto.size();
	int indice = 0; // Alterna entre los índices de las dimensiones
	if (punto[indice] < nodo->obtenerDato()[indice]) {
		encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano);
		if (fabs(punto[indice] - nodo->obtenerDato()[indice]) < menor_distancia) {
			encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano);
		}
	} else {
		encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano);
		if (fabs(punto[indice] - nodo->obtenerDato()[indice]) < menor_distancia) {
			encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano);
		}
	}
}