#include "kdtree.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

template <typename T>
kdtree<T>::kdtree() {
    this->raiz = nullptr;
}

template <typename T>
bool kdtree<T>::esVacio() {
    return raiz == nullptr; // Cambia this por raiz
}

template <typename T>
T& kdtree<T>::datoRaiz() {
    return this->raiz->obtenerDato();
}

template <typename T>
int kdtree<T>::altura() {
    return this->raiz ? this->raiz->altura() : -1; // Agregar manejo de caso vacío
}

template <typename T>
int kdtree<T>::tamano() {
    return this->raiz ? this->raiz->tamano() : 0; // Agregar manejo de caso vacío
}

template <typename T>
void kdtree<T>::insertar(T& vertice) {
    if (!raiz) {
        // Si no hay raíz, creamos el primer nodo
        raiz = new kdnodo<T>();
        raiz->fijarDato(vertice);  // Guardamos el primer vértice en la raíz
        std::cout << "Insertando raiz con vertice: "
                  << vertice.ObtenerCoorX() << ", "
                  << vertice.ObtenerCoorY() << ", "
                  << vertice.ObtenerCoorZ() << std::endl;
    } else {
        // Llamamos al método de inserción recursivo en la raíz
        raiz = insertarRec(raiz, vertice, 0); // El nivel comienza en 0
    }
}

template <typename T>
bool kdtree<T>::eliminar(const T& val) {
    if (!raiz) {
        return false;  // No se puede eliminar si el árbol está vacío
    }
    // Aquí debería ir la lógica para eliminar un nodo
    // Esto depende de cómo quieras implementar la eliminación
    return false; // Placeholder
}

template <typename T>
kdnodo<T>* kdtree<T>::buscar(const T& val) {
    if (!raiz) {
        return nullptr;  // Si el árbol está vacío, devuelve nullptr
    }
    return raiz->buscar(val);  // Llama al metodo buscar del nodo raíz
}

template <typename T>
void kdtree<T>::preOrden() {
    if (raiz) {
        raiz->preOrden();
    }
}

template <typename T>
void kdtree<T>::inOrden() {
    if (raiz) {
        raiz->inOrden();
    }
}

template <typename T>
void kdtree<T>::posOrden() {
    if (raiz) {
        raiz->posOrden();
    }
}

template <typename T>
void kdtree<T>::nivelOrden() {
    if (raiz) {
        raiz->nivelOrden();
    }
}

template <typename T>
void kdtree<T>::maximo(T& maxi) {
    if (raiz) {
        raiz->maximo(maxi);
    }
}

template <typename T>
void kdtree<T>::minimo(T& mini) {
    if (raiz) {
        raiz->minimo(mini);
    }
}

