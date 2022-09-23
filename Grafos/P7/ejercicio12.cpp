#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct puente
{
    vertice v1,v2;
};

puente unir(GrafoP<int>& GFobos,GrafoP<int>& GDeimos, vector<vertice> CosterasF , vector<vertice> CosterasD);
tCoste costeGlobal(matriz<tCoste> M,size_t nf, size_t nd);

int main()
{
    GrafoP<int> GFobos("12fobos.txt");
    GrafoP<int> GDeimos("12deimos.txt");
    vector<vertice> CosterasF(2);
    CosterasF[0] = 1; CosterasF[1] = 2;
    vector<vertice> CosterasD(3);
    CosterasD[0] = 0; CosterasD[1] = 1; CosterasD[2] = 2;

    puente p = unir(GFobos,GDeimos,CosterasF,CosterasD);

    cout << "el puente ira desde la ciudad " << p.v1 << " de Fobos, hasta la ciudad " << p.v2 << endl;" de Deimos.";

    return 0;
}

puente unir(GrafoP<int>& GFobos,GrafoP<int>& GDeimos, vector<vertice> CosterasF , vector<vertice> CosterasD)
{
    size_t nf = GFobos.numVert();
    size_t nd = GDeimos.numVert();

    GrafoP<int> G(nf + nd);

    matriz<tCoste> M;
    matriz<vertice> Mver(nf + nd);

    vertice v1,v2;

    for(vertice i = 0 ; i < nf ; i++)
    {
        for(vertice j = 0 ; j < nf ; j++)
        {
            G[i][j] = GFobos[i][j];
        }
    }

    for(vertice i = nf ; i < nf + nd ; i++)
    {
        for(vertice j = nf ; j < nf + nd ; j++)
        {
            G[i][j] = GDeimos[i-nf][j-nf];
        }
    }


    tCoste minimo = GrafoP<int>::INFINITO;
    tCoste coste;
    puente p;

    //normalizamos el vector de costeras en Deimos
    for (size_t i = 0; i < CosterasD.size() ; i++)
    {
        CosterasD[i] = CosterasD[i] + nf;
    }
    cout << CosterasD;
    //buscamos el puente mejor
    for (size_t i = 0; i < CosterasF.size() ; i++)
    {
        for (size_t j = 0; j < CosterasD.size() ; j++)
        {
            
            G[CosterasF[i]][CosterasD[j]] = 0;
            G[CosterasD[j]][CosterasF[i]] = 0;
            M = Floyd(G,Mver);
            //cout << M << endl;
            coste = costeGlobal(M,nf,nd);
            //cout << "COSTE DE LA MATRIZ: " << coste << endl << endl;
            if (coste < minimo)
            {
                minimo = coste;
                v1 = CosterasF[i];
                v2 = CosterasD[j];
            }
            G[CosterasF[i]][CosterasD[j]] = GrafoP<int>::INFINITO;
            G[CosterasD[j]][CosterasF[i]] = GrafoP<int>::INFINITO;
        }
    }

    p.v1 = v1;
    p.v2 = v2;

    return p;
}

tCoste costeGlobal(matriz<tCoste> M,size_t nf, size_t nd)
{
    tCoste sum = 0;
    for(vertice i = 0; i < nf + nd ; i++)
    {
        for(vertice j = 0; j < nf + nd ; j++)
        {
            if(M[i][j] != GrafoP<int>::INFINITO)
            {
                sum = sum + M[i][j];
            }
        }
    } 
    return sum;
}