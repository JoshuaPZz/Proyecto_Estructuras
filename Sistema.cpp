#include "Sistema.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Sistema::Sistema() : salida(false) {
    Comandos com;
    com.leerComandos(comandos);
}

void Sistema::Iniciar() {
    do {
        leerEntrada();
    } while (!salida);
}

void Sistema::leerEntrada() {
    string opcion;
    cout << "$";
    getline(cin, opcion);

    string comando, argumento1, argumento2, argumento3, argumento4, argumento5;
    istringstream stream(opcion);
    stream >> comando >> argumento1 >> argumento2 >> argumento3 >> argumento4 >> argumento5;

    int numArgumentos =
        (argumento1.empty() ? 0 : 1) + (argumento2.empty() ? 0 : 1) +
        (argumento3.empty() ? 0 : 1) + (argumento4.empty() ? 0 : 1) +
        (argumento5.empty() ? 0 : 1);

    if (opcion == "salir") {
        cout << endl;
        cout << "+--------------------------------+" << endl;
        cout << "| " << setw(20) << left << "SALIENDO DEL PROGRAMA, VUELVA PRONTO" << endl;
        cout << "+--------------------------------+" << endl << endl;
        salida = true;
    } else if (comando == "ayuda") {
        mostrarAyuda(argumento1);
    } else if (Comandos().validarArgumentos(comando, numArgumentos, argumento1, argumento2,argumento3,argumento4, figura)) {
        cout << endl;
    } else if (numArgumentos < 1 ||
               (comando == "guardar" && numArgumentos < 2) ||
               (comando == "v_cercano" && numArgumentos < 3) ||
               (comando == "ruta_corta" && numArgumentos < 3) ||
               (comando == "ruta_corta_centro" && numArgumentos < 2) ||
               (comando == "v_cercanos_caja" && numArgumentos < 1)) {
        Comandos().mostrarMensajeFaltanArgumentos(comando);
    } else {
        cout << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "| " << setw(20) << left << " ESE COMANDO NO EXISTE , POR FAVOR PONER UN COMANDO VALIDO " << endl;
        cout << "+---------------------------------------------------------------+" << endl << endl;
    }
}


void Sistema::mostrarAyuda(const string& argumento1) {
    if (argumento1.empty()) {
        cout << "Estos comandos de shell están definidos internamente. Escribe `ayuda' para ver esta lista." << endl
             << "Escribe `ayuda comando' para obtener más información sobre la función `comando'" << endl << endl;
        cout << setw(80) << "TIENE ESTAS OPCIONES DE COMANDO: " << endl << endl;
        for (int i = 0; i < comandos.size(); i++) {
            cout << "+-----------------------+" << endl;
            cout << "| " << setw(20) << left << comandos[i].ObtenerNombrede() << endl;
            cout << "+-----------------------+" << endl;
            cout << "| " << comandos[i].ObtenerDescripcion() << endl << endl;
        }
    } else {
        int ncom = 0;
        for (int i = 0; i < comandos.size(); i++) {
            string arch1;
            istringstream stream(comandos[i].ObtenerNombrede());
            stream >> arch1;
            if (arch1 == argumento1) {
                cout << endl;
                cout << "+-----------------------+" << endl;
                cout << "| " << setw(20) << left << comandos[i].ObtenerNombrede() << endl;
                cout << "+-----------------------+" << endl;
                cout << "| " << comandos[i].ObtenerDescripcion() << endl << endl;
                ncom++;
            }
        }
        if (ncom == 0) {
            cout << endl;
            cout << "+---------------------------------------------------------------+" << endl;
            cout << "| " << setw(20) << left << " ESE COMANDO NO EXISTE , POR FAVOR PONER UN COMANDO VALIDO " << endl;
            cout << "+---------------------------------------------------------------+" << endl << endl;
        }
    }
}
