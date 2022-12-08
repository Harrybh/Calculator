#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define POINT_LIMIT 100

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
    int point; //小数点位数
    int symbol;//符号
    int error; //错误属性
    /*
    1. 非法字符
    2. 语法错误
    3. 数学错误
    4. 数字过大
    */
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
    char sE[1005]="271828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901157383418793070215408914993488416750924476146066808226480016847741185374234544243710753907774499206955170276183860626133138458300075204493382656029760673711320070932870912744374704723069697720931014169283681902551510865746377211125238978442505695369677078544996996794686445490598793163688923009879312773617821542499922957635148220826989519366803318252886939849646510582093923982948879332036250944311730123819706841614039701983767932068328237646480429531180232878250981945581530175671736133206981125099618188159304169035159888851934580727386673858942287922849989208680582574927961048419844436346324496848756023362482704197862320900216099023530436994184914631409343173814364054625315209618369088870701676839642437814059271456354906130310720851038375051011574770417189861068739696552126715468895703503";
    for(int i=0;i<=POINT_LIMIT;i++)
        vE.push_back(sE[POINT_LIMIT-i]-'0');
    return vE;
}

vector getPi()
{
    vector vPi;
    char sPi[1005]="31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989";
    for(int i=0;i<=POINT_LIMIT;i++)
        vPi.push_back(sPi[POINT_LIMIT-i]-'0');
    return vPi;
}

Data InttoData(int x)
{
    Data rlt;
    rlt.number.init();
    rlt.symbol=x<0?-1:1;
    rlt.error=0;
    x=x<0?-x:x;
    if(!x) rlt.number.push_back(x);
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
    error=InttoData(0);
    error.error=x;
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
const Data E={getE(),POINT_LIMIT,1,0};
//常量(圆周率)
const Data Pi={getPi(),POINT_LIMIT,1,0};
