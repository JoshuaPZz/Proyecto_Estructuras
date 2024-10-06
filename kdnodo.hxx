#include "kdnodo.h"
#include <iostream>
#include <queue>
#include <cmath>

template<class T>
kdnodo<T>::kdnodo()
{
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
    this->tag = 0; // 0 x, 1 y, 2 z
}

template<class T>
Vertices& kdnodo<T>::obtenerDato()
{
    return dato;
}

template<class T>
void kdnodo<T>::fijarDato(const Vertices& val) {
    dato = val;  // Asigna el valor recibido al dato
}

template<class T>
void kdnodo<T>::fijarTag(int value)
{
    this->tag = value;
}

template<class T>
kdnodo<T>* kdnodo<T>::obtenerHijoIzq()
{
    return this->hijoIzq;
}

template<class T>
kdnodo<T>* kdnodo<T>::obtenerHijoDer()
{
    return this->hijoDer;
}

template<class T>
void kdnodo<T>::fijarHijoIzq(kdnodo<T>* izq)
{
    this->hijoIzq = izq;
}

template<class T>
void kdnodo<T>::fijarHijoDer(kdnodo<T>* der)
{
    this->hijoDer = der;
}

template<class T>
int kdnodo<T>::altura()
{
    if (this->hijoIzq == nullptr && this->hijoDer == nullptr)
    {
        return 1;
    }
    if (this->hijoIzq == nullptr)
        return this->hijoDer->altura() + 1;
    else if (this->hijoDer == nullptr)
        return this->hijoIzq->altura() + 1;

    return std::max(this->hijoIzq->altura(), this->hijoDer->altura()) + 1;
}

template<class T>
void kdnodo<T>::insertar(Vertices& val, int nivel) {
    // Si el nodo está vacío, fijamos el dato
    if (dato.esVacio()) {
        fijarDato(val); // Guardamos el primer nodo
        std::cout << "Insertando primer vertice: "
                  << val.ObtenerCoorX() << ", "
                  << val.ObtenerCoorY() << ", "
                  << val.ObtenerCoorZ() << std::endl;
        return;
    }

    // evitar duplicados exactos
    if (dato.ObtenerCoorX() == val.ObtenerCoorX() &&
        dato.ObtenerCoorY() == val.ObtenerCoorY() &&
        dato.ObtenerCoorZ() == val.ObtenerCoorZ()) {
        std::cout << "El vertice ya existe en el arbol: "
                  << val.ObtenerCoorX() << ", "
                  << val.ObtenerCoorY() << ", "
                  << val.ObtenerCoorZ() << std::endl;
        return; // si el vertice ya esta paila
    }

    // Determinar la dimensión actual (0 = X, 1 = Y, 2 = Z)
    int dim = nivel % 3;
    float coordVal, coordDato;

    // segun el dim alternar entre dimensiones
    switch (dim) {
        case 0:
            //x
            coordVal = val.ObtenerCoorX();
            coordDato = dato.ObtenerCoorX();
            break;
        case 1:
            //y
            coordVal = val.ObtenerCoorY();
            coordDato = dato.ObtenerCoorY();
            break;
        case 2:
            //z
            coordVal = val.ObtenerCoorZ();
            coordDato = dato.ObtenerCoorZ();
            break;
    }

    std::cout << "Nivel: " << nivel << " Dimension: " << dim
              << " CoordVal: " << coordVal
              << " CoordDato: " << coordDato << std::endl;

    // Comparar según la dimensión actual
    if (coordVal < coordDato) {
        if (hijoIzq == nullptr) {
            hijoIzq = new kdnodo<T>(); // Crea un nuevo nodo para el hijo izquierdo
            std::cout << "Creando hijo izquierdo para " << coordVal << std::endl;
        }
        hijoIzq->insertar(val, nivel + 1); // Inserta en el hijo izquierdo
    } else if (coordVal > coordDato) {
        if (hijoDer == nullptr) {
            hijoDer = new kdnodo<T>(); // Crea un nuevo nodo para el hijo derecho
            std::cout << "Creando hijo derecho para " << coordVal << std::endl;
        }
        hijoDer->insertar(val, nivel + 1); // Inserta en el hijo derecho
    } else {
        // Si coordVal y coordDato son iguales en la dimensión actual,no insertamos na
        std::cout << "Las coordenadas son iguales en la dimension " << dim
                  << ". El vertice ya existe o es un duplicado parcial." << std::endl;
        return;
    }
}


// Método para obtener coordenadas de un nodo
template<class T>
std::vector<float> kdnodo<T>::obtenerCoordenadas()
{
    return {dato.ObtenerCoorX(), dato.ObtenerCoorY(), dato.ObtenerCoorZ()};
}

template<class T>
void kdnodo<T>::preOrden()
{
    this->imprimir();
    if (this->hijoIzq != nullptr)
        this->hijoIzq->preOrden();
    if (this->hijoDer != nullptr)
        this->hijoDer->preOrden();
}

template<class T>
void kdnodo<T>::inOrden()
{
    if (this->hijoIzq != nullptr)
        this->hijoIzq->inOrden();

    this->imprimir();

    if (this->hijoDer != nullptr)
        this->hijoDer->inOrden();
}

template<class T>
void kdnodo<T>::posOrden()
{
    if (this->hijoIzq != nullptr)
        this->hijoIzq->posOrden();

    if (this->hijoDer != nullptr)
        this->hijoDer->posOrden();

    this->imprimir();
}

template<class T>
void kdnodo<T>::nivelOrden()
{
    std::queue<kdnodo<T>*> cola;
    cola.push(this);
    while (!cola.empty())
    {
        cola.front()->imprimir();
        if (cola.front()->hijoIzq != nullptr)
        {
            cola.push(cola.front()->hijoIzq);
        }

        if (cola.front()->hijoDer != nullptr)
        {
            cola.push(cola.front()->hijoDer);
        }
        cola.pop();
    }
}

template<class T>
void kdnodo<T>::maximo(float& maxi) {
    if (maxi < dato.ObtenerCoorX()) {
        maxi = dato.ObtenerCoorX();  // Actualiza el máximo
    }

    if (hijoIzq != nullptr) {
        hijoIzq->maximo(maxi);  // Busca en el hijo izquierdo
    }

    if (hijoDer != nullptr) {
        hijoDer->maximo(maxi);  // Busca en el hijo derecho
    }
}

template<class T>
void kdnodo<T>::minimo(float& mini) {
    if (mini > dato.ObtenerCoorX()) {
        mini = dato.ObtenerCoorX();  // Actualiza el mínimo
    }

    if (hijoIzq != nullptr) {
        hijoIzq->minimo(mini);  // Busca en el hijo izquierdo
    }

    if (hijoDer != nullptr) {
        hijoDer->minimo(mini);  // Busca en el hijo derecho
    }
}

template<class T>
void kdnodo<T>::imprimir()
{
    std::cout << "( "
              << dato.ObtenerCoorX() << ", "
              << dato.ObtenerCoorY() << ", "
              << dato.ObtenerCoorZ() << " )" << std::endl;
}

template <class T>
double kdnodo<T>::distanciaEuclidiana( Vertices& p1,  Vertices& p2) {
    return sqrt(pow(p1.ObtenerCoorX() - p2.ObtenerCoorX(), 2) +
                pow(p1.ObtenerCoorY() - p2.ObtenerCoorY(), 2) +
                pow(p1.ObtenerCoorZ() - p2.ObtenerCoorZ(), 2));
}