#ifndef FilaContador_h
#define FilaContador_h

#include "../Constantes.h"

class FilaContador
{
private:
    int *thisArray;
    int FIRSTINDEX = 0;
    int LASTINDEX;
    int OLDESTINDEX = 0;
    void UpdateOldest();

public:
    int maxSize;
    int currentSize;

    FilaContador(int maximumSize = Constantes::MINUTO)
    {
        maxSize = maximumSize;
        LASTINDEX = maximumSize - 1;
        thisArray = new int[maxSize];

        for (int i = 0; i < maxSize; i++)
        {
            thisArray[i] = 0;
        }
        return;
    }

    int InsertLast(int value)
    {
        int currValue = value;
        if (currentSize < maxSize)
        {
            thisArray[currentSize] = currValue;
            currentSize++;
        }
        else
        {
            currentSize = maxSize;
            currValue = ChangeOldest(value);
        }

        return currValue;
    }

    int ChangeOldest(int value)
    {
        int currValue = thisArray[OLDESTINDEX];
        thisArray[OLDESTINDEX] = value;
        UpdateOldest();
        return currValue;
    }

    void Delete()
    {
        delete thisArray;
        delete this;
    }
};

#endif