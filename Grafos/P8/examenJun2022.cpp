/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha
decretado el cierre a la ciudad como paso de tránsito hacia otras ciudades. (Para ir de una
ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma
empleándola como ciudad destino u origen).

Sin embargo esto podria ocasionar traslados mas largos y el consecuente descontento del viajero zuelandes,
asi como un incremento de la contaminacion eb todo el pais. Por esa razon, el gobierno solo tomara esta medida
si el coste total adicional en km recorridos por los conductores zueladeces con motivo de la medida anticontaminacion
no exceden a una cantidad de km determinada. Para poder estimar/calcular el numero total de km adicionales se dispone del
numero de viajes diarios que se realizan entre cualquieras dos ciudades de Zuelandia 
(obviamente, el numero de viajes diarios podrá ser distintos para dos pares diferentes de ciudades de Zuelandia).

Asi pues, dados los siguientes datos
    o La capital de Zuelandia
    o El Grafo con los km de cada carretera del est
    o Los viajes diarios que se estima que se realizan entre todos los pares de ciudades del pais
    o El numero maximo del total de km adicionales que se acepta realizar para implementar la medida

Implementa un subprograma que calcule y devuelva el numero de km adicionales que provocara la implantacion de la medida anticontaminacion
y si debe implementarse dicha medida o no, de acuerdo al criterio anteriormente descrito.
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

struct decision
{
    tCoste numKilometrosTotal;
    bool aceptar; //true si si, false si no
};

decision KmSinCapital(GrafoP<int>& G, vertice capital, matriz<int> numViajes, int maximoKm);
tCoste kmTotales(matriz<tCoste> Mfloyd, matriz<int> numViajes,size_t n);


int main()
{
    GrafoP<int> G("examenJun2022.txt");

    vertice capital = 0;
    
    matriz<int> numViajes(G.numVert());
    for(int i = 0; i < G.numVert(); i++) 
    {
        numViajes[i][i] = 0;
    }
    numViajes[0][1] = 2; numViajes[0][2] = 5; numViajes[0][3] = 5; numViajes[0][4] = 2;
    numViajes[1][0] = 1; numViajes[1][2] = 3; numViajes[1][3] = 1; numViajes[1][4] = 2;
    numViajes[2][0] = 2; numViajes[2][1] = 1; numViajes[2][3] = 1; numViajes[2][4] = 1;
    numViajes[3][0] = 0; numViajes[3][1] = 0; numViajes[3][2] = 0; numViajes[3][4] = 2;
    numViajes[4][0] = 2; numViajes[4][1] = 0; numViajes[4][2] = 0; numViajes[4][3] = 0;


    int maximoKm = 145;

    decision d = KmSinCapital(G,capital,numViajes,maximoKm);

    if(d.aceptar)
    {
        cout << "el num de km que se realizaria seria de: " << d.numKilometrosTotal << " y es menor que el maximo: " << maximoKm << endl;
    }
    else
    {
        cout << "el num de km que se realizaria seria de: " << d.numKilometrosTotal << " y es mayor o igual que el maximo: " << maximoKm << endl;
    }

    return 0;
}

decision KmSinCapital(GrafoP<int>& G, vertice capital, matriz<int> numViajes, int maximoKm)
{
    size_t n = G.numVert();
    GrafoP<int> GsinCapital(G);
    matriz<vertice> Mver1(n);
    matriz<tCoste> FloydAntes = Floyd(G,Mver1);
    int kmtotalesAntes = kmTotales(FloydAntes,numViajes,n);
    
    for(vertice i = 0; i < n; i++)
    {
        GsinCapital[i][capital] = GrafoP<int>::INFINITO;
        GsinCapital[capital][i] = GrafoP<int>::INFINITO;
    }

    matriz<vertice> Mver(n);
    matriz<tCoste> Mfloyd = Floyd(GsinCapital,Mver);

    vector<vertice> P1(n);
    vector<tCoste> D = Dijkstra(G,capital,P1);
    
    vector<vertice> P2(n);
    vector<tCoste> DI = DijkstraInv(G,capital,P2);

    
    for(size_t i = 0 ; i < n ; i++)
    {
        Mfloyd[i][capital] = DI[i];
    }
    
    Mfloyd[capital] = D;

    decision d;

    d.numKilometrosTotal = kmTotales(Mfloyd,numViajes,n);
    d.aceptar = (d.numKilometrosTotal < maximoKm + kmtotalesAntes);

    return d;
}


tCoste kmTotales(matriz<tCoste> Mfloyd, matriz<int> numViajes,size_t n)
{
    tCoste sumkm = 0;

    for(size_t i = 0; i < n ; i++)
    {
        for(size_t j = 0; j < n ; j++)
        {
            if(i != j && Mfloyd[i][j] != GrafoP<int>::INFINITO)
            {
                sumkm = sumkm + Mfloyd[i][j] * numViajes[i][j];
            }
        }
    }
    return sumkm;
}