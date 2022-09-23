/*
        0     1     2    
     /  E               \
  0  | ___              |
  1  |    |      |      |
  2  |  S  ¯¯¯¯¯¯       |


P1 -> origen [0][0] || destino [1][0]
P2 -> origen [0][1] || destino [1][1]
P3 -> origen [1][1] || destino [1][2]
P4 -> origen [2][0] || destino [2][1]

*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct casilla
{
    int x,y;    //fila será x y columna será y
};

struct pared
{
    casilla origen, destino;
};

struct path
{
    tCoste costeTotal;
    GrafoP<tCoste>::tCamino origenToDestino;
};

using namespace std;


path laberinto(size_t& N,vector<pared>& paredes, casilla& entrada, casilla& salida);
vertice CasillaToNodo(casilla c,size_t N);
casilla NodoToCasilla(vertice v,size_t N);
bool abyacentes (casilla c1, casilla c2);

int main()
{
    size_t N = 3; //Tamaño del laberinto 3

    // DEFINICION DE LA PAREDES
    vector<pared> paredes(4);
    pared p1,p2,p3,p4;
    p1.origen.x=0; p1.origen.y=0; p1.destino.x=1; p1.destino.y=0;
    p2.origen.x=1; p2.origen.y=0; p2.destino.x=1; p2.destino.y=1;
    p3.origen.x=1; p3.origen.y=1; p3.destino.x=2; p3.destino.y=1;
    p4.origen.x=1; p4.origen.y=1; p4.destino.x=1; p4.destino.y=2;

    paredes[0]=p1; paredes[1]=p2; paredes[2]=p3; paredes[3]=p4;
    // FIN DEFINICION DE PAREDES

    casilla entrada,salida;
    entrada.x = 0; entrada.y = 0;
    salida.x = 2; salida.y = 0;


    path resultado = laberinto(N,paredes,entrada,salida);

    Lista<vertice>::posicion p = resultado.origenToDestino.primera();

   cout << "El coste minimo para completar el laberinto es de: " << resultado.costeTotal << endl << "Ademas el camino a seguir es: ";
   while(p != resultado.origenToDestino.fin())
   {
        cout << resultado.origenToDestino.elemento(p) << " ";
        p = resultado.origenToDestino.siguiente(p);
   }

    return 0;
}

path laberinto(size_t& N,vector<pared>& paredes, casilla& entrada, casilla& salida)
{
    GrafoP<int> G(N*N); // El grafo deber ser de N*N ya que el laberinto tiene 9 vertices que

    for(vertice i = 0; i < N*N ; i++)
    {
        G[i][i] = 0; // el coste de un vertice a el mismo es 0 :)
    
        for(vertice j = 0 ; j < N*N ; j++)
        {
            if(abyacentes(NodoToCasilla(i,N),NodoToCasilla(j,N)))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    
    for(size_t i = 0; i < paredes.size(); i++)
    {
        casilla origen = paredes[i].origen;
        casilla destino = paredes[i].destino;

        vertice v1 = CasillaToNodo(origen,N);
        vertice v2 = CasillaToNodo(destino,N);


        G[v1][v2] = GrafoP<int>::INFINITO;
        G[v2][v1] = GrafoP<int>::INFINITO;
    }


    //Esta manera es mas costosa ya que usamos Floyd que es de orden O(n^3)
    /*
    vertice o = CasillaToNodo(entrada,N);
    vertice d = CasillaToNodo(salida,N);

    matriz<vertice> P(G.numVert());
    matriz<tCoste> Mcostes = Floyd(G,P);

    return Mcostes[o][d];
    */

   //Una manera menos costosa es usando djikstra ya que es de orden O(n^2)
    vertice o = CasillaToNodo(entrada,N);
    vertice d = CasillaToNodo(salida,N);

    vector<vertice> P(G.numVert());
    vector<tCoste> D = Dijkstra(G,o,P);
    path C;
    C.costeTotal = D[d];
    GrafoP<tCoste>::tCamino ruta = camino<GrafoP<size_t>::vertice>(o,d,P);
    C.origenToDestino = ruta;

    return C;

    //otra manera seria con Dijkstra Inverso:
    /*
    vertice o = CasillaToNodo(entrada,N);
    vertice d = CasillaToNodo(salida,N);

    vector<vertice> P(G.numVert());
    vector<tCoste> D = DijkstraInv(G,d,P);

    return D[o];
    */

}

vertice CasillaToNodo(casilla c,size_t N)
{
    vertice v = (c.x * N) + c.y;
    return v;
}

casilla NodoToCasilla(vertice v,size_t N)
{
    casilla c;
    c.x = v / N;
    c.y = v % N;

    return c;
}

bool abyacentes (casilla c1, casilla c2)
{
    return (abs(c1.x - c2.x) + abs(c1.y - c2.y) == 1);
}