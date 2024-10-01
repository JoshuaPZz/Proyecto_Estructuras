#include "kdnodo.h"
#include <bits/stdc++.h>

using namespace std;

template<class T>
kdnodo<T>::kdnodo()
{
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
    this->tag = 0; // 0 x, 1 y, 2 z
}

template<class T>
T& kdnodo<T>::obtenerDato()
{
    return dato;
}

template<class T>
void kdnodo<T>::fijarDato(const T& val) {
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

    return max(this->hijoIzq->altura(), this->hijoDer->altura()) + 1;
}

template<class T>
void kdnodo<T>::insertar(T& val, int nivel) {
    // Si el nodo está vacío, fijamos el dato
    if (dato.esVacio()) {
        fijarDato(val); // Guardamos el primer nodo
        std::cout << "Insertando primer vertice: "
                  << val.ObtenerCoorX() << ", "
                  << val.ObtenerCoorY() << ", "
                  << val.ObtenerCoorZ() << std::endl;
        return;
    }

    // Comprobación para evitar duplicados exactos en todas las dimensiones
    if (dato.ObtenerCoorX() == val.ObtenerCoorX() &&
        dato.ObtenerCoorY() == val.ObtenerCoorY() &&
        dato.ObtenerCoorZ() == val.ObtenerCoorZ()) {
        std::cout << "El vertice ya existe en el arbol: "
                  << val.ObtenerCoorX() << ", "
                  << val.ObtenerCoorY() << ", "
                  << val.ObtenerCoorZ() << std::endl;
        return; // Salir si el vértice ya está presente
    }

    // Determinar la dimensión actual (0 = X, 1 = Y, 2 = Z)
    int dim = nivel % 3;  // Asumimos que Vertices tiene 3 dimensiones
    float coordVal, coordDato;

    // Alternar la coordenada comparada según el nivel (dim)
    switch (dim) {
        case 0:
            coordVal = val.ObtenerCoorX();
            coordDato = dato.ObtenerCoorX();
            break; // Comparar en X
        case 1:
            coordVal = val.ObtenerCoorY();
            coordDato = dato.ObtenerCoorY();
            break; // Comparar en Y
        case 2:
            coordVal = val.ObtenerCoorZ();
            coordDato = dato.ObtenerCoorZ();
            break; // Comparar en Z
    }

    std::cout << "Nivel: " << nivel << " Dimension: " << dim
              << " CoordVal: " << coordVal
              << " CoordDato: " << coordDato << std::endl;

    // Decidir si ir al hijo izquierdo o derecho según la coordenada
    if (coordVal < coordDato) {
        if (hijoIzq == nullptr) {
            hijoIzq = new kdnodo<T>(); // Crea un nuevo nodo para el hijo izquierdo
            std::cout << "Creando hijo izquierdo para " << coordVal << std::endl;
        }
        hijoIzq->insertar(val, nivel + 1); // Inserta en el hijo izquierdo
    } else if (coordVal > coordDato) {
        // Si el valor es mayor, ir al hijo derecho
        if (hijoDer == nullptr) {
            hijoDer = new kdnodo<T>(); // Crea un nuevo nodo para el hijo derecho
            std::cout << "Creando hijo derecho para " << coordVal << std::endl;
        }
        hijoDer->insertar(val, nivel + 1); // Inserta en el hijo derecho
    } else {
        // Si coordVal == coordDato pero en otra dimensión (caso raro)
        std::cout << "El vertice ya existe en esta dimension: " << coordVal << std::endl;
    }
}



// Método para obtener coordenadas de un nodo
template<class T>
std::vector<float> kdnodo<T>::obtenerCoordenadas()
{
    return {dato[0].getX(), dato[0].getY(), dato[0].getZ()};
}

template<class T>
kdnodo<T>* kdnodo<T>::buscar(const std::vector<T>& val, int nivel) {
    if (dato == val) {
        return this;  // Se encontró el nodo
    }

    int dim = nivel % val.size();  // Obtener la dimensión actual
    if (val[dim] < dato[dim]) {
        return hijoIzq ? hijoIzq->buscar(val, nivel + 1) : nullptr;  // Buscar en el hijo izquierdo
    } else {
        return hijoDer ? hijoDer->buscar(val, nivel + 1) : nullptr;  // Buscar en el hijo derecho
    }
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
    queue<kdnodo*> cola;
    cola.push(this);
    while (!cola.empty())
    {
        cout << "\t" << cola.front()->obtenerDato() << endl;
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
    // Comparar el dato actual con el máximo actual
    if (maxi < this->obtenerDato()) {
        maxi = this->obtenerDato();  // Actualiza el máximo si es necesario
    }

    // Llama recursivamente a los hijos izquierdo y derecho
    if (this->hijoIzq != nullptr) {
        this->hijoIzq->maximo(maxi);  // Busca en el hijo izquierdo
    }

    if (this->hijoDer != nullptr) {
        this->hijoDer->maximo(maxi);  // Busca en el hijo derecho
    }
}

template<class T>
void kdnodo<T>::minimo(float& mini) {
    if (mini > this->obtenerDato()) {
        mini = this->obtenerDato();  // Actualiza el mínimo si es necesario
    }
    if (this->hijoIzq != nullptr) {
        this->hijoIzq->minimo(mini);  // Busca en el hijo izquierdo
    }

    if (this->hijoDer != nullptr) {
        this->hijoDer->minimo(mini);  // Busca en el hijo derecho
    }
}

template<class T>
void kdnodo<T>::imprimir()
{
    cout << "( ";
    for (size_t i = 0; i < this->dato.size(); ++i)
    {
        cout << this->dato[i];
        if (i != this->dato.size() - 1)
            cout << ", ";
    }
    cout << " )\n";
}
