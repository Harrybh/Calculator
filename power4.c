#include<stdio.h>
double pow_n(double num,double m)//定义求幂的函数
{
    double basic=1;
    int i;
    for(i=0;i<m;i++)
    {
        basic=basic*num;
    }
    return basic;
}

double pow_s(double num,double m)//定义求幂级数的函数
{
    int i,j;
    double basic2=0,temp=1;
    double x=num-1;
    for(i=1;temp>0.00000001||temp<-0.00000001;i++)//这里有修改
    {
        for(j=1,temp=1;j<=i;j++){
        temp*=(m-j+1)*x/j;
        }
        basic2+=temp;
    }
    return (basic2+1);
}

/*为解决底数较小，指数较大时，因循环不足导致的物差问题，
需要将指数分为整数和小数两部分，各自求幂后将两个部分相乘，
这时对指数为整数时，利用pow_n直接求；当指数为小数时，
利用pow_s来求*/

/*设置入口函数，判断使用函数的种类*/
double etc(double num,double m)
{
   
    if(num==0&&m!=0)
        return 0;
    else if(num==0&&m==0)
        return 1;
    else if(num<0&&m-(int)m!=0)//出错
        return 0;
    if(num>2)
    {
        num=1/num;
        m=-m;
    }
    if(m<0)
    return 1/etc(num,-m);
    if(m==(int)m)
    return pow_n(num,m);
    else
    return pow_s(num,m-(int)m)*pow_n(num,(int)m);

}
int main()
{
    double num,m;
    printf("请输入底数和幂：");
    scanf("%lf %lf",&num,&m);
    double result;
    result=etc(num,m);
    printf("Result is %lf",result);
    return 0;
}