#include"vector.h"
typedef struct Data
{
    vector number;//值
    int point;
    int symbol;//符号
}Data;

Data InttoData(int x)
{
    Data rlt;
    rlt.number.init();
    rlt.symbol=x<0?-1:1;
    while(x){
        rlt.number.push_back(x%10);
        x/=10;
    }
    rlt.point=0;
    return rlt;
}

//常量(自然常量)
const Data E={getE(),50,1};
//常量(圆周率)
const Data Pi={getPi(),50,1};