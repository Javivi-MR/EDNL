int contarnodos(Abin<T>& A, Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else 
        return 1 + contarnodos(A,A.hijoizqdo(n)) + contarnodos(A,A.hijodrcho(n)); 
}

int 4descendientes(Abin<T>& A)
{
    4descendientesREC(A,A.raiz())
}

int 4descendientesREC(Abin<T>& A,Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;   
    else
        if(contarnodos(A,n) - 1 == 4)
            return 1 + 4descendientesREC(A,A.hijoizqdo(n)) + 4descendientesREC(A,A.hijodrcho(n));
        else
            return 4descendientesREC(A,A.hijoizqdo(n)) + 4descendientesREC(A,A.hijodrcho(n));
}
