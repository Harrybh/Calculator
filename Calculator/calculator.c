#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>

//定义数据
typedef struct Data
{
    int number;
    int symbol;   
}Data;

//定义栈里的元素
typedef struct StackMember
{
    struct StackMember *next;
    Data data;
    
}StackMember;
//定义空成员

//定义栈
typedef struct Stack
{
    StackMember *top;
    int size;
}Stack;

Stack *Init();
StackMember *InitStackMember(Data data);
bool Empty(Stack *s);
StackMember *Top(Stack *s);
bool Push(Stack *s,StackMember *val);
bool Pop(Stack *s);
Data Add(Data a,Data b);
Data Sub(Data a,Data b);
Data Mul(Data a,Data b);
Data Div(Data a,Data b);
Data Read(int symbol,char *ch);
Data Cal();

char ch;

int main()
{
    Data rlt,a,b;
    rlt=Cal();
    printf("%d\n",rlt.symbol*rlt.number);
    return 0;
}

//初始化栈
Stack *Init()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));//申请栈的内存空间,并将空间的地址传给栈数据类型的指针.
    s->top=NULL;
    s->size=0;
    return s;//返回初始话栈的地址
}

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
    if (s == NULL)//判断栈是否存在
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
    s->top=s->top->next;
    return true;
}

Data Add(Data a,Data b)
{
    if(a.symbol<0&&b.symbol>0){
        a.symbol=1;
        return Sub(b,a);
    }
    if(b.symbol<0&&a.symbol>0){
        b.symbol=1;
        return Sub(a,b);
    }
    Data rlt;
    rlt.symbol=a.symbol;
    rlt.number=a.number+b.number;
    return rlt;
}

Data Sub(Data a,Data b)
{
    Data rlt;
    rlt.symbol=a.number>b.number?1:-1;
    rlt.number=rlt.symbol*(a.number-b.number);
    return rlt;
}

Data Mul(Data a,Data b)
{
    Data rlt;
    rlt.symbol=a.symbol*b.symbol;
    rlt.number=a.number*b.number;
    return rlt;
}

Data Div(Data a,Data b)
{
    Data rlt;
    if(b.number==0){
        perror("algorithmic error!\n");
        exit(1);
    }
    rlt.symbol=a.symbol/b.symbol;
    rlt.number=a.number/b.number;
    return rlt;
}

Data Read(int symbol)
{
	Data rlt;
    rlt.symbol=symbol;
    rlt.number=0;
	while((ch=getchar())==' ');
    if(ch=='('){
        rlt=Cal();
        rlt.symbol=symbol;
        return rlt;
    }
    if(ch>'9'||ch<'0'){
        perror("syntax error!\n");
        exit(1);
    }
	while(ch<='9'&&ch>='0'){
		rlt.number*=10;
		rlt.number+=ch-'0';
        ch=getchar();
	}
	return rlt;
}

Data Cal()
{
	Stack *st=Init();
	Push(st,InitStackMember(Read(1)));
	while(ch!='\n'&&ch!=')'){
		switch(ch){
			case '+': Push(st,InitStackMember(Read(1))); break;
			case '-': Push(st,InitStackMember(Read(-1))); break;
			case '*': Top(st)->data=Mul(Top(st)->data,Read(1)); break;
			case '/': Top(st)->data=Div(Top(st)->data,Read(1)); break;
			case '(': Push(st,InitStackMember(Cal())); break;
			default: perror("illegal word!\n"); exit(1);
		}
	}
    if(ch==')') ch=getchar();
	Data rlt;
    rlt.number=0;
    rlt.symbol=1;
	while(!Empty(st)){
		rlt=Add(rlt,Top(st)->data);
		Pop(st);
	}
    free(st);
    return rlt;
}