#include<vector.h>
#define PROCESS_TIMES 51
vector cos(vector x)
{
    vector nowNumber = x * x / vector(2);
    vector finalAns = 1 - nowNumber; 
    for(int i = 2; i <= PROCESS_TIMES; i++)
    {
        nowNumber = nowNumber * x / vector(i*2-1) * x / vector(i<<1);
        if(i&1)finalAns =  finalAns - nowNumber;
        else finalAns = finalAns + nowNumber;
    }
    return finalAns;
}
vector cos(vector x)
{
    vector nowNumber = x * x / vector(6) * x;
    vector finalAns = x - nowNumber; 
    for(int i = 2; i <= PROCESS_TIMES; i++)
    {
        nowNumber = nowNumber * x / vector(i<<1) * x / vector(i<<1|1);
        if(i&1)finalAns =  finalAns - nowNumber;
        else finalAns = finalAns + nowNumber;
    }
    return finalAns;
}
vector tan(vector x)
{
    return sin(x) / cos(x);
}