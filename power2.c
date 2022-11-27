#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[3000];//读入存入的结果
int pre[3000];//已经算出的结果
int now[3000];//当前的结果
char s[3000];//读入底数（单个字符的形式），后面需要将它通过-'0'操作转换为数字

int main()
{
    int i,j,k,t,flag,point,num,l2;

    printf("input number to calculate and \'0\' to quit.\n");
    /*死循环，但是输入quit n 可退出循环*/
    
    while(scanf("%s %d",s,&num)!=EOF)
    {
        memset(a,0,sizeof(a));
        int integer=0,flag=0;
        //integer是从后往前算整数部分的位数，flag用来判断是否读到‘.‘
        int l=strlen(s);
        for(i=0;i<l;i++)
        {
           if(s[i]=='.')
           {
              flag=1;
              break;
            }
          integer++;//integer用来“记录”整数部分
        }
        if(flag==1)
           l--;//找到小数点的位置后，此时l--，删去'.'的占位，现在整个底数由两部分组成（整数部分与小数部分）
        for(j=i;s[j]!='\0';j++)//计算底数中小数部分的位数，并将小数点后移
        {
            s[j]=s[j+1];
        } 


        /*现在，我们计算n次幂下小数点的位数*/
        point=(l-integer)*num;
        /*接下来对小数部分进行计算*/
        for(i=0;i<l;i++)
        
            a[i]=s[l-i-1]-'0';// -'0'操作将字符转化为整数，类比小学乘法，从后往前逐个存储小数和整数部分

            for(integer=0;integer<3000;integer++)
            {
               pre[integer]=0;
            }
            pre[0]=1;
            l2=1;
            for(i=1;i<=num;i++)
            {
                 memset(now,0,sizeof(now));
                 /*使用两个循环，第一个控制乘法中位数的递进，
			          第二个循环控制该位数分别乘整个字符串*/
                 for(j=0;j<l;j++)
                 {
                    for(k=0;k<l2;k++)
                    now[k+j]+=a[j]*pre[k];
                 }
                 for(k=0;k<l+l2;k++)
                 {
                    now[k+1]+=now[k]/10;
                    now[k]=now[k]%10;
                 }
                 memcpy(pre,now,sizeof(now));
                 l2+=l;
            }
                while(pre[l2]==0)
                {
                  l2--;
                }
                for(i=l2;i>=point;i--)
                {
                  printf("%d",pre[i]);
                }
                for(i=0;i<point;i++)
                {
                  if(pre[i]!=0)
                  break;
                }
                if(i<point)
                {
                   printf(".");
                   for(j=point-1;j>=i;j--)
                   printf("%d",pre[j]);
                }
                printf("\n");
    }
             return 0;
 
}
