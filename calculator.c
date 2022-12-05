#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"data.h"

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
Data Abs(Data x);
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
void Write(Data x)
Data Cal();

//用于获取输入的字符
char input;

int main()
{
    Data rlt,a,b;
    rlt=Cal();
    printf("%d\n",rlt.symbol*rlt.number);
    return 0;
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
    if(x.number<=0||x.point!=0){
        perror("algorithmic error!\n");
        exit(-1);
    }
    Data rlt=x;
    Data one=InttoData(1);
    for(Data i=x-one;i=i-one;i>=one){
        rlt=rlt*i;
        if(rlt.number.size()>100);
            //error
    }
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
    rlt.number.init();
    switch(input){
        case 'a':
            rlt=Abs(Read(1));
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
    if(input=='-'){
        if(symbol=-1){
            perror("syntax error!\n");
            exit(-1);
        }
        symbol=-1;
        input=getchar();
    }
    if(input=='('){
        //当读取到左括号时，对括号内内容进行运算并返回计算结果
        rlt=Cal();
    }
    else if(input<='z'&&input>='a'){
        if(input=='e') rlt=E;
        else if(input=='p'){
            rlt=Pi;
            input=getchar();
        }
        else{
            //当读到字母时，对函数进行运算返回函数值
            rlt=FunctionProcessor();
        }
    }
    else{
        //读取数字
        rlt.number.init();
        rlt.symbol=1;
        rlt.point=0;
        if(input>'9'||input<'0'){
            perror("syntax error!\n");
            exit(-1);
        }
        vector tmp;
        int pointPos=0;
        tmp.init();
        while((input<='9'&&input>='0')||(input=='.')){
            if(input=='.')
                rlt.point=pointPos;
            else   
                tmp.push_back(input-'0');
            pointPos++;
            input=getchar();
        }
        for(int i=tmp.size()-1;i>=0;i--)
            rlt.number.push_back(tmp[i]);
        if(rlt.point) rlt.point=rlt.number.size()-rlt.point;
        if(input=='e'){
            rlt=rlt*E;
        }
        else if(input=='p'){
            rlt=rlt*Pi;
            input=getchar();
        }
        else{
            //当读到字母时，对函数进行运算返回函数值
            rlt=rlt*FunctionProcessor();
        }
    }
    rlt.symbol*=symbol;
    //处理幂
    if(input=='^')
        rlt=Pow(rlt,Read(1));
	return rlt;
}

void Write(Data x)
{
    int end=0;
    while(!x.number[end]) end++;
    if(x.symbol<0) putchar('-');
    for(int i=x.number.size()-1;i>=end;i--){
        printf("%d",x.number[i]);
        if(i==x.point) putchar('.');
    }
    putchar('\n');
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
                Top(st)->data=(Top(st)->data)*Read(1);
                break;
			case '/':
                Top(st)->data=(Top(st)->data)/Read(1);
                break;
            case '%':
                Top(st)->data=(Top(st)->data)%Read(1);
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
		rlt=rlt+Top(st)->data;
		Pop(st);
	}
    free(st);  //计算完后
    return rlt;
}
