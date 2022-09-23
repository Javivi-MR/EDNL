/*
El archipielago de Grecoland (Nozuelandia) está formado unicamente por tres islas, Fobos, Deimos y Europa y tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.

Se dispone de la relacion de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. Las condiciones del programa COMUNICA indican que se sufragaran
todos los costes de construcción de las comunicaciones (carreteras y puentes) al menor coste posible.

Se sabe que la mera construccion de un puente o carretera ya implica una serie de costes fijos, que difieren para el caso de carretera y puente.
Además, el coste por unidad de longitud para carreteras y puentes tambien es distinto.

En estas condiciones se debe calcular (mediante una funcion) que carreteras y puentes deben construirse para comunicar entre si todas las ciudades de Grecoland, dados los siguientes datos:

    1. Relacion de las ciudades de Fobos, representadas mediante sus coordenadas cartesianas
    2. Relacion de las ciudades de Deimos, representadas mediante sus coordenadas cartesianas
    3. Relacion de las ciudades de Europa, representadas mediante sus coordenadas cartesianas
    4. Coste inicial de construccion de un puente
    5. Coste inicial de construccion de una carreteras
    6. Coste adicional por unidad de longitud de construccion de un puente
    7. Coste adicional por unidad de longitud de construccion de una carretera
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>
#include <cmath>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

using namespace std;

struct ciudad
{
    double x,y;
};

struct puente
{
    vertice v1,v2;
    ciudad c1,c2;
    double coste;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x),2) + pow(abs(c1.y - c2.y),2));
}

double construirGrecoland(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<ciudad> ciudadesEuropa, double CosteFijoPuente, double CosteFijoCarretera, double CosteVarLongitudPuente, double CosteVarLongitudCarretera);
puente mejorPuente(vector<ciudad> ciudadesFobos,vector<ciudad> ciudadesDeimos,vector<ciudad> ciudadesEuropa, int& aux);

int main()
{
    vector<ciudad> ciudadesFobos(4);
    ciudadesFobos[0].x = 2; ciudadesFobos[0].y = 3;
    ciudadesFobos[1].x = 3; ciudadesFobos[1].y = 3;
    ciudadesFobos[2].x = 4; ciudadesFobos[2].y = 3;
    ciudadesFobos[3].x = 6; ciudadesFobos[3].y = 3;

    vector<ciudad> ciudadesDeimos(3);
    ciudadesDeimos[0].x = 4; ciudadesDeimos[0].y = -2;
    ciudadesDeimos[1].x = 4; ciudadesDeimos[1].y = -3;
    ciudadesDeimos[2].x = 4; ciudadesDeimos[2].y = -5;

    vector<ciudad> ciudadesEuropa(3);
    ciudadesEuropa[0].x = 6; ciudadesEuropa[0].y = -2;
    ciudadesEuropa[1].x = 7; ciudadesEuropa[1].y = -2;
    ciudadesEuropa[2].x = 9; ciudadesEuropa[2].y = -2;

    double CosteFijoPuente = 10;
    double CosteFijoCarretera = 5;

    double CosteVarLongitudPuente = 2;
    double CosteVarLongitudCarretera = 1;

    double costeTotal = construirGrecoland(ciudadesFobos,ciudadesDeimos,ciudadesEuropa,CosteFijoPuente,CosteFijoCarretera,CosteVarLongitudPuente,CosteVarLongitudCarretera);

    cout << "El coste total de la construccion es de: " << costeTotal;

    return 0;
}

double construirGrecoland(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<ciudad> ciudadesEuropa, double CosteFijoPuente, double CosteFijoCarretera, double CosteVarLongitudPuente, double CosteVarLongitudCarretera)
{
    size_t n1 = ciudadesFobos.size();
    size_t n2 = ciudadesDeimos.size();
    size_t n3 = ciudadesEuropa.size();
    double CosteConstruccion = 0;

    //FOBOS----------------------------------------------------------------------------------------------------------------
    GrafoP<double> GFobos(n1);
    for(vertice i = 0 ; i < n1 ; i++) 
    {
        for(vertice j = 0 ; j < n1 ; j++)
        {
            if(i != j)
            {
                GFobos[i][j] = distancia(ciudadesFobos[i],ciudadesFobos[j]);
            }
        }
    }
    GrafoP<double> GFobosPrim = Prim(GFobos);
    for(vertice i = 0 ; i < n1 ; i++) 
    {
        for(vertice j = 0 ; j < n1 ; j++)
        {
            if(GFobosPrim[i][j] != GrafoP<double>::INFINITO)
            {
                CosteConstruccion = CosteConstruccion + CosteFijoCarretera + (GFobosPrim[i][j] * CosteVarLongitudCarretera);    //carreteras de Fobos construidas al MENOR coste :)
            }
        }
    }
    //---------------------------------------------------------------------------------------------------------------------
    //DEIMOS --------------------------------------------------------------------------------------------------------------
    GrafoP<double> GDeimos(n2);
    for(vertice i = 0 ; i < n2 ; i++) 
    {
        for(vertice j = 0 ; j < n2 ; j++)
        {
            if(i != j)
            {
                GDeimos[i][j] = distancia(ciudadesDeimos[i],ciudadesDeimos[j]);
            }
        }
    }
    GrafoP<double> GDeimosPrim = Prim(GDeimos);
    for(vertice i = 0 ; i < n2 ; i++) 
    {
        for(vertice j = 0 ; j < n2 ; j++)
        {
            if(GDeimosPrim[i][j] != GrafoP<double>::INFINITO)
            {
                CosteConstruccion = CosteConstruccion + CosteFijoCarretera + (GDeimosPrim[i][j] * CosteVarLongitudCarretera);   //carreteras de Deimos construidas al MENOR coste :)
            }
        }
    }
    //--------------------------------------------------------------------------------------------------------------------
    //EUROPA--------------------------------------------------------------------------------------------------------------
    GrafoP<double> GEuropa(n3);
    for(vertice i = 0 ; i < n3 ; i++) 
    {
        for(vertice j = 0 ; j < n3 ; j++)
        {
            if(i != j)
            {
                GEuropa[i][j] = distancia(ciudadesEuropa[i],ciudadesEuropa[j]);
            }
        }
    }
    GrafoP<double> GEuropaPrim = Prim(GEuropa);
    for(vertice i = 0 ; i < n3 ; i++) 
    {
        for(vertice j = 0 ; j < n3 ; j++)
        {
            if(GEuropaPrim[i][j] != GrafoP<double>::INFINITO)
            {
                CosteConstruccion = CosteConstruccion + CosteFijoCarretera + (GEuropaPrim[i][j] * CosteVarLongitudCarretera);   //carreteras de Europa construidas al MENOR coste :)
            }
        }
    }
    //--------------------------------------------------------------------------------------------------------------------
    //Construyamos ahora un grafo que contenga a las tres islas
    GrafoP<double> Grecoland(n1+n2+n3);
    for(vertice i = 0 ; i < n1 ; i++) 
    {
        for(vertice j = 0 ; j < n1 ; j++)
        {
            Grecoland[i][j] = GFobosPrim[i][j];
        }
    }
    for(vertice i = n1 ; i < n1+n2 ; i++) 
    {
        for(vertice j = n1 ; j < n1+n2 ; j++)
        {
            Grecoland[i][j] = GDeimosPrim[i-n1][j-n1];
        }
    }
    for(vertice i = n1+n2 ; i < n1+n2+n3 ; i++) 
    {
        for(vertice j = n1+n2 ; j < n1+n2+n3 ; j++)
        {
            Grecoland[i][j] = GEuropaPrim[i-n1-n2][j-n1-n2];
        }
    }

    int aux = 0;//queremos compara todas las islas
    puente p = mejorPuente(ciudadesFobos,ciudadesDeimos,ciudadesEuropa,aux);
    if(aux == 1) //Fobos y Deimos
    {
        p.v2 = p.v2 + n1;
    }
    if(aux == 2)//Fobos y Europa
    {
        p.v2 = p.v2 + n1 + n2;
    }
    if(aux == 3)//Deimos y Europa
    {
        p.v1 = p.v1 + n1;
        p.v2 = p.v2 + n1 + n2;
    }

    Grecoland[p.v1][p.v2] = p.coste; //construimos puente ida
    CosteConstruccion = CosteConstruccion + CosteFijoPuente + (CosteVarLongitudPuente * p.coste);
    Grecoland[p.v2][p.v1] = p.coste; //construimos puente vuelta
    CosteConstruccion = CosteConstruccion + CosteFijoPuente + (CosteVarLongitudPuente * p.coste);

    puente p2 = mejorPuente(ciudadesFobos,ciudadesDeimos,ciudadesEuropa,aux);
    if(aux == 1) //Fobos y Deimos
    {
        p2.v2 = p2.v2 + n1;
    }
    if(aux == 2)//Fobos y Europa
    {
        p2.v2 = p2.v2 + n1 + n2;
    }
    if(aux == 3)//Deimos y Europa
    {
        p2.v1 = p2.v1 + n1;
        p2.v2 = p2.v2 + n1 + n2;
    }
    Grecoland[p2.v1][p2.v2] = p2.coste;
    CosteConstruccion = CosteConstruccion + CosteFijoPuente + (CosteVarLongitudPuente * p2.coste);
    Grecoland[p2.v2][p2.v1] = p2.coste;
    CosteConstruccion = CosteConstruccion + CosteFijoPuente + (CosteVarLongitudPuente * p2.coste);

    cout << "El grafo de Grecoland quedaria asi: " << endl << Grecoland << endl;

    return CosteConstruccion;
}

puente mejorPuente(vector<ciudad> ciudadesFobos,vector<ciudad> ciudadesDeimos,vector<ciudad> ciudadesEuropa, int& aux)
{
    if(aux == 0)    //comparamos todas las islas
    {
        puente paux;
        paux.coste = GrafoP<double>::INFINITO;
        //Primero comparamos Fobos y Deimos
        for(size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesDeimos.size(); j++)
            {
                double costeaux = distancia(ciudadesFobos[i],ciudadesDeimos[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesFobos[i];
                    paux.c2 = ciudadesDeimos[j];
                    aux = 1; // si es 1 significara que se construyo puente entre Fobos y Deimos
                }   
            }
        }
        //salimos con el mejor puente entre Fobos y Deimos

        //ahora comparamos el anterior puente con el puente que puede construirse entre Fobos y Europa
        for(size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesEuropa.size(); j++)
            {
                double costeaux = distancia(ciudadesFobos[i],ciudadesEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesFobos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 2; // si es 2 significara que se construyo puente entre Fobos y Europa
                }   
            }
        }
        //salimos (o no) con el mejor puente entre Fobos y Deimos

        //por ultimo comparamos el anterior puente con el puente que puede construirse entre Deimos y Europa
        for(size_t i = 0; i < ciudadesDeimos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesEuropa.size(); j++)
            {
                double costeaux = distancia(ciudadesDeimos[i],ciudadesEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesDeimos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 3; // si es 3 significara que se construyo puente entre Deimos y Europa
                }   
            }
        }
        //llegados aqui paux deberia ser el puente con menor coste entre las 3 islas (CUIDAO' solo conecta 2, hay que buscar otro)
        return paux;
    }
    if(aux == 1)//si el puente existente está entre Fobos y Deimos el puente faltante esta entre Fobos y Europa o Deimos y Europa
    {
        puente paux;
        paux.coste = GrafoP<double>::INFINITO;
        //FOBOS - EUROPA
        for(size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesEuropa.size(); j++)
            {
                double costeaux = distancia(ciudadesFobos[i],ciudadesEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesFobos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 2; // si es 2 significara que se construyo puente entre Fobos y Europa
                }   
            }
        }
        //DEIMOS - EUROPA
        for(size_t i = 0; i < ciudadesDeimos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesEuropa.size(); j++)
            {
                double costeaux = distancia(ciudadesDeimos[i],ciudadesEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesDeimos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 3; // si es 2 significara que se construyo puente entre Deimos y Europa
                }   
            }
        }
        return paux;
    }
    if(aux == 2)//si el puente existente está entre Fobos y Europa el puente faltante esta entre Fobos y Deimos o Deimos y Europa
    {
        puente paux;
        paux.coste = GrafoP<double>::INFINITO;
        //Fobos - Deimos
        for(size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesDeimos.size(); j++)
            {
                double costeaux = distancia(ciudadesFobos[i],ciudadesDeimos[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesFobos[i];
                    paux.c2 = ciudadesDeimos[j];
                    aux = 1; // si es 1 significara que se construyo puente entre Fobos y Deimos
                }   
            }
        }
        //Deimos - Europa
        for(size_t i = 0; i < ciudadesDeimos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesEuropa.size(); j++)
            {
                double costeaux = distancia(ciudadesDeimos[i],ciudadesEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesDeimos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 3; // si es 2 significara que se construyo puente entre Deimos y Europa
                }   
            }
        }
        return paux;
    }
    if(aux == 3)//si el puente existente está entre Deimos y Europa el puente faltante esta entre Fobos y Deimos o Fobos y Europa
    {
        puente paux;
        paux.coste = GrafoP<double>::INFINITO;        
        //FOBOS - Deimos
        for(size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesDeimos.size(); j++)
            {
                double costeaux = distancia(ciudadesFobos[i],ciudadesDeimos[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesFobos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 1; // si es 1 significara que se construyo puente entre Fobos y Deimos
                }   
            }
        }
        //FOBOS - EUROPA
        for(size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            for(size_t j = 0 ; j < ciudadesEuropa.size(); j++)
            {
                double costeaux = distancia(ciudadesFobos[i],ciudadesEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.v1 = i;
                    paux.v2 = j;
                    paux.c1 = ciudadesFobos[i];
                    paux.c2 = ciudadesEuropa[j];
                    aux = 2; // si es 2 significara que se construyo puente entre Fobos y Europa
                }   
            }
        }
        return paux;
    }
}