template <typename T>
double kdtree<T>::distanciaEuclidiana(T& puntoFig, const std::vector<float>& puntoComp) {
    double suma = 0.0;

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

template <typename T>
T kdtree<T>::encontrarMasCercano(T& punto_buscado, double& menor_distancia) {
    T vertice_cercano; //aca se guarda el vertice mas cercano
    vector<float> punto = { punto_buscado.ObtenerCoorX(), punto_buscado.ObtenerCoorY(), punto_buscado.ObtenerCoorZ() };

    menor_distancia = numeric_limits<double>::max(); //valor grandesito

    // Llamada recursiva al metodo para encontrar el vertice mas cercano
    encontrarMasCercanoRec(raiz, punto, menor_distancia, vertice_cercano, 0);

    return vertice_cercano;
}

template <typename T>
kdnodo<T>* kdtree<T>::insertarRec(kdnodo<T>* nodo, T& vertice, int profundidad) {
    if (nodo == nullptr) {
        nodo = new kdnodo<T>();
        nodo->fijarDato(vertice);
        return nodo;
    }

    float coordX = vertice.ObtenerCoorX();
    float coordY = vertice.ObtenerCoorY();
    float coordZ = vertice.ObtenerCoorZ();

    // Determinar la dimensión a comparar
    int dim = profundidad % 3; // Cambiar a 3 para X, Y, Z

    // Comparar los valores y decidir si ir a la izquierda o derecha
    if ((dim == 0 && coordX < nodo->obtenerDato().ObtenerCoorX()) ||
        (dim == 1 && coordY < nodo->obtenerDato().ObtenerCoorY()) ||
        (dim == 2 && coordZ < nodo->obtenerDato().ObtenerCoorZ())) {
        nodo->fijarHijoIzq(insertarRec(nodo->obtenerHijoIzq(), vertice, profundidad + 1));
    } else {
        nodo->fijarHijoDer(insertarRec(nodo->obtenerHijoDer(), vertice, profundidad + 1));
    }

    return nodo;
}

template <typename T>
void kdtree<T>::encontrarMasCercanoRec(kdnodo<T>* nodo, const std::vector<float>& punto, double& menor_distancia, T& vertice_cercano, int nivel) {
    if (nodo == nullptr) return;

    T datoNodo = nodo->obtenerDato();

    // Calcular la distancia Euclidiana entre el punto del nodo y el punto de búsqueda
    double distancia = distanciaEuclidiana(datoNodo, punto);

    // Actualizar el vértice más cercano si encontramos uno más cercano
    if (distancia < menor_distancia) {
        menor_distancia = distancia;
        vertice_cercano = datoNodo;
    }

    // Determinar la dimensión actual
    int dim = nivel % 3; // Cambia para X, Y, Z
    float coordNodo = (dim == 0) ? datoNodo.ObtenerCoorX() : (dim == 1) ? datoNodo.ObtenerCoorY() : datoNodo.ObtenerCoorZ();

    // Decidir si buscar en el hijo izquierdo o derecho
    if (punto[dim] < coordNodo) {
        encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano, nivel + 1);
        if (fabs(punto[dim] - coordNodo) < menor_distancia) {
            encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano, nivel + 1);
        }
    } else {
        encontrarMasCercanoRec(nodo->obtenerHijoDer(), punto, menor_distancia, vertice_cercano, nivel + 1);
        if (fabs(punto[dim] - coordNodo) < menor_distancia) {
            encontrarMasCercanoRec(nodo->obtenerHijoIzq(), punto, menor_distancia, vertice_cercano, nivel + 1);
        }
    }
}

/*
template <typename T>
std::vector<T> kdtree<T>::encontrarVerticesMasCercanos( Figuras caja) {
    std::vector<T> verticesCercanos;
    std::vector<Vertices> esquinas = caja.obtenerEsquinas();

    // Verificar si hay esquinas en la caja envolvente
    if (esquinas.empty()) {
        std::cout << "La caja envolvente no contiene esquinas." << std::endl;
        return verticesCercanos;
    }

    // Imprimir encabezado de la tabla
    std::cout << "Resultado exitoso: Los vértices del objeto más cercanos a las esquinas de su caja envolvente son:" << std::endl;
    std::cout << "Esquina          Vértice          Distancia" << std::endl;

    for (size_t i = 0; i < esquinas.size(); ++i) {
        const auto& esquina = esquinas[i];
        double menor_distancia = std::numeric_limits<double>::max();
        T verticeCercano = encontrarMasCercano(esquina, menor_distancia); // Encontrar el vértice más cercano

        // Si se encontró un vértice cercano
        if (menor_distancia < std::numeric_limits<double>::max()) {
            verticesCercanos.push_back(verticeCercano);
            std::cout << "(" << esquina.ObtenerCoorX() << ", "
                      << esquina.ObtenerCoorY() << ", "
                      << esquina.ObtenerCoorZ() << ") "
                      << " i" << (i + 1) << " ("
                      << verticeCercano.ObtenerCoorX() << ", "
                      << verticeCercano.ObtenerCoorY() << ", "
                      << verticeCercano.ObtenerCoorZ() << ") "
                      << menor_distancia << std::endl;
        } else {
            // Si no se encontró un vértice cercano
            std::cout << "Esquina " << (i + 1) << " ("
                      << esquina.ObtenerCoorX() << ", "
                      << esquina.ObtenerCoorY() << ", "
                      << esquina.ObtenerCoorZ() << ") "
                      << " no tiene un vértice cercano." << std::endl;
        }
    }

    return verticesCercanos;
}
*/