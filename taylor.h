#include<data.h>
#define PROCESS_TIMES 51
Data cos(Data x)
{
    Data nowNumber = x * x / vector(2);
    Data finalAns = 1 - nowNumber; 
    for(int i = 2; i <= PROCESS_TIMES; i++)
    {
        nowNumber = nowNumber * x / vector(i*2-1) * x / vector(i<<1);
        if(i&1)finalAns =  finalAns - nowNumber;
        else finalAns = finalAns + nowNumber;
    }
    return finalAns;
}
Data cos(Data x)
{
    Data nowNumber = x * x / vector(6) * x;
    Data finalAns = x - nowNumber; 
    for(int i = 2; i <= PROCESS_TIMES; i++)
    {
        nowNumber = nowNumber * x / vector(i<<1) * x / vector(i<<1|1);
        if(i&1)finalAns =  finalAns - nowNumber;
        else finalAns = finalAns + nowNumber;
    }
    return finalAns;
}
Data tan(Data x)
{
    return sin(x) / cos(x);
}