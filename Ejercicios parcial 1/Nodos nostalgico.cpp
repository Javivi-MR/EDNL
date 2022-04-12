int nostalgico (Abin<T>& A)
{
    return nostalgicoREC(A,A.raiz());
}

int nostalgicoREC (Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        if(profundidad(A,n) > contarnodos(A,n)-1)
            return 1 + nostalgicoREC(A,A.hijoizqdo(n)) + nostalgicoREC(A,A.hijodrcho(n));
        else 
            return nostalgicoREC(A,A.hijoizqdo(n)) + nostalgicoREC(A,A.hijodrcho(n));
   
}

int profundidad (Abin<T>& A,Abin<T>::nodo n)
{
    if(A.padre(n) == Abin<T>::NODO_NULO)
        return 0;
    else
        return 1 + profundidad(A,A.padre(n));
}

int contarnodos (Abin<T>& A,Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else 
        return 1 + contarnodos(A,A.hijoizqdo(n)) + contarnodos(A,A.hijodrcho(n)); 
}
