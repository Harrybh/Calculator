#include "data.h"

#define PROCESS_TIMES 50

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//判断是否为零
bool IsZero(const Data &x)
{
    bool flag = true;
    for (int i = x.number.size()-1; i >= 0; i--){
        if (i < x.point - POINT_LIMIT)
            break;
        if (x.number[i])
            flag = false;
    }
    return flag;
}
//清楚小数点后多余的零
void ClearZero(Data &x)
{
    if (x.point < POINT_LIMIT)
        return;
    Data y;
    y.number.init();
    y.point = POINT_LIMIT;
    y.symbol = x.symbol;
    y.error=0;
    bool flag = 0;
    for (int i = x.point - POINT_LIMIT; i < x.number.Len; i++)
    {
        if (x.number[i])
            flag = 1;
        if (flag)
            y.number.push_back(x.number[i]);
        else
            y.point--;
    }
    x = y;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
// NTT
const int maxn = 1e6 + 10;
const int mod = 998244353, gs = 3;
int rev[maxn], lim, len;
int A_tmp[maxn], B_tmp[maxn];

void init(int Len)
{
    lim = 1, len = 0;
    while (lim <= Len)
        lim <<= 1, len++;
    for (int i = 1; i < lim; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
    for (int i = 0; i < lim; i++)
        A_tmp[i] = B_tmp[i] = 0;
}

inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int Pow(int a, long long k)
{
    int ret = 1;
    while (k)
    {
        if (k & 1)
            ret = ret * 1LL * a % mod;
        k >>= 1, a = a * 1LL * a % mod;
    }
    return ret;
}

void NTT(int *a, int type)
{
    for (int i = 0; i < lim; i++)
        if (rev[i] > i)
            swap(&a[rev[i]], &a[i]);
    for (int mid = 1; mid < lim; mid <<= 1)
    {
        int wn = Pow(gs, (mod - 1) / (mid << 1));
        if (type == -1)
            wn = Pow(wn, mod - 2);
        for (int i = 0; i < lim; i += mid << 1)
            for (int j = 0, w = 1; j < mid; j++, w = w * 1LL * wn % mod)
            {
                int x = a[i + j], y = a[i + j + mid] * 1LL * w % mod;
                a[i + j] = (x + y) % mod;
                a[i + j + mid] = (x + mod - y) % mod;
            }
    }
    if (type == -1)
    {
        int inv = Pow(lim, mod - 2);
        for (int i = 0; i < lim; i++)
            a[i] = a[i] * 1LL * inv % mod;
    }
}

inline int min(const int &a, const int &b) { return a > b ? b : a; }
inline int max(const int &a, const int &b) { return b > a ? b : a; }
inline void Process_NTT(const Data &a, const Data &b, Data *c)
{
    int lim1 = a.number.size(), lim2 = b.number.size();
    init(lim1 + lim2);
    for (int i = 0; i < min(lim1, lim); i++)
        A_tmp[i] = a.number[i];
    for (int i = 0; i < min(lim2, lim); i++)
        B_tmp[i] = b.number[i];
    NTT(A_tmp, 1), NTT(B_tmp, 1);
    for (int i = 0; i < lim; i++)
        A_tmp[i] = A_tmp[i] * 1LL * B_tmp[i] % mod;
    NTT(A_tmp, -1);
    while (c->number.size() < lim1 + lim2)
        c->number.push_back(0);
    for (int i = 0; i < lim1 + lim2 - 1; i++)
        c->number[i] = A_tmp[i];
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//加减乘除模
bool operator>=(const Data &x, const Data &y);
Data operator+(const Data &x, const Data &y);
Data operator-(const Data &x, const Data &y);
Data operator*(const Data &x, const Data &y);
Data operator/(const Data &a, const Data &b);

bool operator>=(const Data &x, const Data &y)
{
    if (x.number.size() - x.point != y.number.size() - y.point)
        return x.number.size() - x.point > y.number.size() - y.point;
    int i, j;
    for (i = x.number.size() - 1, j = y.number.size() - 1; i >= 0 && j >= 0; i--, j--)
        if (x.number[i] != y.number[j])
            return x.number[i] > y.number[j];
    while (i >= 0)
    {
        if (x.number[i])
            return true;
        i--;
    }
    while (j >= 0)
    {
        if (y.number[j])
            return false;
        j--;
    }
    return true;
}

Data operator+(const Data &x, const Data &y)
{
    if (x.symbol < 0 && y.symbol > 0)
    {
        Data Posx = x;
        Posx.symbol = 1;
        return y - Posx;
    }
    if (x.symbol > 0 && y.symbol < 0)
    {
        Data Posy = y;
        Posy.symbol = 1;
        return x - Posy;
    }
    Data rlt;
    rlt.error=0;
    rlt.number.init();
    rlt.symbol = x.symbol;
    vector left, right;
    left.init();
    right.init();
    int leftPoint, rightPoint;
    leftPoint = x.point;
    rightPoint = y.point;
    int move, i; // move小数点对齐移动位数
    if (leftPoint >= rightPoint)
    {
        move = leftPoint - rightPoint;
        for (i = 0; i < x.number.size(); i++)
            left.push_back(x.number[i]);
        for (i = 0; i < move; i++)
            right.push_back(0);
        for (i = 0; i < y.number.size(); i++)
            right.push_back(y.number[i]);
    }
    else
    {
        move = rightPoint - leftPoint;
        for (i = 0; i < y.number.size(); i++)
            right.push_back(y.number[i]);
        for (i = 0; i < move; i++)
            left.push_back(0);
        for (i = 0; i < x.number.size(); i++)
            left.push_back(x.number[i]);
    }
    // 计算
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
    // 最后一位可能进位
    if (extra)
        rlt.number.push_back(extra);
    rlt.point = leftPoint > rightPoint ? leftPoint : rightPoint;
    while (!rlt.number[rlt.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        rlt.number.pop_back();
    IsZero(rlt);
    return rlt;
}

Data operator-(const Data &x, const Data &y)
{
    if (x.symbol < 0 && y.symbol > 0)
    {
        Data Posy = y;
        Posy.symbol = -1;
        return x + Posy;
    }
    if (x.symbol > 0 && y.symbol < 0)
    {
        Data Posy = y;
        Posy.symbol = 1;
        return x + Posy;
    }
    Data rlt;
    rlt.error=0;
    vector left, right;
    int leftPoint, rightPoint;
    left.init();
    right.init();
    rlt.number.init();
    if (x >= y)
        left = x.number, right = y.number, leftPoint = x.point, rightPoint = y.point, rlt.symbol = x.symbol;
    else
        left = y.number, right = x.number, leftPoint = y.point, rightPoint = x.point, rlt.symbol = -x.symbol;
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
        rlt.number.push_back(leftNow + rlt.number[k] >= rightNow ? 0 : -1);
        rlt.number[k] += leftNow + rlt.number[k] >= rightNow ? leftNow - rightNow : leftNow + 10 - rightNow;
        if (j >= rightPoint - leftPoint && i < left.size())
            i++;
        if (i > leftPoint - rightPoint && j < right.size())
            j++;
    }
    rlt.point = leftPoint > rightPoint ? leftPoint : rightPoint;
    while (!rlt.number[rlt.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        rlt.number.pop_back();
    IsZero(rlt);
    return rlt;
}

Data operator*(const Data &x, const Data &y)
{
    Data rlt;
    rlt.error=0;
    rlt.number.init();
    rlt.point = x.point + y.point; // 小数点
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
    if (rlt.number[rlt.number.size() - 1] >= 10)
    {
        rlt.number.push_back(rlt.number[rlt.number.size() - 1] / 10);
        rlt.number[rlt.number.size() - 2] %= 10;
    }
    while (!rlt.number[rlt.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        rlt.number.pop_back();
    IsZero(rlt);
    return rlt;
}

int FindDiv(const Data &x, const Data &y)
{
    int l = 0, r = 9, ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (x >= y * InttoData(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    return ans;
}
Data operator/(const Data &a, const Data &b)
{
    Data x, y;
    x = a, y = b;
    if(IsZero(y))
        return Error(3);
    Data ans;
    ans.error=0;
    Data rlt = InttoData(0);
    x.symbol = y.symbol = 1;
    while (!x.number[x.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        x.number.pop_back();
    while (!y.number[y.number.size() - 1] && rlt.point + 1 < rlt.number.size())
        y.number.pop_back();
    ans.point = x.point - y.point + y.number.size() - x.number.size() - 1;
    Data newX;
    newX = x;
    x.point = 0;
    y.point = 0;
    for (int i = x.number.size() - 1;; i--)
    {
        Data now;
        now.number.init();
        now.point = 0;
        now.symbol = 1;
        for (int j = 0; j < y.number.size(); j++)
        {
            int p = i + j + 1 - y.number.size();
            if (p >= 0)
            {
                now.number.push_back(newX.number[i + j + 1 - y.number.size()]);
                newX.number[i + j + 1 - y.number.size()] = 0;
            }
            else
                now.number.push_back(0);
        }

        now = now + rlt * InttoData(10);
        int p = FindDiv(now, y);
        rlt = now - InttoData(p) * y;
        ans.number.push_back(p);
        ans.point++;
        if (rlt.number.size() == 1 && rlt.number[0] == 0 && i + 1 - y.number.size() < 0)
            break;
        if (ans.point > POINT_LIMIT - 1)
            break;
    }
    while (ans.point < 0)
        ans.point++, ans.number.push_back(0);
    for (int i = 0; i <= (ans.number.size() - 1) / 2; i++)
        swap(&ans.number[i], &ans.number[ans.number.size() - 1 - i]);
    while (ans.number.size() <= ans.point)
        ans.number.push_back(0);
    ans.symbol = a.symbol * b.symbol;
    while (!ans.number[ans.number.size() - 1] && ans.point + 1 < ans.number.size())
        ans.number.pop_back();
    rlt.number.clear();
    x.number.clear();
    y.number.clear();
    newX.number.clear();
    IsZero(ans);
    ClearZero(ans);
    return ans;
}

Data operator%(const Data &x, const Data &yy)
{
    Data y = yy;
    if(IsZero(y)||x.point||y.point)
        return Error(3);
    y.symbol = 1;
    if (x.number.size() < y.number.size())
        return InttoData(0);
    Data rlt = InttoData(0), newX = x;
    rlt.error=0;
    for (int i = x.number.size() - 1; i >= y.number.size() - 1; i--)
    {
        Data now;
        now.number.init();
        now.point = 0;
        now.symbol = 1;
        for (int j = 0; j < y.number.size(); j++)
        {
            now.number.push_back(newX.number[i + j + 1 - y.number.size()]);
            newX.number[i + j + 1 - y.number.size()] = 0;
        }
        now = now + rlt * InttoData(10);
        int p = FindDiv(now, y);
        rlt = now - InttoData(p) * y;
    }
    rlt.symbol = x.symbol * yy.symbol;
    IsZero(rlt);
    return rlt;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//函数（泰勒展开）
Data Sin(Data x)
{
    Data nowNumber = x * x / InttoData(6) * x;
    Data finalAns = x - nowNumber;
    for (int i = 2; i <= PROCESS_TIMES; i++)
    {
        nowNumber = nowNumber * x / InttoData(i << 1) * x / InttoData(i << 1 | 1);
        if (i & 1)
            finalAns = finalAns - nowNumber;
        else
            finalAns = finalAns + nowNumber;
    }
    finalAns.error=0;
    return finalAns;
}

Data Cos(Data x)
{
    Data nowNumber = x * x / InttoData(2);
    Data finalAns = InttoData(1) - nowNumber;
    for (int i = 2; i <= PROCESS_TIMES; i++)
    {
        nowNumber = nowNumber * x * x / InttoData(i << 1) / InttoData(i * 2 - 1);
        if (i & 1)
            finalAns = finalAns - nowNumber;
        else
            finalAns = finalAns + nowNumber;
    }
    finalAns.error=0;
    return finalAns;
}

Data Tan(Data x)
{
    Data cosans=Cos(x);
    if(IsZero(cosans))
        return Error(3);
    return Sin(x) / Cos(x);
}

Data Fac(Data x)
{
    if(x.symbol<0||x.point!=0){
        return Error(3);
    }
    Data rlt=x;
    Data one=InttoData(1);
    for(Data i=x-one;i>=one;i=i-one){
        rlt=rlt*i;
        if(rlt.number.size()>100)
            return Error(4);
    }
    rlt.error=0;
    return rlt;
}

Data Abs(Data x)
{
    x.symbol=x.symbol>=0?x.symbol:-x.symbol;
    x.error=0;
    return x;
}

Data Ln(Data base)
{
     if (base.symbol > 0)
    {

        Data base2 = (base - InttoData(1)) / (base + InttoData(1));
        Data result = base2, now = base2;
        qDebug()<<"YES";
        for (int i = 3; i <= 100; i += 2)
        {

            // printf("now:\n");
            // Write(now);
            now = now * base2 * base2 * InttoData(i - 2) / InttoData(i)  ;
            qDebug()<<"YES";
            result = result + now;
            qDebug()<<"YES";
            // printf("result:\n");
            // Write(result);
        }
        qDebug()<<"YES";
        return result * InttoData(2);
    }
    else{
        return Error(3);
    }
}

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
                return Error(3);
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
            return Error(3);
        else
            return InttoData(0);
    }
    result = index * Ln(base);
    for (int i = 1; i <= 50; i++)
    {
        now = now * result / InttoData(i);
        final = final + now;
    }
    return final;
}

Data Sqrt(Data x)
{
    if(IsZero(x))
        return Error(3);
    Data half;
    half=InttoData(5);
    half.number.push_back(0);
    half.point=1;
    return Exp(x,half);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
