#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "operation.h"

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
//输出
void Write(Data x);
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

Data LogProcessor()
{
    Data rlt,x,y;
    input=getchar();
    switch (input)
    {
        case 'o':
            if(getchar()!='g') return Error(1);
            x=Ln(Read(1)),y=Ln(Read(1));
            rlt=y/x;
            break;
        case 'n':
            rlt=Ln(Read(1));
            break;
        case 'g':
            rlt=Ln(Read(1))/Ln(InttoData(10));
            break;
        default:
            return Error(1);
    }
    return rlt;
}

Data FunctionProcessor()
{
    Data rlt,nowNumber;
    rlt.number.init();
    switch(input){
        case 'a':
            if(getchar()!='b')
                return Error(1);
            if(getchar()!='s')
                return Error(1);
            nowNumber=Read(1);
            rlt=Abs(nowNumber);
            break;
        case 's':
            if(getchar()=='i'){
                if(getchar()!='n')
                    return Error(1);
                nowNumber=Read(1);
                rlt=Sin(nowNumber);
            }
            else if(getchar()=='q'){
                if(getchar()!='r')
                    return Error(1);
                if(getchar()!='t')
                    return Error(1);
                nowNumber=Read(1);
                rlt=Sqrt(nowNumber);
            }
            else 
                return Error(1);
            break;
        case 'c':
            if(getchar()!='o')
                return Error(1);
            if(getchar()!='s')
                return Error(1);
            nowNumber=Read(1);
            rlt=Cos(nowNumber); 
            break;
        case 't':
            if(getchar()!='a')
                return Error(1);
            if(getchar()!='n')
                return Error(1);
            nowNumber=Read(1);
            rlt=Tan(nowNumber);
            break;
        case 'l':
            rlt=LogProcessor();
            break;
        case 'f':
            if(getchar()!='a')
                return Error(1);
            if(getchar()!='c')
                return Error(1);
            if(getchar()!='t')
                return Error(1);
            nowNumber=Read(1);
            rlt=Fac(nowNumber);
            break;
        default:
            return Error(1);
    }
    return rlt;
}

Data Read(int symbol)
{
	Data rlt;
    input=getchar();
    if(input=='-'){
        if(symbol==-1)
			return Error(2);
        symbol=-1;
        input=getchar();
    }
    if(input=='('){
        //当读取到左括号时，对括号内内容进行运算并返回计算结果
        rlt=Cal();
    }
    else if(input<='z'&&input>='a'){
        if(input=='e'){
			rlt=E;
			input=getchar();
		}
        else if(input=='p'){
            rlt=Pi;
            if(getchar()!='i') return Error(1); 
            input=getchar();
        }
        else{
            //当读到字母时，对函数进行运算返回函数值
            rlt=FunctionProcessor();
        }
    }
    else if(input<='9'&&input>='0'){
        //读取数字
        rlt.number.init();
        rlt.symbol=1;
        rlt.error=0;
        rlt.point=0;
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
        if(rlt.number.size()>100)
            return Error(4);
        if(input=='e'){
            rlt=rlt*E;
            input=getchar();
        }
        else if(input=='p'){
            rlt=rlt*Pi;
            if(getchar()!='i') return Error(1); 
            input=getchar();
        }
        else if(input>='a'&&input<='z'){
            //当读到字母时，对函数进行运算返回函数值
            Data func=FunctionProcessor();
            if(func.error) return func;
            rlt=rlt*func;
        }
    }
    else{
        if(input=='+'||input=='-'||input=='*'||input=='/'||input==')'||input=='^')
            return Error(2);
        else
            return Error(1);
    }
    rlt.symbol*=symbol;
    //处理幂
    if(input=='^')
        rlt=Exp(rlt,Read(1));
	return rlt;
}

void Write(Data x)
{
    if(x.error){
        switch (x.error)
        {
            case 1:
            	putchar('1');
                printf("非法的字符！！！\n");
                break;
            case 2:
            	putchar('2');
                printf("语法错误！！！\n");
                break;
            case 3:
            	putchar('3');
                printf("数学错误！！！\n");
                break;
            case 4:
            	putchar('4');
                printf("数字过大！！！\n");
                break;
            default:
                printf("无该错误...\n");
                break;
        }
    }
    else{
    	bool flag=true;
		for (int i = x.number.size()-1; i >= 0; i--){
	    	if (i < x.point - 50) 
				break;
	    	if (x.number[i])
	            flag = false;
		}
		if(flag) x.symbol=1;
        if (x.symbol < 0)
            putchar('-');
        for (int i = x.number.size() - 1; i >= 0; i--)
        {
            if (i < x.point - 50) break;
            printf("%d", x.number[i]);
            if (x.point && i == x.point)
                putchar('.');
        }
        putchar('\n');
    }
}

Data Cal()
{
	Stack *st=Init();
    Data nowNumber,calNumber;
    nowNumber=Read(1);
	Push(st,InitStackMember(nowNumber));
	while(input!='\n'&&input!=')'){
        if(nowNumber.error)
            return nowNumber;
		switch(input){
			case '+':
                nowNumber=Read(1);
                Push(st,InitStackMember(nowNumber));
                break;
			case '-':
                nowNumber=Read(-1);
                Push(st,InitStackMember(nowNumber));
                break;
			case '*':
                nowNumber=Read(1);
                calNumber=(Top(st)->data)*nowNumber;
                if(calNumber.error) return calNumber;
                Top(st)->data=calNumber;
                break;
			case '/':
                nowNumber=Read(1);
                calNumber=(Top(st)->data)/nowNumber;
                if(calNumber.error) return calNumber;
                Top(st)->data=calNumber;
                break;
            case '%':
                nowNumber=Read(1);
                calNumber=(Top(st)->data)%nowNumber;
                if(calNumber.error) return calNumber;
                Top(st)->data=calNumber;
                break;
			default:
                free(st);
                if(input=='(') return Error(2);
                else return Error(1);
		}
	}
    if(input==')') input=getchar();
	Data rlt;
    rlt=InttoData(0);
    rlt.error=0;
	while(!Empty(st)){
		rlt=rlt+Top(st)->data;
		Pop(st);
	}
    free(st);  //计算完后释放栈的内存
    return rlt;
}
