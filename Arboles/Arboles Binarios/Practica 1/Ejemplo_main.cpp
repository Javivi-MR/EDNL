#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#'; // Fin de lectura.

int main ()
{
    Abin<tElto> A, B;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    fs.close();

    cout << "\n*** Arbol A guardado en fichero abin.dat ***\n";

    cout << "\n*** Lectura de arbol binario B de abin.dat ***\n";

    ifstream fe("abin.dat"); // Abrir fichero de entrada.

    rellenarAbin(fe, B); // Desde fichero.

    fe.close();

    cout << "\n*** Mostrar arbol binario B ***\n";
    
    imprimirAbin(B); // En std::cout
} 