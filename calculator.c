#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"stack.h"

//加法
Data Add(Data a,Data b);
//减法
Data Sub(Data a,Data b);
//乘法
Data Mul(Data a,Data b);
//除法
Data Div(Data a,Data b);
//模
Data Mod(Data a,Data b);
//幂
Data Pow(Data a,Data b);
//对数函数
Data Log(Data a,Data b);
//阶乘
Data Fac(Data x);
//三角函数
Data Sin(Data x);
Data Cos(Data x);
Data Tan(Data x);
//开方
Data Sqrt(Data x);
//处理不同类型的对数函数
Data LogProcessor();
//识别当前input的字符，找到对应函数并返回函数值
Data FunctionProcessor();
/*
读取数字，并给input赋值为读取到的非数字字符；
识别字母字符，并交给FunctionProcessor处理；
识别^幂符号，并返回幂函数值。
*/
Data Read(int symbol);
/*
识别Read后input的字符(+ - * / %)，并改变栈中的值（* / %)或向栈内加入新元素(+ -);
以+ - * / %运算为基础，进行计算;
原理如下：
各类运算优先级为：函数运算,括号>幂>* / %>+ -；
因此，将所有运算提前算出(Read中)，只留下+ - * / %。
由于乘除模优先级大于加减，所以可以创建一个栈。
当读取到* / %时，直接对栈顶元素进行运算，
当读取到+时，向栈中加入+后面的数字，
当读取到-时，向栈中加入-后面的数字的相反数。
所有字符读取完后，将栈中元素一一相加，得到最终结果。
*/
Data Cal();

//用于获取输入的字符
char input;
//常量(自然常量)
const Data E={1,123};
//常量(圆周率)
const Data Pi={1,123};

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

Data Mod(Data a,Data b)
{
    Data rlt;
    rlt.number=0;
    rlt.symbol=0;
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

Data Sin(Data x)
{
    Data rlt;
    rlt.number=0;
    rlt.symbol=0;
    return rlt;
}

Data LogProcessor()
{
    Data rlt;
    rlt.number=10;
    rlt.symbol=1;
    input=getchar();
    switch (input)
    {
        case 'o':
            getchar();
            rlt=Log(Read(1),Read(1));
            break;
        case 'n':
            rlt=Log(E,Read(1));
            break;
        case 'g':
            rlt=Log(rlt,Read(1));
            break;
        default:
            perror("no such function!\n");
            exit(-1);
    }
    return rlt;
}

Data FunctionProcessor()
{
    Data rlt;
    switch(input){
        case 's':
            if(getchar()=='i')
                rlt=Sin(Read(1));
            else
                rlt=Sqrt(Read(1));
            break;
        case 'c':
            rlt=Cos(Read(1)); 
            break;
        case 't':
            rlt=Tan(Read(1));
            break;
        case 'l':
            rlt=LogProcessor();
            break;
        case 'f':
            rlt=Fac(Read(1));
        default:
            perror("no such function!\n"); 
            exit(-1);
    }
    return rlt;
}

Data Read(int symbol)
{
	Data rlt;
    input=getchar();
    if(input=='('){
        //当读取到左括号时，对括号内内容进行运算并返回计算结果
        rlt=Cal();
        rlt.symbol=symbol*rlt.symbol;
    }
    else if(input<='z'&&input>='a'){
        //当读到字母时，对函数进行运算返回函数值
        rlt=FunctionProcessor();
        rlt.symbol=symbol*rlt.symbol;
    }
    else{
        //读取数字
        rlt.number=0;
        if(input=='-'){
            rlt.symbol=-1;
            input=getchar();
        }
        else
            rlt.symbol=1;
        if(input>'9'||input<'0'){
            perror("syntax error!\n");
            exit(-1);
        }
        while(input<='9'&&input>='0'){
            rlt.number*=10;
            rlt.number+=input-'0';
            input=getchar();
        }
    }
    //处理幂
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
			case '+':
                Push(st,InitStackMember(Read(1)));
                break;
			case '-':
                Push(st,InitStackMember(Read(-1)));
                break;
			case '*':
                Top(st)->data=Mul(Top(st)->data,Read(1));
                break;
			case '/':
                Top(st)->data=Div(Top(st)->data,Read(1));
                break;
            case '%':
                Top(st)->data=Mod(Top(st)->data,Read(1));
                break;
			default:
                perror("illegal word!\n");
                exit(-1);
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
    free(st);  //计算完后
    return rlt;
}