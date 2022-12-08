#include <stdio.h>
#include "operation.h"
/* base是底数，index是指数，本函数组合用来将a^b转化为e^b*lna */

/*利用泰勒展开求lnx的函数*/
Data ln(Data base)
{
     if (base.symbol > 0)
    {
        Data base2 = (base - InttoData(1)) / (base + InttoData(1));
        Data result = base2, now = base2;
        for (int i = 3; i <= 100; i += 2)
        {
            // printf("now:\n");
            // Write(now);
            now = now * base2 * base2 * InttoData(i - 2) / InttoData(i)  ;
            result = result + now;
            // printf("result:\n");
            // Write(result);
        }
        return result * InttoData(2);
    }
    else{
        return Error(1);
    }
}
/*
Data ln(Data base)
{
     if (base.symbol > 0)
    {
        Data base1 = base - InttoData(1);
        Data base2 = base + InttoData(1);
        Data result = base1 / base2, now = base1, cur = base2;
        for (int i = 3; i <= 100; i += 2)
        {
            // printf("now:\n");
            // Write(now);
            now = now * base1 * base1  / InttoData(i) * InttoData(i - 2) ;
            cur = cur * base2 * base2;
            if(i % 10 == 0)
            {
                now = now / cur;
                cur = InttoData(1);
            }
            result = result + now / cur;
            // printf("result:\n");
            // Write(result);
        }
        return result * InttoData(2);
    }
    else{
        return Error(1);
    }
}
*/

//求转化后e的指数的函数
Data Exp(Data base, Data index)
{
    /*麦克劳林展开：ln(x+1)=x-x^2/2!+x^3/3!-...*/
    int flag = 1;                                                         //用来决定展开式每一项的正负号
    Data result = InttoData(1), now = InttoData(1), final = InttoData(1); // temp存储每一项的值，result是总和
    if (base.symbol < 0)
    {
        base.symbol = 1;
        if (index.point)
        {
            Data fenzi;
            int point = index.point;
            fenzi = index;
            fenzi.point = 0;
            while (point > 0 && fenzi.number[0] & 1 == 0)
            {
                point--;
                fenzi = fenzi / InttoData(2);
            }
            if (!point && fenzi.number[0] & 1)
                final.symbol = -1;
            else if (point > 0)
                printf("error");
        }
        else
        {
            if (index.number[0] % 2)
                final.symbol = -1;
        }
    }
    else if (IsZero(base))
    {
        if (IsZero(index) || index.symbol < 0)
            printf("error");
        else
            return InttoData(0);
    }
    result = index * ln(base);
    for (int i = 1; i <= 50; i++)
    {
        now = now * result / InttoData(i);
        final = final + now;
    }
    return final;
}

int main()
{
    Data x, y;
    Write(sin(Pi));
    Write(ln(E));
    Write(Exp(InttoData(2),InttoData(10)));
    return 0;
}