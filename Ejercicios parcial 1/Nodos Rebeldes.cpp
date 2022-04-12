int profundidad(const Abin<bool>& A, typename Abin<bool>::nodo n)
{
    if(A.padre(n) != Abin<bool>::NODO_NULO)
        return 1 + profundidad(A,A.padre(n)) + 1;   
    else 
        return 0;
}

int numideasim(const Abin <bool>& A, typename Abin<bool>::nodo n, bool b)
{
    if(n == Abin<bool>::NODO_NULO)
        return 0;
    else
        if (A.elto(n) == b)
            return 1 + numideasim(A,A.padre(n),b); 
        else
            return numideasim(A,A.padre(n),b);
}


bool compruebaREC(const Abin <bool>& A , typename Abin<bool>::nodo n)
{
    if(numideasim(A,A.padre(n),A.elto(n)) < (profundidad(A,n)/2))
        return true;
    else
        return false;
}

int rebeldes(const Abin <bool>& A)
{
    return rebeldesREC(A,a.raiz())
}

int rebeldesREC(const Abin <bool>& A , typename Abin<bool>::nodo n)
{
    if(n == Abin<bool>::NODO_NULO)
        return 0;
    else
        if (compruebaREC(A,n))
            return 1 + rebeldesREC(A,A.hijoizqdo(n)) + rebeldesREC(A,A.hijodrcho(n))
        else
            return rebeldesREC(A,A.hijoizqdo(n)) + rebeldesREC(A,A.hijodrcho(n))
}
