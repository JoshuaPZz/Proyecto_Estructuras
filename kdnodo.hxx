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
    return datos;
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
int kdnodo<T>::tamano()
{
    if (this->hijoIzq == nullptr && this->hijoDer == nullptr)
    {
        return 1;
    }
    return 1 + (this->hijoIzq ? this->hijoIzq->tamano() : 0) + (this->hijoDer ? this->hijoDer->tamano() : 0);
}

template<class T>
void kdnodo<T>::insertar(T& val, int nivel)
{
    if (datos.empty())
    {
        fijarDato(val);  // Guardamos el primer nodo
    }
    else
    {
        // Obtén la dimensión actual en la que estamos insertando
        int dim = nivel % 3;  // Asumiendo que `Vertices` tiene 3 dimensiones

        // Comparamos usando las coordenadas de `val`
        float coordVal;
        switch (dim)
        {
        case 0: coordVal = val.ObtenerCoorX(); break;
        case 1: coordVal = val.ObtenerCoorY(); break;
        case 2: coordVal = val.ObtenerCoorZ(); break;
        }

        if (coordVal < obtenerDato().ObtenerCoorX())  // Cambia esto según sea necesario
        {
            if (hijoIzq == nullptr)
            {
                hijoIzq = new kdnodo<T>();  // Crea nuevo nodo
            }
            hijoIzq->insertar(val, nivel + 1);
        }
        else
        {
            if (hijoDer == nullptr)
            {
                hijoDer = new kdnodo<T>();  // Crea nuevo nodo
            }
            hijoDer->insertar(val, nivel + 1);
        }
    }
}


// Método para obtener coordenadas de un nodo
template<class T>
std::vector<float> kdnodo<T>::obtenerCoordenadas()
{
    return {datos[0].getX(), datos[0].getY(), datos[0].getZ()};
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
    for (size_t i = 0; i < this->datos.size(); ++i)
    {
        cout << this->datos[i];
        if (i != this->datos.size() - 1)
            cout << ", ";
    }
    cout << " )\n";
}
