#include "Comandos.h"
using namespace std;
#include <vector>


Figuras Figuras::CargarFigura(const string &argumento1) {
  int indice = 0;
  ifstream entrada(argumento1);

  if (!entrada) {
    cout << "El archivo " << argumento1 << " no existe o es ilegible" << endl;
    exit(1);
  }

  string linea;
   if (!(entrada >> this->nombre)) {
    cout << "El archivo " << argumento1 << " no contiene un objeto 3D valido (nombre)" << endl;
    exit(1);
  }
 // this->nombre = linea;

  if (!(entrada >> this->nvertices)) {
    cout << "El archivo " << argumento1 << " no contiene un objeto 3D valido (nvertices)" << endl;
    exit(1);
  }

  this->lvertices.clear();
  for (int j = 0; j < this->nvertices; j++) {
    Vertices vertice;
    vertice.CargarVertice(entrada, indice);
    this->lvertices.push_back(vertice);
  }
  this->lcaras.clear();
  string pal;
   while (entrada >> ws && entrada.peek() != '-' && !entrada.eof()) {
    Caras cara;
    cara.CargarCara(entrada);
    this->lcaras.push_back(cara);
  }

  if (this->lvertices.size() != this->nvertices || this->lvertices.empty() ||
      this->lcaras.empty()) {
    cout << "El archivo " << argumento1 << " no contiene un objeto 3D válido (caras o aristas)"
         << endl;
    exit(1);
  }

  return *this;
}

void Figuras::MostrarListado(list<Figuras> &figura) {
  if (figura.empty()) {
    cout << "  Ningun objeto ha sido cargado en memoria." << endl;
  } else {
    cout << "Hay: " << figura.size() << " objetos en memoria" << endl;
    for (Figuras fig : figura) {
      int ar = 0;
      int aristas_v1[1000] = {0};
      int aristas_v2[1000] = {0};
      cout << fig.ObtenerNombre() << " contiene " << fig.ObtenerNVertices()
           << " vertices, ";
      for (const Caras &cara : fig.ObtenerCaras())
      {
        vector<int> indices = cara.obtenerIndiceVertices();
        for (int i = 0; i < indices.size(); i++) {
          int v1 = indices[i];
          int v2 = indices[(i + 1) % indices.size()];
          if (v1 > v2) {
            int temp = v1;
            v1 = v2;
            v2 = temp;
          }
          bool existe = false;
          for (int j = 0; j < ar; j++) {
            if (aristas_v1[j] == v1 && aristas_v2[j] == v2) {
              existe = true;
              break;
            }
          }
          if (!existe) {
            aristas_v1[ar] = v1;
            aristas_v2[ar] = v2;
            ar++;
          }
        }
      }
      cout << ar << " aristas y " << fig.lcaras.size() << " caras" << endl;
    }
  }
}
void Figuras::Descargar(const string &argumento1, list<Figuras> &figura) {
  bool encontrado = false;
  list<Figuras>::iterator it;
  for (it = figura.begin(); it != figura.end();) {
    if (argumento1 == it->ObtenerNombre()) {
      cout << "El objeto " << argumento1
           << " ha sido eliminado de la memoria de trabajo." << endl;
      it = figura.erase(it);
      encontrado = true;
    } else {
      ++it;
    }
  }

  if (!encontrado) {
    cout << "El objeto " << argumento1 << " no ha sido cargado en memoria."
         << endl;
  }
}

void Figuras::GuardarFigura(const string &argumento1, const string &argumento2,
                            list<Figuras> &figura) {
  list<Figuras>::iterator it;
  bool encontrado = false;

  for (it = figura.begin(); it != figura.end(); ++it) {
    if (argumento1 == it->ObtenerNombre()) {
      cout << "La informacion del objeto " << argumento1
           << " ha sido guardada exitosamente en el archivo " << argumento2
           << endl;
      ofstream salida(argumento2);
      salida << it->ObtenerNombre() << endl;
      salida << it->ObtenerNVertices() << endl;
      for (Vertices vertice : it->ObtenerVertices()) {
        salida << vertice.ObtenerCoorX() << " " << vertice.ObtenerCoorY() << " "
               << vertice.ObtenerCoorZ() << endl;
      }
      for ( Caras cara : it->ObtenerCaras()) {
        salida << cara.obtenerCantidadVertices() << " ";
        for (int i = 0; i < cara.obtenerCantidadVertices(); i++) {
          salida << cara.obtenerIndiceVertices()[i] << " ";
        }
        salida << endl;
      }
      salida << "-1";
      salida.close();
      encontrado = true;
      break;
    }
  }
  if (!encontrado) {
    cout << "El objeto " << argumento1 << " no ha sido cargado en memoria."
         << endl;
  }
}

