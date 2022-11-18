#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"stack.h"

Data Add(Data a,Data b);
Data Sub(Data a,Data b);
Data Mul(Data a,Data b);
Data Div(Data a,Data b);
Data Read(int symbol);
Data Cal();

char input;

int main()
{
    Data rlt,a,b;
    rlt=Cal();
    printf("%d\n",rlt.symbol*rlt.number);
    return 0;
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
    if(b.number==0){
        perror("algorithmic error!\n");
        exit(-1);
    }
    Data rlt;
    rlt.symbol=a.symbol/b.symbol;
    rlt.number=a.number/b.number;
    return rlt;
}

Data Pow(Data a,Data b)
{
    Data rlt;
    rlt.symbol=a.symbol;
    rlt.number=a.number;
    for(int i=2;i<=b.number;i++)
        rlt.number*=a.number;
    return rlt;
}

Data Fac(Data x)
{
    if(x.number<=0){
        perror("algorithmic error!\n");
        exit(-1);
    }
    Data rlt;
    rlt.symbol=x.symbol;
    rlt.number=1;
    for(int i=2;i<=x.number;i++)
        rlt.number*=i;
    return rlt;
}

Data Read(int symbol)
{
	Data rlt;
    rlt.symbol=symbol;
    rlt.number=0;
	while((input=getchar())==' ');
    if(input=='('){
        rlt=Cal();
        rlt.symbol=symbol;
        return rlt;
    }
    if(input>'9'||input<'0'){
        perror("syntax error!\n");
        exit(-1);
    }
	while(input<='9'&&input>='0'){
		rlt.number*=10;
		rlt.number+=input-'0';
        input=getchar();
	}
    if(input=='^')
        rlt=Pow(rlt,Read(1));
	return rlt;
}

Data Cal()
{
	Stack *st=Init();
	Push(st,InitStackMember(Read(1)));
	while(input!='\n'&&input!=')'){
		switch(input){
			case '+': Push(st,InitStackMember(Read(1))); break;
			case '-': Push(st,InitStackMember(Read(-1))); break;
			case '*': Top(st)->data=Mul(Top(st)->data,Read(1)); break;
			case '/': Top(st)->data=Div(Top(st)->data,Read(1)); break;
            case '!': Top(st)->data=Fac(Top(st)->data); input=getchar(); break;
			default: perror("illegal word!\n"); exit(-1);
		}
	}
    if(input==')') input=getchar();
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