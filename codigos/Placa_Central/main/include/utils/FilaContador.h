#ifndef FilaContador_h
#define FilaContador_h

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
    FilaContador(int maximumSize);
    int InsertLast(int value);
    int ChangeOldest(int value);
    void Delete();
};

#endif