void Figuras::Envolvente(list<Figuras> &figura, const string &argumento1) {
  if (figura.empty()) {
    cout << "Ningun objeto ha sido cargado en memoria." << endl;
    return;
  }
  float minx = 0, maxx = 0;
  float miny = 0, maxy = 0;
  float minz = 0, maxz = 0;
  list<Vertices> ver;
  list<Caras> car;
  list<Figuras>::iterator it = figura.begin();
  Vertices primerVertice = it->ObtenerVertices().front();
  if (argumento1.empty()) {
    string archivo = "env_global";
    int indice = 0;

    minx = maxx = primerVertice.ObtenerCoorX();
    miny = maxy = primerVertice.ObtenerCoorY();
    minz = maxz = primerVertice.ObtenerCoorZ();
    for (it = figura.begin(); it != figura.end(); ++it) {
      for (Vertices vertice : it->ObtenerVertices()) {
        if (vertice.ObtenerCoorX() < minx)
          minx = vertice.ObtenerCoorX();
        if (vertice.ObtenerCoorX() > maxx)
          maxx = vertice.ObtenerCoorX();
        if (vertice.ObtenerCoorY() < miny)
          miny = vertice.ObtenerCoorY();
        if (vertice.ObtenerCoorY() > maxy)
          maxy = vertice.ObtenerCoorY();
        if (vertice.ObtenerCoorZ() < minz)
          minz = vertice.ObtenerCoorZ();
        if (vertice.ObtenerCoorZ() > maxz)
          maxz = vertice.ObtenerCoorZ();
      }
    }
    ver.push_back(Vertices(indice, minx, miny, minz));
    ver.push_back(Vertices(indice++, maxx, miny, minz));
    ver.push_back(Vertices(indice++, minx, maxy, minz));
    ver.push_back(Vertices(indice++, maxx, maxy, minz));
    ver.push_back(Vertices(indice++, minx, miny, maxz));
    ver.push_back(Vertices(indice++, maxx, miny, maxz));
    ver.push_back(Vertices(indice++, minx, maxy, maxz));
    ver.push_back(Vertices(indice++, maxx, maxy, maxz));

    car.push_back(Caras(4, {0, 1, 3, 2}));
    car.push_back(Caras(4, {0, 2, 6, 4}));
    car.push_back(Caras(4, {6, 7, 5, 4}));
    car.push_back(Caras(4, {1, 3, 7, 5}));
    car.push_back(Caras(4, {0, 1, 5, 4}));
    car.push_back(Caras(4, {2, 3, 7, 6}));

    Figuras envolvente(archivo, 8, ver, car);
    figura.push_back(envolvente);
    cout << "La caja envolvente de los objetos en memoria se ha generado con "
            "el nombre"
         << archivo << " y se ha agregado a los objetos en memoria." << endl;
  } else {
    string archivo = "env_" + argumento1;
    int indice = 0;
    for (; it != figura.end(); it++) {
      if (it->ObtenerNombre() == argumento1) {
        break;
      }
    }
    if (it == figura.end()) {
      cout << " El objeto " << argumento1 << " no ha sido cargado en memoria.";
      return;
    }
    minx = maxx = primerVertice.ObtenerCoorX();
    miny = maxy = primerVertice.ObtenerCoorY();
    minz = maxz = primerVertice.ObtenerCoorZ();
    for (Vertices vertice : it->ObtenerVertices()) {
      if (vertice.ObtenerCoorX() < minx)
        minx = vertice.ObtenerCoorX();
      if (vertice.ObtenerCoorX() > maxx)
        maxx = vertice.ObtenerCoorX();
      if (vertice.ObtenerCoorY() < miny)
        miny = vertice.ObtenerCoorY();
      if (vertice.ObtenerCoorY() > maxy)
        maxy = vertice.ObtenerCoorY();
      if (vertice.ObtenerCoorZ() < minz)
        minz = vertice.ObtenerCoorZ();
      if (vertice.ObtenerCoorZ() > maxz)
        maxz = vertice.ObtenerCoorZ();
    }

    ver.push_back(Vertices(indice, minx, miny, minz));
    ver.push_back(Vertices(indice++, maxx, miny, minz));
    ver.push_back(Vertices(indice++, minx, maxy, minz));
    ver.push_back(Vertices(indice++, maxx, maxy, minz));
    ver.push_back(Vertices(indice++, minx, miny, maxz));
    ver.push_back(Vertices(indice++, maxx, miny, maxz));
    ver.push_back(Vertices(indice++, minx, maxy, maxz));
    ver.push_back(Vertices(indice++, maxx, maxy, maxz));

    car.push_back(Caras(4, {0, 1, 3, 2}));
    car.push_back(Caras(4, {0, 2, 6, 4}));
    car.push_back(Caras(4, {6, 7, 5, 4}));
    car.push_back(Caras(4, {1, 3, 7, 5}));
    car.push_back(Caras(4, {0, 1, 5, 4}));
    car.push_back(Caras(4, {2, 3, 7, 6}));

    Figuras envolvente(archivo, 8, ver, car);
    figura.push_back(envolvente);
    cout << "La caja envolvente del objeto " << argumento1
         << " se ha generado con el nombre " << archivo
         << " y se ha agregado a los objetos en memoria." << endl;
  }
}

