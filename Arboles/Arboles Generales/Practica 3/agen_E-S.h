#ifndef AGEN_E_S_H
#define AGEN_E_S_H

#include <cassert>
#include <iostream>
#include <fstream>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

template <typename T>
void rellenarAgen(Agen<T>& A, const T& fin)
// Pre: A está vacío.
// Post: Rellena el árbol A con la estructura y elementos
//       leídos en preorden de la entrada estándar, usando
//       fin como elemento especial para introducir nodos nulos.
{
   T e;

   assert(A.arbolVacio());
   cout << "Raíz (Fin = " << fin << "): "; cin >> e;
   if (e != fin) {
      A.insertarRaiz(e);
      rellenarDescendientes(A.raiz(), A, fin);
   }
}

template <typename T>
void rellenarDescendientes(typename Agen<T>::nodo n, Agen<T>& A, const T& fin)
// Pre: n es un nodo hoja de A.
// Post: Lee de la entrada estándar y en preorden los descendientes de n,
//       usando fin para introducir nodos nulos.
{
   T ehi, ehd;

   assert(A.hijoIzqdo(n) == Agen<T>::NODO_NULO);
   cout << "Hijo izqdo. de " << A.elemento(n)
        << " (Fin = " << fin << "): ";
   cin >> ehi;
   if (ehi != fin) {
      A.insertarHijoIzqdo(n, ehi);
      rellenarDescendientes(A.hijoIzqdo(n), A, fin);
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      cout << "Hermano drcho. de " << A.elemento(hijo)
           << " (Fin = " << fin << "): ";
      cin >> ehd;
      while (ehd != fin) {
         A.insertarHermDrcho(hijo, ehd);
         rellenarDescendientes(A.hermDrcho(hijo), A, fin);
         hijo = A.hermDrcho(hijo);
         cout << "Hermano drcho. de " << A.elemento(hijo)
              << " (Fin = " << fin << "): ";
         cin >> ehd;
      }
   }
}

template <typename T>
void rellenarAgen(istream& is, Agen<T>& A)
// Pre: A está vacío.
// Post: Extrae los nodos de A del flujo de entrada is,
//       que contendrá el elemento especial que denota
//       un nodo nulo seguido de los elementos en preorden,
//       incluyendo los correspondientes a nodos nulos.
{
   T e, fin;

   assert(A.arbolVacio());
   if (is >> fin && is >> e && e != fin) {
      A.insertarRaiz(e);
      rellenarDescendientes(is, A.raiz(), A, fin);
   }
}

template <typename T>
void rellenarDescendientes(istream& is, typename Agen<T>::nodo n, Agen<T>& A, const T& fin)
// Pre: n es un nodo hoja de A.
// Post: Lee del flujo de entrada is y en preorden los descendientes de n,
//       usando fin para los nodos nulos.
{
   T ehi, ehd;

   assert(A.hijoIzqdo(n) == Agen<T>::NODO_NULO);
   if (is >> ehi && ehi != fin) {
      A.insertarHijoIzqdo(n, ehi);
      rellenarDescendientes(is, A.hijoIzqdo(n), A, fin);
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      while (is >> ehd && ehd != fin) {
         A.insertarHermDrcho(hijo, ehd);
         rellenarDescendientes(is,A.hermDrcho(hijo), A, fin);
         hijo = A.hermDrcho(hijo);
      }
   }
}

template <typename T>
void imprimirAgen(const Agen<T>& A)
// Post: Muestra los nodos de A en la salida estándar
{
   if (!A.arbolVacio())
   {
      cout << "Raiz del arbol: "
           << A.elemento(A.raiz()) << endl;
      imprimirDescendientes(A.raiz(), A);
   }
   else
      cout << "Arbol vacio\n";
}

template <typename T>
void imprimirDescendientes(typename Agen<T>::nodo n, const Agen<T>& A)
// Post: Muestra los descendientes de n en la salida estándar.
{
   if (A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
   {
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      cout << "Hijo izqdo de " << A.elemento(n) << ": "
           << A.elemento(hijo) << endl;
      while (hijo != Agen<T>::NODO_NULO) {
         imprimirDescendientes(hijo, A);
         if (A.hermDrcho(hijo) != Agen<T>::NODO_NULO)
            cout << "Hermano derecho de " << A.elemento(hijo) << ": "
                 << A.elemento(A.hermDrcho(hijo)) << endl;
         hijo = A.hermDrcho(hijo);
      }
   }
}

template <typename T>
void imprimirAgen(ostream& os, const Agen<T>& A, const T& fin)
// Post: Inserta en el flujo de salida os los nodos de A en preorden,
//       precedidos del elemento especial usado para denotar un nodo nulo.
{
   if (!A.arbolVacio())
   {
      os << fin << endl
         << A.elemento(A.raiz()) << ' ';
      imprimirDescendientes(os, A.raiz(), A, fin);
      os << endl;
   }
}

template <typename T>
void imprimirDescendientes(ostream& os, typename Agen<T>::nodo n, const Agen<T>& A, const T& fin)
// Post: Inserta en el flujo de salida os y en preorden
//       los descendientes de n, usando fin como nodo nulo.
{
   typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
   while (hijo != Agen<T>::NODO_NULO) {
      os << A.elemento(hijo) << ' ';
      imprimirDescendientes(os, hijo, A, fin);
      hijo = A.hermDrcho(hijo);
   }
   os << fin << ' ';
}

#endif   // AGEN_E_S_H
