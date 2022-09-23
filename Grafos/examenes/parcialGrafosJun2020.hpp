#ifndef PARCIALGRAFOS_HPP
#define PARCIALGRAFOS_HPP

#include <vector>
#include <algorithm>

#include "lib/alg_grafoPMC.h"
#include "lib/grafoPMC.h"

typedef double tCoste;

typedef typename GrafoP<tCoste>::vertice vertice;

int Pedido() { return 0; }

bool faltanClientes(const std::vector<bool>& clientesServidos)
{
    bool res = true;

    for( bool e : clientesServidos )
        res = res && e;
    
    return res;
}

vertice proximoCliente(const matriz<tCoste>& carreteras, const std::vector<bool>& clientesServidos, const vertice& clienteActual, const vertice& central, tCoste& distanciaTotal)
{
	tCoste carreteraMin = GrafoP<tCoste>::INFINITO;
	vertice clienteMin;
	
	for( int i = 0; i < carreteras.dimension(); ++i )
		if( carreteras[clienteActual][i] < carreteraMin && !clientesServidos[i] )
        {
			carreteraMin = carreteras[clienteActual][i];
			clienteMin = i;
		}
	
	return (clienteMin);
}


tCoste repartidor(const GrafoP<tCoste>& G, const vertice& central, int capacidadMax)
{
    matriz<vertice> P;
    matriz<tCoste> carreteras = Floyd(G, P);

    tCoste distanciaTotal = 0;

    std::vector<bool> clientesServidos(G.numVert(), false);
    clientesServidos[central] = true;

    vertice clienteActual = central;

    int capacidadActual = capacidadMax;

    while( !faltanClientes(clientesServidos) )
    {
        if( clienteActual == central )
        {
            capacidadActual = capacidadMax;
            clienteActual = proximoCliente(carreteras, clientesServidos, clienteActual, central, distanciaTotal);
        }
        else
            if( capacidadActual - Pedido() <= 0 )
            {
                capacidadActual = 0;
                distanciaTotal += carreteras[clienteActual][central];
                clienteActual = central;
            }
            else
            {
                capacidadActual -= Pedido();
                clientesServidos[clienteActual] = true;

                clienteActual = proximoCliente(carreteras, clientesServidos, clienteActual, central, distanciaTotal);
            }
    }

    return distanciaTotal;
}

#endif   // PARCIALGRAFOS_HPP