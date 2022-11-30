#include "data.h"
#include <stdbool.h>
#include "NTT.h"
bool operator>=(const Data &x, const Data &y)
{
    if (x.number.size() - x.point != y.number.size() - y.point)
        return x.number.size() - x.point > y.number.size() - y.point;
    for (int i = x.number.size() - 1, j = y.number.size() - 1; i >= 0 && j >= 0; i--, j--)
        if (x.number[i] != y.number[j])
            return x.number[i] > y.number[j];
    return x.point>y.point;
}

Data operator-(const Data &x, const Data &y)
{
    Data rlt;
    vector left, right;
    int leftPoint, rightPoint;
    left.init();
    right.init();
    rlt.number.init();
    if (x >= y)
        left = x.number, right = y.number, leftPoint = x.point, rightPoint = y.point, rlt.symbol = 1;
    else
        left = y.number, right = x.number, leftPoint = y.point, rightPoint = x.point, rlt.symbol = -1;
    rlt.number.push_back(0);
    for (int i = 0, j = 0, k = 0; i < left.size() || j < right.size(); k++)
    {
        int leftNow, rightNow;
        if (i < leftPoint - rightPoint || j >= right.size())
            rightNow = 0;
        else
            rightNow = right[j];
        if (j < rightPoint - leftPoint || i >= left.size())
            leftNow = 0;
        else
            leftNow = left[i];
        rlt.number.push_back(leftNow+rlt.number[k] >= rightNow ? 0 : -1);
        rlt.number[k] += leftNow+rlt.number[k] >= rightNow ? leftNow - rightNow : leftNow + 10 - rightNow;
        if (j >= rightPoint - leftPoint && i < left.size()) i++;
        if (i > leftPoint - rightPoint && j < right.size()) j++;
    }
    rlt.point = leftPoint > rightPoint ? leftPoint : rightPoint;
    while (!rlt.number[rlt.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        rlt.number.pop_back();
    return rlt;
}

Data operator+(const Data &x, const Data &y)
{
    if (x.symbol < 0 && y.symbol > 0)
    {
        Data Posx = x;
        Posx.symbol = 1;
        return y - x;
    }
    if (x.symbol > 0 && y.symbol < 0)
    {
        Data Posy = y;
        Posy.symbol = 1;
        return x - y;
    }
    Data rlt;
    rlt.number.init();
    rlt.symbol = x.symbol;
    vector left, right;
    left.init();
    right.init();
    int leftPoint, rightPoint;
    leftPoint = x.point;
    rightPoint = y.point;
    int move, i; // move小数点对齐移动位数
    //对齐
    if (leftPoint >= rightPoint)
    {
        move = leftPoint - rightPoint;
        for (i = 0; i < x.number.size(); i++)
        {
            left.push_back(x.number[i]);
        }
        for (i = 0; i < move; i++)
        {
            right.push_back(0);
        }
        for (i = 0; i < y.number.size(); i++)
        {
            right.push_back(y.number[i]);
        }
    }
    else
    {
        move = rightPoint - leftPoint;
        for (i = 0; i < y.number.size(); i++)
        {
            right.push_back(y.number[i]);
        }
        for (i = 0; i < move; i++)
        {
            left.push_back(0);
        }
        for (i = 0; i < x.number.size(); i++)
        {
            left.push_back(x.number[i]);
        }
    }
    //计算
    int numNow, extra = 0; // extra进位
    int len_max;
    len_max = left.size() > right.size() ? left.size() : right.size();
    for (i = 0; i < len_max; i++)
    {
        numNow = (i < left.size() ? left[i] : 0) + (i < right.size() ? right[i] : 0) + extra;
        extra = 0;
        if (numNow >= 10)
        {
            extra = numNow / 10;
            numNow %= 10;
        }
        rlt.number.push_back(numNow);
    }
    //最后一位可能进位
    if (extra)
        rlt.number.push_back(extra);
    rlt.point = leftPoint > rightPoint ? leftPoint : rightPoint;
    while (!rlt.number[rlt.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        rlt.number.pop_back();
    return rlt;
}

Data operator*(const Data &x, const Data &y)
{
    Data rlt;
    rlt.number.init();
    rlt.point = x.point + y.point; //小数点
    rlt.symbol = x.symbol * y.symbol;
    int i, j;
    for (i = 0; i < x.number.size() + y.number.size(); i++)
    {
        rlt.number.push_back(0);
    }
    Process_NTT(x, y, &rlt);
    for (i = 0; i < rlt.number.size(); i++)
    {
        if (rlt.number[i] >= 10)
        {
            rlt.number[i + 1] += rlt.number[i] / 10;
            rlt.number[i] %= 10;
        }
    }
    if(rlt.number[rlt.number.size()-1]>=10){
        rlt.number.push_back(rlt.number[rlt.number.size()-1]/10);
        rlt.number[rlt.number.size()-2]%=10;
    }
    while (!rlt.number[rlt.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        rlt.number.pop_back();
    return rlt;
}

Data operator/(const Data &x, const Data &y)
{
    Data rlt;
    rlt.number.init();
    rlt.point = x.point - y.point;
    rlt.symbol = x.symbol / y.symbol;
    for (int i = 0; i < x.number.size() - y.number.size(); i++)
        rlt.number.push_back(0);
    Data extra = InttoData(0), ten = InttoData(10);
    for (int i = x.number.size() - 1; i >= y.number.size() - 1; i--)
    {
        for (int k = 9; k > 0; k--)
        {
            Data K = InttoData(k), nowX, nowRlt;
            nowX.number.init();
            for (int j = 0; j < y.number.size(); j++)
                nowX.number.push_back(x.number[i + j - y.number.size()]);
            nowX.point = y.point;
            nowX.symbol = 1;
            nowRlt = nowX + extra * ten - K * y;
            if (nowRlt.symbol > 0)
            {
                rlt.number[i - y.number.size()] = k;
                extra = nowRlt;
                break;
            }
        }
    }
    while (rlt.point < rlt.number.size() - 1 && !rlt.number[rlt.number.size() - 1])
        rlt.number.pop_back();
    return rlt;
}