#include "FilaContador.h"

FilaContador::FilaContador(int maximumSize)
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

int FilaContador::InsertLast(int value)
{
    int currValue = value;
    if (currentSize < maxSize)
    {
        thisArray[currentSize] = currValue;
        currentSize++;
    } else {
        currentSize = maxSize;
        currValue = ChangeOldest(value);
    }

    return currValue;
}

int FilaContador::ChangeOldest(int value)
{
    int currValue = thisArray[OLDESTINDEX];
    thisArray[OLDESTINDEX] = value;
    UpdateOldest();
    return currValue;
}

void FilaContador::UpdateOldest() 
{
    OLDESTINDEX < LASTINDEX? OLDESTINDEX++ : OLDESTINDEX = 0;
}

void FilaContador::Delete()
{
    delete thisArray;
    delete this;
}