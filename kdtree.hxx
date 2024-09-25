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
	if (!raiz) {
		raiz = new kdnodo<T>();
		raiz->fijarDato(vertice);  // Usamos el objeto Vertices directamente
	} else {
		raiz->insertar(vertice, 0); // Llamamos al método insertar
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
double kdtree<T>::distanciaEuclidiana(Vertices& puntoFig, const std::vector<float>& puntoComp) {
	double suma = 0.0;

	// Utiliza los métodos adecuados para obtener las coordenadas
	float coordX = puntoFig.ObtenerCoorX();
	float coordY = puntoFig.ObtenerCoorY();
	float coordZ = puntoFig.ObtenerCoorZ();

	// Supongamos que puntoComp tiene 3 dimensiones
	suma += pow(coordX - puntoComp[0], 2);
	suma += pow(coordY - puntoComp[1], 2);
	suma += pow(coordZ - puntoComp[2], 2);

	return sqrt(suma);
}



template<class T>
Vertices kdtree<T>::encontrarMasCercano(Vertices& punto_buscado, double& menor_distancia) {
	Vertices vertice_cercano; // Variable para almacenar el vértice más cercano
	std::vector<float> punto = { punto_buscado.ObtenerCoorX(), punto_buscado.ObtenerCoorY(), punto_buscado.ObtenerCoorZ() };
	encontrarMasCercanoRec(raiz, punto, menor_distancia, vertice_cercano);
	return vertice_cercano;
}

template<class T>
kdnodo<T>* kdtree<T>::insertarRec(kdnodo<T>* nodo,  Vertices& vertice, int profundidad) {
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

	// Asegúrate de que obtenerDato() devuelva un objeto Vertices
	Vertices datoNodo = nodo->obtenerDato(); // Aquí obtenemos el objeto Vertices

	// Llama a distanciaEuclidiana con un objeto Vertices
	double distancia = distanciaEuclidiana(datoNodo, punto);

	if (distancia < menor_distancia) {
		menor_distancia = distancia;
		vertice_cercano = datoNodo; // Usar el objeto Vertices directamente
	}

	int dim = punto.size();
	int indice = 0; // Alterna entre los índices de las dimensiones
	float coordNodo = datoNodo.ObtenerCoorX(); // Usa el método adecuado para obtener la coordenada

	if (punto[indice] < coordNodo) {
		encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano);
		if (fabs(punto[indice] - coordNodo) < menor_distancia) {
			encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano);
		}
	} else {
		encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano);
		if (fabs(punto[indice] - coordNodo) < menor_distancia) {
			encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano);
		}
	}
}

