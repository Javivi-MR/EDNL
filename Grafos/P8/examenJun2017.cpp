/*

La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha
decretado el cierre a la ciudad como paso de tránsito hacia otras ciudades. (Para ir de una
ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma
empleándola como ciudad destino u origen).

Implemente un subprograma que dada la capital y un grafo ponderado con los km de las
carreteras existentes entre las ciudades del país, nos devuelva los caminos resultantes de
nuestra nueva política “Sin pasar por la capital, por favor”.

Nota impotante: Se ha de definir todos los tipos de dato, prototipo de las operaciones
empleadas en los TADs y también los prototipos de los grafos vistos en clase que se empleen.

*/
#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

using namespace std;


matriz<vertice> CaminoSinCapital(GrafoP<int>& G, vertice capital);

int main()
{
    GrafoP<int> G ("examenJun2017.txt");

    matriz<vertice> M = CaminoSinCapital(G,0);

    cout << "Los caminos son: " << endl << M;

    return 0;
}

matriz<vertice> CaminoSinCapital(GrafoP<int>& G, vertice capital)
{
    GrafoP<int> GsinCapital(G);
    size_t n = G.numVert();
    for(vertice i = 0 ; i < n ; i++)
    {
        GsinCapital[capital][i] = GrafoP<int>::INFINITO;
        GsinCapital[i][capital] = GrafoP<int>::INFINITO;
    }

    matriz<vertice> Mcamino(n);
    matriz<tCoste> Mfloyd = Floyd(GsinCapital,Mcamino);

    vector<vertice> P1(n);
    vector<tCoste> D = Dijkstra(G,capital,P1);

    vector<vertice> P2(n);
    vector<tCoste> DI = DijkstraInv(G,capital,P2);

    for(vertice i = 0; i < n; i++)
    {
        Mfloyd[i][capital] = DI[i];
        Mcamino[i][capital] = P2[i];
    }

    Mfloyd[capital] = D;
    Mcamino[capital] = P1;

    cout << Mfloyd << endl;

   return Mcamino;
}