#include"vector.h"
typedef struct Data
{
    vector number;//值
    int point;
    int symbol;//符号
}Data;

//常量(自然常量)
const Data E={getE(),50,1};
//常量(圆周率)
const Data Pi={getPi(),50,1};