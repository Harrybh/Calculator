#include <stdio.h>
#include "operation.h"
/* base是底数，index是指数，本函数组合用来将a^b转化为e^b*lna */

/*利用麦克劳林公式求lnx的函数*/
Data ln(Data base)
{
    Data base2 = base - InttoData(1);
    if (base2.symbol > 0)
    {
        int flag = -1;
        Data result = InttoData(0), pownumber = InttoData(1), facnumber = InttoData(1),x;
        for (int i = 1; i <= 100; i++)
        {
            flag = -flag;
            pownumber=base2 * pownumber;
            facnumber = facnumber * InttoData(i);
            result = flag > 0 ? result + (pownumber / facnumber) : result - (pownumber / facnumber);
        }
        return result;
    }
    else
        return Error(1);
}

/*
//求转化后e的指数的函数
Data Exp(Data base, Data index)
{
    /*麦克劳林展开：ln(x+1)=x-x^2/2!+x^3/3!-...
    int flag=1;//用来决定展开式每一项的正负号
    Data result=0,temp=1;//temp存储每一项的值，result是总和
    Data result;
    if (base.symbol<0){
        base.symbol=1;
        if (index.point){
            if(index.number[0]%2)
                return Error(1);
            else
                result.symbol=-1;
        }
        else{
            if(index.number[0]%2)
                result.symbol=-1;
            else
                result.symbol=1;
        }
    }
    else
        result.symbol=1;

    if (base < 0)
    {
        if (index.point == 0)
        {
            if (index % 2 == 0)
            {
                base = -base;
                Data result = index * ln(base);
                Data final = InttoData(1);
                Data tmp = InttoData(1);
                for (int i = 1; i <= 50; i++)
                {
                    for (int j = 1; j <= i; j++)
                        tmp *= result / j;
                    final += tmp;
                }
                return final;
            }
            else
            {
                base = -base;
                Data result = index * ln(base);
                Data final = 1;
                Data tmp = 1;
                for (int i = 1; i <= 50; i++)
                {
                    for (int j = 1; j <= i; j++)
                        tmp *= result / j;
                    final += tmp;
                }
                return -final; //返回它的负值
            }
        }
        else if (index.point > 0)
        {
            Data index2 = index //存储原先的index值,在index%2!=0时使用
                Data digit = index.point;
            for (int i = 1; i <= digit; i++)
            {
                index *= 10;
            }
            if (index % 2 != 0)
                printf("Error!"); //需修改,返回值是？
            else
            {
                Data deno = 1; //将指数化为整数后，它需要除以的10的倍数
                /*约分
                for (int i = 1; i <= digit; i++)
                {
                    deno *= 10;
                }
                Data max;
                Data min;
                if (index > deno)
                {
                    max = index;
                    min = deno;
                }
                else
                {
                    max = deno;
                    min = index;
                }
                Data mod = max % min;
                while (mod)
                {
                    max = min;
                    min = mod;
                    mod = max % min;
                }
                index = index / min;
                deno = deno / min;
                /*1，负数的无理数次幂无意义。
                  2，负数的p/q(p奇q偶)次幂无意义。
                  3，负数的p/q(p，q同为奇)次幂是负数。
                  4，负数的p/q(p偶q奇)次幂是正数。
                if (index % 2 != 0 && deno % 2 == 0)
                {
                    printf("Error!"); //返回值？
                }
                else if (index % 2 != 0 && deno % 2 != 0)
                {
                    base = -base;
                    Data result = index * ln(base);
                    Data final = 1;
                    Data tmp = 1;
                    for (int i = 1; i <= 50; i++)
                    {
                        for (int j = 1; j <= i; j++)
                            tmp *= result / j;
                        final += tmp;
                    }
                    return (-final);
                }
                else if (index % 2 == 0 && deno % 2 != 0)
                {
                    base = -base;
                    Data result = index * ln(base);
                    Data final = 1;
                    Data tmp = 1;
                    for (int i = 1; i <= 50; i++)
                    {
                        for (int j = 1; j <= i; j++)
                            tmp *= result / j;
                        final += tmp;
                    }
                    return final;
                }
            }
        }
    }

    //底数为0时,注意0没有负数次方
    else if (base == 0)
    {
        if (index == 0)
            return 1;
        else if (index > 0)
        {
            return 0;
        }
        else if (index < 0)
            printf("Error");
    }

    else
    {
        Data result = index * ln(base);
        Data final = 1;
        Data tmp = 1;
        for (int i = 1; i <= 50; i++)
        {
            for (int j = 1; j <= i; j++)
                tmp *= result / j;
            final += tmp;
        }
        return final;
    }
}
*/

int main()
{
    Data x, y;
    x = InttoData(2.06);
    y = InttoData(-3);
    //x.point=2;
    //y.point=2;
    printf("%d\n",x>=y);
    Write(x);
    Write(y);
    Write(x-y);
    Write(ln(E));
    return 0;
}