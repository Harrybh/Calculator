#include"operation.h"
#include<stdio.h>

void Write(Data x)
{
    if(x.symbol<0) putchar('-');
    for(int i=x.number.size()-1;i>=0;i--){
        printf("%d",x.number[i]);
        if(x.point&&i==x.point) putchar('.');
    }
    putchar('\n');
}

Data Read()
{
    Data rlt;
    char input;
    input=getchar();
    if(input=='-'){
        rlt.symbol=-1;
        input=getchar();
    }
    else
        rlt.symbol=1;
    rlt.number.init();
    vector tmp;
    int pointPos=0;
    tmp.init();
    rlt.point=0;
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
    return rlt;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("testout.txt","w",stdout);
    Data x,y;
    x=Read(),y=Read();
    Write(x*y);
    /*scanf("%d\n",&n);
    for(int i=1;i<=n;i++)
        x=Read(),y=Read(),Write(x+y);
    for(int i=1;i<=n;i++)
        x=Read(),y=Read(),Write(x-y);
    for(int i=1;i<=n;i++)
        x=Read(),y=Read(),Write(x*y);*/
    int n;
    return 0;
}