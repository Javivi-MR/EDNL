#ifndef ABIN_VEC_HPP
#define ABIN_VEC_HPP
#include <cassert>
#include <cstdint>

template<typename T> 
class AbinVec
{
public:
    typedef std::size_t nodo;
    static const nodo NODO_NULO;
    explicit AbinVec(std::size_t maxNodos);
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T& elemento (nodo n) const; //solo lectura
    T& elemento(nodo n);
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    AbinVec(const AbinVec<T>& A);
    AbinVec<T>& operator=(const AbinVec<T>& A);
    int altura(nodo n);
    int profundidad(nodo n);
    ~AbinVec();
private:
    struct celda{
        T elto;
        nodo padre, hizq, hder;
    };
    celda *nodos; //vector de nodos
    std::size_t maxNodos; //tam. del vector
    std::size_t numNodos; //numero de nodos del arbol

};


//definicion de nodo nulo
template <typename T>
const typename AbinVec<T>::nodo AbinVec<T>::NODO_NULO(SIZE_MAX);

template <typename T>
inline AbinVec<T>::AbinVec(std::size_t maxNodos) :
    nodos(new celda[maxNodos]),
    maxNodos(maxNodos),
    numNodos(0)
{}


template <typename T>
int AbinVec<T>::altura(nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return -1;
    else 
        return 1 + std::max(alturaRec(nodos[n].hizq), alturaRec(nodos[n].hder));

}


template <typename T>
int AbinVec<T>::profundidad(nodo n)
{
    int profundidad = 0;
    nodo aux = n;

    while (aux != 0)
    {
        profundidad++;
        aux = nodos[aux].padre;
    }

    return profundidad;
}

template <typename T>
inline void AbinVec<T>::insertarRaiz(const T& e)
{
    assert(numNodos == 0);

    numNodos = 1;
    nodos[0].elto = e;
    nodos[0].padre = NODO_NULO;
    nodos[0].hizq = NODO_NULO;
    nodos[0].hder = NODO_NULO;
}

template <typename T>
inline void AbinVec<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n >= 0 && n < numNodos); //nodo valido
    assert(nodos[n].hizq == NODO_NULO); //n no tiene hijo izq
    assert(numNodos < maxNodos); // arbol no lleno

    //add new nodo
    nodos[n].hizq = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}


template <typename T>
inline void AbinVec<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n >= 0 && n < numNodos); //nodo valido
    assert(nodos[n].hder == NODO_NULO);//n no tiene hijo drch
    assert(numNodos < maxNodos); //arbol no lleno
    
    //add new nodo
    nodos[n].hder = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
 }

template <typename T>
void AbinVec<T>::eliminarHijoIzqdo(nodo n)
{
    nodo hizqdo;
    assert(n >= 0 && n < numNodos);//nodo valido
    hizqdo = nodos[n].hizq;
    assert(hizqdo != NODO_NULO);
    assert(nodos[hizqdo].hizq == NODO_NULO && nodos[hizqdo].hder == NODO_NULO);
    //hijo izq de n es hoja

    if(hizqdo != numNodos-1)
    {// Mover el último nodo a la posición del hijo izqdo.
        nodos[hizqdo] = nodos[numNodos-1];// Actualizar la posición del hijo (izquierdo o derecho) en el padre del nodo movido.
        if(nodos[nodos[hizqdo].padre].hizq == numNodos-1)
            nodos[nodos[hizqdo].padre].hizq = hizqdo;
        else
            nodos[nodos[hizqdo].padre].hder= hizqdo;
        // Si el nodo movido tiene hijos, actualizar la posición del padre.
        if(nodos[hizqdo].hizq != NODO_NULO)
            nodos[nodos[hizqdo].hizq].padre = hizqdo;
        if(nodos[hizqdo].hder!= NODO_NULO)
            nodos[nodos[hizqdo].hder].padre = hizqdo;
    }
    
    nodos[n].hizq = NODO_NULO;
    --numNodos;
}
 
template <typename T>
void AbinVec<T>::eliminarHijoDrcho(nodo n)
{
    nodo hdrcho;
    assert(n >= 0 && n < numNodos); //nodo valido
    hdrcho = nodos[n].hder;
    assert(hdrcho != NODO_NULO); //existe hijo derecho
    assert(nodos[hdrcho].hizq == NODO_NULO && nodos[hdrcho].hder == NODO_NULO); //hijo derecho de n es hoja

    if(hdrcho != numNodos-1)
    {
        //mover el ultimo nodo a la posicion del hijo derecho
        nodos[hdrcho] = nodos[numNodos - 1];
        //actualizar la posicion del hijo (izquierdo o derecho) en el padre del nodo movido
        if(nodos[nodos[hdrcho].padre].hizq == numNodos - 1)
            nodos[nodos[hdrcho].padre].hizq == hdrcho;
        else 
            nodos[nodos[hdrcho].padre].hder = hdrcho;
        
        //si el nodo movido tiene hijos, actualizar la posicion del padre
        if(nodos[hdrcho].hizq != NODO_NULO)
            nodos[nodos[hdrcho].hizq].padre = hdrcho;
        if(nodos[hdrcho].hder != NODO_NULO)
            nodos[nodos[hdrcho].hder].padre = hdrcho;
    }
    nodos[n].hder = NODO_NULO;
    --numNodos;
}


template <typename T>
inline void AbinVec<T>::eliminarRaiz()
{
    assert(numNodos == 1);
    numNodos = 0;
}


template <typename T>
inline bool AbinVec<T>::arbolVacio() const 
{
    return (numNodos == 0);
}

template <typename T>
inline const T& AbinVec<T>::elemento(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}


template <typename T>
inline T& AbinVec<T>::elemento(nodo n)
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}


template <typename T>
inline typename AbinVec<T>::nodo AbinVec<T>::raiz() const 
{
    return (numNodos > 0) ? 0 : NODO_NULO;
}


template <typename T>
inline typename AbinVec<T>::nodo AbinVec<T>::padre(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].padre;
}


template <typename T>
inline typename AbinVec<T>::nodo AbinVec<T>::hijoIzqdo(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hizq;
}


template <typename T>
inline typename AbinVec<T>::nodo AbinVec<T>::hijoDrcho(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hder;
}


template <typename T>
AbinVec<T>::AbinVec(const AbinVec<T>& A) :
    nodos(new celda[A.maxNodos]),
    maxNodos(A.maxNodos), 
    numNodos(A.numNodos)
{
    for(nodo n = 0; n <= numNodos-1; n++)
        nodos[n] = a.nodos[n];
}


template <typename T>
inline AbinVec<T>::~AbinVec()
{
    delete[] nodos;
}


template <typename T>
AbinVec<T>& AbinVec<T>::operator =(const AbinVec<T>& A)
{
    if(this != &A)
    {
        if(maxNodos != A.maxNodos)
        {
            delete [] nodos;
            maxNodos = A.maxNodos;
            nodos = new celda[maxNodos];
        }
    
        //copiar el vector
        for (nodo n = 0; n <= numNodos-1; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}


#endif //ABINVEC_HPP