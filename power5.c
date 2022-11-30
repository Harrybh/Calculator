#include<stdio.h>
#include"vector.h"
/* base是底数，index是指数，本函数用来将a^b转化为b*lna */
Data ln(double base,double index)
{
    double base2=base-1;//麦克劳林展开：ln(x+1)=x-x^2/2!+x^3/3!-...
    int flag=1;//用来决定展开式每一项的正负号
    double result=0,temp=1;//temp存储每一项的值，result是总和

    /*底数为负数：1.当指数为偶数，利用偶函数直接算；
    2.指数为奇数,先将底数变为正数计算*/
    if(base2<0)
    {
       if(index%2==0)
       base2=-base2;
       for(int i=1;i<50;i++)
       {
           for(int j=1,temp=1;j<=i;j++)
           {
               temp*=flag*base/j;
           }   
           flag=-flag;
           result+=temp;
       }
        Data result2=result*index;
        return result2;

        else
        {
            base2=-base2;

           for(int i=1;i<50;i++)
           {
              for(int j=1,temp=1;j<=i;j++)
              {
                  temp*=flag*base/j;
              }   
              flag=-flag;
              result+=temp;
           }
           Data result2=result*index;
           return result2;
        }
    }

    else if(base2==0)//底数为0
    {
        if(index==0)
        return 1;
        else
        return 0;
    }
   

    else{                         
    for(int i=1;i<50;i++)
    {
        for(int j=1,temp=1;j<=i;j++)
        {
            temp*=flag*base/j;
        }   
        flag=-flag;
        result+=temp;
    }
        Data result2=result*index;
        return result2;
    }
}

/*还是得要三个参数*/
Data Exp(Data result2,double base,double index)
{
    Data final=1;
    double temp=1;
    for(int i=1;i<=50;i++)
    {
        for(int j=1;j<=i;j++)
           temp*=result2/j;
        final+=temp;
    }
    if(base<0&&index%2!=0)
    return -final;
    else
    return final;  
}