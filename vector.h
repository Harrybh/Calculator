#include<stdlib.h>
#include<string.h>
typedef struct 
{
    int *Array;
    int Len;
    int *ArrayNew;
    void init()
    {
        Array = NULL;
        ArrayNew = NULL;
        Len = 0;
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
    int size() const
    {
        return Len;
    }
    int &operator [] (int i) const 
    {
        return Array[i];
    }
}vector;

vector getE()
{
    vector vE;
    long long a,b,c,d,e;
    a=27182818284,b=5904523536,c=287471352,d=6624977572,e=4709369995;
    for(int i=0;i<=50;i++)
        vE.push_back(0);
    for(int i=0;i<=10;i++)
        vE[10-i]=(int)(a%10),a/=10;
    for(int i=0;i<10;i++)
        vE[20-i]=(int)(b%10),b/=10;
    for(int i=0;i<10;i++)
        vE[30-i]=(int)(c%10),c/=10;
    for(int i=0;i<10;i++)
        vE[40-i]=(int)(d%10),d/=10;
    for(int i=0;i<10;i++)
        vE[50-i]=(int)(e%10),e/=10;
    return vE;
}

vector getPi()
{
    vector vPi;
    long long a,b,c,d,e;
    a=31415926535,b=8979323846,c=2643383279,d=5028841971,e=6939937510;
    for(int i=0;i<=50;i++)
        vPi.push_back(0);
    for(int i=0;i<=10;i++)
        vPi[10-i]=(int)(a%10),a/=10;
    for(int i=0;i<10;i++)
        vPi[20-i]=(int)(b%10),b/=10;
    for(int i=0;i<10;i++)
        vPi[30-i]=(int)(c%10),c/=10;
    for(int i=0;i<10;i++)
        vPi[40-i]=(int)(d%10),d/=10;
    for(int i=0;i<10;i++)
        vPi[50-i]=(int)(e%10),e/=10;
    return vPi;
}
    