#ifndef FilaContador_h
#define FilaContador_h

#include "../Constantes.h"

class FilaContador
{
    private:
    int* thisArray;
    int FIRSTINDEX = 0;
    int LASTINDEX;
    int OLDESTINDEX = 0;
    void UpdateOldest();
    
    public:
    int maxSize;
    int currentSize;
    FilaContador();
    FilaContador(int maximumSize  = Constantes::MINUTO);
    int InsertLast(int value);
    int ChangeOldest(int value);
    void Delete();
};

#endif