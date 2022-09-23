#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "alg_grafoMA.h"
#include "grafoMA.h"
#include "grafoMA.cpp"
#include "particion.h"
#include "particion.cpp"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;



struct ciudad
{
    double x,y;
};

matriz<double> tombuctu(Grafo& G, vector<ciudad> Vciudad);

int main()
{
    Grafo G("1tom.txt");

    vector<ciudad> Vciudad(5);
    Vciudad[0].x = 3; Vciudad[0].y = 5;
    Vciudad[1].x = 3; Vciudad[1].y = 2;
    Vciudad[2].x = 3; Vciudad[2].y = 1;
    Vciudad[3].x = 1; Vciudad[3].y = -1;
    Vciudad[4].x = 3; Vciudad[4].y = -1;


    matriz<double> res = tombuctu(G,Vciudad); 

    cout << res;

    return 0;
}

matriz<double> tombuctu(Grafo& G, vector<ciudad> Vciudad)
{
    size_t n = G.numVert();
    GrafoP<double> Gresultado(n);
    Particion p(n);

    for(vertice i = 0 ; i < n ; i++)
    {
        for(vertice j = 0 ; j < n ; j++)
        {
            if(G[i][j])
            {
                Gresultado[i][j] = sqrt(pow(Vciudad[i].x - Vciudad[j].x,2) + 
                                        pow(Vciudad[i].y - Vciudad[j].y,2));

                if(p.encontrar(i) != p.encontrar(j))
                {
                    p.unir(i,j);
                }
            }
        }
    }
    cout << Gresultado << endl;

    matriz<vertice> Mver(n);
    matriz<double> Mcoste = Floyd(Gresultado,Mver);
    return Mcoste;

}