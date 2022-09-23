#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<tCoste> viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice trasbordo);

int main ()
{
    GrafoP<int> GTren ("6tren.txt");
    GrafoP<int> GAutobus ("6autobus.txt");

    cout << "Grafo del autobus: " << endl << GAutobus << endl;
    cout << "Grafo del tren: " << endl << GTren << endl;

    //la ciudad del vertice 2 sera donde se pueda hacer transbordo entre tren y avion
    matriz<tCoste> McosteMinimo = viajar(GTren,GAutobus,2);

    cout << "coste minimo: " << endl << McosteMinimo << endl;

    return 0;
}

matriz<tCoste> viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice ciudad)
{
    bool existeTransbordoaTren = false;
    bool existeTransbordoaBus = false;

    for(size_t i = 0; i < GTren.numVert() ; i++)
    {
        if(GAutobus[ciudad][i] != GrafoP<int>::INFINITO)
        {
            existeTransbordoaBus = true;
        }
        if(GTren[ciudad][i] != GrafoP<int>::INFINITO)
        {
            existeTransbordoaTren = true;
        }
    }

    if(existeTransbordoaBus || existeTransbordoaTren)
    {
        GrafoP<int> Gresultado(GTren.numVert());
        for(size_t i = 0 ; i < Gresultado.numVert() ; i++)
        {
            for(size_t j = 0 ; j < Gresultado.numVert() ; j++)
            {
                Gresultado[i][j] = min(GTren[i][j] , GAutobus[i][j]);
            }
        }

        matriz<vertice> P (Gresultado.numVert());
        matriz<tCoste> McosteMinimo = Floyd(Gresultado,P);
        return McosteMinimo;
    }
    else
    {
        cout << "No es posible hacer un transbordo en la ciudad: " << ciudad << " tendremos que usar o el grafo del tren o el Bus" << endl;
        matriz<vertice> P (GTren.numVert());
        return Floyd(GTren,P);
    }

}