void Figuras::Vcercano(list<Figuras> figura, const string &coorx, const string &coory, const string &coorz, const string &nombre) {
    float px = stof(coorx);
    float py = stof(coory);
    float pz = stof(coorz);

    kdtree<Vertices> arbol;
    bool figura_encontrada = false;

    for (list<Figuras>::iterator it = figura.begin(); it != figura.end(); ++it) {
        if (it->ObtenerNombre() == nombre) {
            figura_encontrada = true;
            list<Vertices> vertices = it->ObtenerVertices(); // Ahora obtenemos una copia

            for (list<Vertices>::iterator vertice_it = vertices.begin(); vertice_it != vertices.end(); ++vertice_it) {
                cout << "Insertando vertice: " << vertice_it->ObtenerCoorX() << ", "
                     << vertice_it->ObtenerCoorY() << ", " << vertice_it->ObtenerCoorZ() << endl;

                arbol.insertar(*vertice_it);
            }
            break; // Salir del bucle una vez que se encuentra la figura
        }
    }

    if (!figura_encontrada) {
        cout << "(Objeto no existe) El objeto " << nombre << " no ha sido cargado en memoria." << endl;
        return;
    }

    double menor_distancia = std::numeric_limits<double>::max();
    Vertices punto_buscado(-1, px, py, pz);
    Vertices vertice_cercano;
    vertice_cercano = arbol.encontrarMasCercano(punto_buscado, menor_distancia);

    if (menor_distancia < std::numeric_limits<double>::max()) {
        cout << "(Resultado exitoso) El vertice mas cercano es ("
             << vertice_cercano.ObtenerCoorX() << ", "
             << vertice_cercano.ObtenerCoorY() << ", "
             << vertice_cercano.ObtenerCoorZ() << ") "
             << "del objeto " << nombre << " es el más cercano al punto ("
             << px << ", " << py << ", " << pz << "), a una distancia de "
             << menor_distancia << "." << endl;
    } else {
        cout << "(Error inesperado) No se pudo encontrar un vértice cercano en el objeto " << nombre << "." << endl;
    }
}



void Figuras::insertarVerticeArbol(Vertices& vertice) {
    // Asegúrate de que el árbol está inicializado
    if (arbol.esVacio()) {
        cout << "Error: El árbol no está inicializado." << endl;
        return;
    }

    // Insertar en el árbol k-d
    arbol.insertar(vertice);
}




Figuras::Figuras() : nombre(""), nvertices(0) {}
Figuras::Figuras(const string &nombre, int nvertices,
                 const list<Vertices> &lvertices, const list<Caras> &lcaras)
    : nombre(nombre), nvertices(nvertices), lvertices(lvertices),
      lcaras(lcaras) {}

string Figuras::ObtenerNombre() const { return nombre; }

int Figuras::ObtenerNVertices() const { return nvertices; }

list<Vertices> Figuras::ObtenerVertices() const { return lvertices; }

list<Caras> Figuras::ObtenerCaras() const { return lcaras; }
void Figuras::FijarNombre(const string &nombre) { this->nombre = nombre; }

void Figuras::FijarNVertices(int nvertices) { this->nvertices = nvertices; }

void Figuras::FijarVertices(const list<Vertices> &lvertices) {
  this->lvertices = lvertices;
}

void Figuras::FijarCaras(const list<Caras> &lcaras) { this->lcaras = lcaras; }
