/*
Ejercicio 3:
Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la
lista de posibles subvenciones del Ministerio de Fomento en la que una de las más
jugosas se concede a las empresas cuyo grafo asociado a su matriz de costes sea
acíclico. ¿Puedes pedir esta subvención?
Implementa un subprograma que a partir de la matriz de costes nos indique si tu
empresa tiene derecho a dicha subvención.
*/

#include <iostream>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"
#include "matriz.h"

using namespace std;

bool subvencion(GrafoP<int>& G);
bool tieneciclo(GrafoP<int>& G, GrafoP<int>::vertice v);

int main()
{

    GrafoP<int> G ("3.txt");

    bool result = subvencion(G); //devuelve true si puede obtener la subvención(es aciclico) y false si no

    if(result)
    {
        cout << "Puede obtener la subvencion" << endl;
    }
    else
    {
        cout << "NO puede obtener la subvencion" << endl;
    }

    return 0;
}

bool subvencion(GrafoP<int>& G)
{
    typedef GrafoP<int>::vertice vertice;
    typedef GrafoP<int>::tCoste tCoste;
    size_t n = G.numVert();
    matriz<tCoste> Mcoste = FloydMod(G);  // FloydMod hace lo mismo que floyd pero este busca un camino mas corto del 0-0 ya que al principio es infinito y si se encuentra un camino mas corto implica que hay 
    bool aciclico = true;
    cout << Mcoste << endl;
    for(vertice i = 0; i < n; i++)
    {
        if(Mcoste[i][i] != GrafoP<int>::INFINITO)
        {
            aciclico = false;
        }
    }
    return aciclico;
}
