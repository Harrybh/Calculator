#include<stdlib.h>
#include<string.h>
#include<stdio.h>
struct vector 
{
    int *Array;
    int Len;
    int BatchSize;
    int *ArrayNew;
    void init()
    {
        Array = NULL;
        ArrayNew = NULL;
        Len = 0;
        BatchSize = 0;
    }
    vector()
    {
        Array = NULL;
        ArrayNew = NULL;
        Len = 0;
        BatchSize = 0;
    }
    void clear()
    {
        if(Len == 0)return ;
        Len = 0;
        free(Array);
    }
    void push_back(int Num)
    {
        if(Len+1<=BatchSize)
        {
            Array[Len++] = Num;
        }
        else 
        {
            if(Len)
            { 
                BatchSize<<=1;
                ArrayNew = (int *)malloc(sizeof(int)*BatchSize);
                memcpy(ArrayNew,Array,sizeof(int)*Len);
                free(Array);
            }
            else 
            {
                ArrayNew = (int *)malloc(sizeof(int));
                BatchSize=1;
            }
            Array = ArrayNew;
            Array[Len++] = Num;    
        }
        
    }
    void pop_back()
    {
        if(Len < 1)return;
        if(Len == 1)
        {
            Len--;
            free(Array);
            BatchSize = 0;
            return;
        }
        if(Len-1 <= (BatchSize>>1))
        {
            BatchSize>>=1;
            ArrayNew = (int *)malloc(sizeof(int)*BatchSize);
            memcpy(ArrayNew,Array,sizeof(int)*BatchSize);
            free(Array);
            Array = ArrayNew;
            Len--;    
        }
        else Len--;
        
    }
    int size() const
    {
        return Len;
    }
    int &operator [] (int i) const 
    {
        return Array[i];
    }
    int batch_size() const 
    {
        return BatchSize;
    }
    vector &operator = (const vector &vec)
    {
        if(Array!=NULL)free(Array);
        Array = (int *)malloc(sizeof(int)*vec.batch_size());
        memcpy(Array,vec.Array,sizeof(int)*vec.batch_size());
        Len = vec.size();
        BatchSize = vec.batch_size();
        return (*this);
    }
};

typedef struct Data
{
    vector number;//值
    int point;
    int symbol;//符号
    Data &operator = (const Data &b)
    {
        number = b.number;
        point = b.point;
        symbol = b.symbol;
        return (*this);
    }
}Data;

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
    char sE[300]="271828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901";
    for(int i=0;i<=100;i++)
        vE.push_back(sE[100-i]-'0');
    return vE;
}

vector getPi()
{
    vector vPi;
    char sPi[300]="314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";
    for(int i=0;i<=100;i++)
        vPi.push_back(sPi[100-i]-'0');
    return vPi;
}

Data InttoData(int x)
{
    Data rlt;
    rlt.number.init();
    rlt.symbol=x<0?-1:1;
    x=x<0?-x:x;
    while(x){
        rlt.number.push_back(x%10);
        x/=10;
    }
    rlt.point=0;
    return rlt;
}

Data Error(int x)
{
    Data error;
    error.point=-x;
    return error;
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

//常量(自然常量)
const Data E={getE(),100,1};
//常量(圆周率)
const Data Pi={getPi(),100,1};
