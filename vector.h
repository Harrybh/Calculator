#include<stdlib.h>
#include<string.h>
typedef struct 
{
    int *Array;
    int Len;
    int *ArrayNew;
    vector()
    {
        Array = NULL;
        ArrayNew = NULL;
        Len = 0;
    }
    vector(int Num)
    {
        int tmp = Num;
        while(tmp)tmp /= 10, Len++;
        Array = (int *)malloc(Len * sizeof(int));
        for(int i = 0;i < Len; i++)Array[i] = Num % 10, Num /= 10;
    }
    void clear()
    {
        if(Len == 0)return ;
        Len = 0;
        free(Array);
    }
    void push_back(int Num)
    {
        ArrayNew = (int *)malloc(sizeof(int)*(Len+1));
        if(Len)
        {
            memcpy(ArrayNew,Array,sizeof(int)*Len);
            free(Array);
        }
        Array = ArrayNew;
        Array[Len++] = Num;
    }
    void pop_back()
    {
        if(Len < 1)return;
        if(Len == 1)
        {
            Len--;
            free(Array);
            return;
        }
        ArrayNew = (int *)malloc(sizeof(int)*(Len-1));
        memcpy(ArrayNew,Array,sizeof(int)*(Len-1));
        free(Array);
        Array = ArrayNew;
        Len--;
    }
    int size()
    {
        return Len;
    }
    int &operator [] (int i) const 
    {
        return Array[i];
    }
}vector;
