#include "Comandos.h"
using namespace std;
void Comandos::leerComandos(vector<Comandos> &comandos) {
  ifstream entrada("comandos.txt");
  if (!entrada) {
    cout << "No existe el archivo";
    exit(1);
  }
  Comandos comando;
  while (getline(entrada, comando.nombrede)) {
    getline(entrada, comando.descripcion);
    comandos.push_back(comando);
  }
}

bool Comandos::validarArgumentos(const string &comando, int numArgumentos,
                                 const string &argumento1,
                                 const string &argumento2,const string &argumento3,const string &argumento4,
                                 list<Figuras> &figura) {
  Figuras fi;
  list<string>::iterator it;
  // cargar
  if (comando == "cargar" && numArgumentos == 1) {
    fi = fi.CargarFigura(argumento1);
    for (Figuras f : figura) {
      if (fi.ObtenerNombre() == f.ObtenerNombre()) {
        cout << "El objeto con el nombre " << fi.ObtenerNombre()
             << " ya está en la lista." << endl;
        return true;
      }
    }
    cout << "El objeto " << fi.ObtenerNombre()
         << " ha sido cargado exitosamente desde el archivo " << argumento1;
    figura.push_back(fi);
    return true;
  }
  // listado
  if (comando == "listado" && numArgumentos == 0) {
   fi.MostrarListado(figura);
    return true;
  }

  if (comando == "envolvente" && (numArgumentos == 0 || numArgumentos == 1)) {
    fi.Envolvente(figura, argumento1);
    return true;
  }
  if (comando == "descargar" && numArgumentos == 1) {
 fi.Descargar(argumento1, figura);
    return true;
  }
  if (comando == "guardar" && numArgumentos == 2) {
    fi.GuardarFigura(argumento1, argumento2, figura);
    return true;
  }
  if (comando == "v_cercano" && (numArgumentos == 3 || numArgumentos == 4)) {
    fi.Vcercano(figura,argumento1,argumento2,argumento3,argumento4);
    return true;
  }
  if (comando == "v_cercanos_caja" && numArgumentos == 1) {
    return true;
  }
  if (comando == "ruta_corta" && numArgumentos == 3) {
    return true;
  }
  if (comando == "ruta_corta_centro" && numArgumentos == 2) {
    return true;
  }
  return false;
}

void Comandos::mostrarMensajeFaltanArgumentos(const string &comando) {
  if (comando == "cargar") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: cargar nombre_archivo.txt" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "envolvente" && comando != "envolvente") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: envolvente nombre_objeto" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "descargar") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: descargar nombre_objeto" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "guardar") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: guardar nombre_objeto nombre_archivo.txt" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "v_cercano") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: v_cercano px py pz nombre_objeto" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "v_cercanos_caja") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: v_cercanos_caja nombre_objeto" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "ruta_corta") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: ruta_corta i1 i2 nombre_objeto" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else if (comando == "ruta_corta_centro") {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left
         << "Faltan argumentos: ruta_corta_centro i1 nombre_objeto" << endl;
    cout << "+--------------------------------+" << endl << endl;
  } else {
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| " << setw(20) << left << "ESE COMANDO NO EXISTE" << endl;
    cout << "+--------------------------------+" << endl << endl;
  }
}
Comandos::Comandos() : nombrede(""), descripcion("") {}
Comandos::Comandos(const string &nombrede, const string &descripcion)
    : nombrede(nombrede), descripcion(descripcion) {}
string Comandos::ObtenerNombrede() const { return nombrede; }

string Comandos::ObtenerDescripcion() const { return descripcion; }
void Comandos::FijarNombrede(const string &nombrede) {
  this->nombrede = nombrede;
}

void Comandos::FijarDescripcion(const string &descripcion) {
  this->descripcion = descripcion;
}