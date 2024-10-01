#include "kdtree.h"
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
		// Si no hay raíz, creamos el primer nodo
		raiz = new kdnodo<T>();
		raiz->fijarDato(vertice);  // Guardamos el primer vértice en la raíz
		std::cout << "Insertando raíz con vértice: "
				  << vertice.ObtenerCoorX() << ", "
				  << vertice.ObtenerCoorY() << ", "
				  << vertice.ObtenerCoorZ() << std::endl;
	} else {
		// Llamamos al método de inserción recursivo en la raíz
		raiz->insertar(vertice, 0); // El nivel comienza en 0
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

	// Obtener las coordenadas del vértice
	float coordX = puntoFig.ObtenerCoorX();
	float coordY = puntoFig.ObtenerCoorY();
	float coordZ = puntoFig.ObtenerCoorZ();

	// Calcular la suma de las diferencias al cuadrado
	suma += pow(coordX - puntoComp[0], 2);
	suma += pow(coordY - puntoComp[1], 2);
	suma += pow(coordZ - puntoComp[2], 2);

	// Retornar la raíz cuadrada de la suma de cuadrados
	return sqrt(suma);
}




template<class T>
Vertices kdtree<T>::encontrarMasCercano(Vertices& punto_buscado, double& menor_distancia) {
	Vertices vertice_cercano; // Variable para almacenar el vértice más cercano
	std::vector<float> punto = { punto_buscado.ObtenerCoorX(), punto_buscado.ObtenerCoorY(), punto_buscado.ObtenerCoorZ() };

	// Inicializar menor_distancia con un valor muy grande
	menor_distancia = std::numeric_limits<double>::max();

	// Llamada recursiva al método para encontrar el vértice más cercano
	encontrarMasCercanoRec(raiz, punto, menor_distancia, vertice_cercano, 0);

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
void kdtree<T>::encontrarMasCercanoRec(kdnodo<T>* nodo, const std::vector<float>& punto, double& menor_distancia, Vertices& vertice_cercano, int nivel) {
    if (nodo == nullptr) return;

    // Obtener el dato del nodo actual (debería ser un objeto Vertices)
    Vertices datoNodo = nodo->obtenerDato();

    // Calcular la distancia Euclidiana entre el punto del nodo y el punto de búsqueda
    double distancia = distanciaEuclidiana(datoNodo, punto);

    // Imprimir para depuración
    std::cout << "Distancia actual: " << distancia << " - Vértice: ("
              << datoNodo.ObtenerCoorX() << ", "
              << datoNodo.ObtenerCoorY() << ", "
              << datoNodo.ObtenerCoorZ() << ")" << std::endl;

    // Actualizar el vértice más cercano si encontramos uno más cercano
    if (distancia < menor_distancia) {
        menor_distancia = distancia;
        vertice_cercano = datoNodo;
    }

    // Determinar la dimensión actual (0 = X, 1 = Y, 2 = Z)
    int dim = 3; // Número de dimensiones
    int indice = nivel % dim; // Alternamos entre X, Y, Z

    // Obtener la coordenada del nodo actual según el nivel
    float coordNodo;
    if (indice == 0) coordNodo = datoNodo.ObtenerCoorX();
    else if (indice == 1) coordNodo = datoNodo.ObtenerCoorY();
    else coordNodo = datoNodo.ObtenerCoorZ();

    // Decidir si buscar en el hijo izquierdo o derecho
    if (punto[indice] < coordNodo) {
        // Buscar en el hijo izquierdo
        encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano, nivel + 1);

        // Verificar si necesitamos revisar también el otro lado
        if (fabs(punto[indice] - coordNodo) < menor_distancia) {
            encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano, nivel + 1);
        }
    } else {
        // Buscar en el hijo derecho
        encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano, nivel + 1);

        // Verificar si necesitamos revisar también el otro lado
        if (fabs(punto[indice] - coordNodo) < menor_distancia) {
            encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano, nivel + 1);
        }
    }
}

