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

//定义栈里的元素
typedef struct StackMember
{
    struct StackMember *next;
    Data data;
    
}StackMember;

//定义栈
typedef struct Stack
{
    struct StackMember *top;
    int size;
}Stack;

vector getE()
{
    vector vE;
    long long a,b,c,d,e;
    a=27182818284,b=5904523536,c=287471352,d=6624977572,e=4709369995;
    for(int i=0;i<10;i++)
        vE.push_back((int)(e%10)),e/=10;
    for(int i=0;i<10;i++)
        vE.push_back((int)(d%10)),d/=10;
    for(int i=0;i<10;i++)
        vE.push_back((int)(c%10)),c/=10;
    for(int i=0;i<10;i++)
        vE.push_back((int)(b%10)),b/=10;
    for(int i=0;i<=10;i++)
        vE.push_back((int)(a%10)),a/=10;
    return vE;
}

vector getPi()
{
    vector vPi;
    long long a,b,c,d,e;
    a=31415926535,b=8979323846,c=2643383279,d=5028841971,e=6939937510;
    for(int i=0;i<10;i++)
        vPi.push_back((int)(e%10)),e/=10;
    for(int i=0;i<10;i++)
        vPi.push_back((int)(d%10)),d/=10;
    for(int i=0;i<10;i++)
        vPi.push_back((int)(c%10)),c/=10;
    for(int i=0;i<10;i++)
        vPi.push_back((int)(b%10)),b/=10;
    for(int i=0;i<=10;i++)
        vPi.push_back((int)(a%10)),a/=10;
    return vPi;
}

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

//初始化栈
Stack *Init()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));//申请栈的内存空间,并将空间的地址传给栈数据类型的指针.
    s->top=NULL;
    s->size=0;
    return s;//返回初始话栈的地址
}

//初始化栈的成员
StackMember *InitStackMember(Data x)
{
    StackMember *tempStackMember=(StackMember *)malloc(sizeof(StackMember));
    tempStackMember->data=x;
    tempStackMember->next=NULL;
    return tempStackMember;
}

//判断栈是否为空
bool Empty(Stack *s)
{
    return s->top==NULL;//如果栈为空，栈顶为-1
}

//返回栈顶元素
StackMember *Top(Stack *s)
{
    if (Empty(s))//判断栈是否为空
        return NULL;
    return s->top;//返回栈顶元素
}

//入栈操作
bool Push(Stack *s,StackMember *val)
{
    if (s==NULL)//判断栈是否存在
        return false;
    val->next=s->top;
    s->top=val;
    (s->size)++;
    return true;
}

//出栈操作
bool Pop(Stack *s)
{
    if (s == NULL)//判断栈是否存在
        return false;
    if (Empty(s))//判断栈内是否为空
        return false;
    StackMember *topMember=s->top;
    s->top=s->top->next;
    free(topMember); //释放出栈成员的空间
    (s->size)--;
    return true;
}