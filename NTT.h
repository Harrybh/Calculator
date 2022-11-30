#include<data.h>
const int maxn=1e6+10;
const int mod=998244353,gs=3;
int rev[maxn],lim,len;
int A_tmp[maxn],B_tmp[maxn];
void init(int Len)
{
    lim=1,len=0;
    while(lim<=Len)lim<<=1,len++;
    for(int i=1;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
    for(int i=0;i<lim;i++)A_tmp[i]=B_tmp[i]=0;
}
inline void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int Pow(int a,long long k)
{
    int ret=1;
    while(k)
    {
        if(k&1)ret=ret*1LL*a%mod;
        k>>=1,a=a*1LL*a%mod;
    }
    return ret;
}
void NTT(int *a,int type)
{
    for(int i=0;i<lim;i++)if(rev[i]>i)swap(&a[rev[i]],&a[i]);
    for(int mid=1;mid<lim;mid<<=1)
    {
        int wn=Pow(gs,(mod-1)/(mid<<1));
        if(type==-1)wn=Pow(wn,mod-2);
        for(int i=0;i<lim;i+=mid<<1)
        for(int j=0,w=1;j<mid;j++,w=w*1LL*wn%mod)
        {
            int x=a[i+j],y=a[i+j+mid]*1LL*w%mod;
            a[i+j]=(x+y)%mod;
            a[i+j+mid]=(x+mod-y)%mod;
        }
    }
    if(type==-1)
    {
        int inv=Pow(lim,mod-2);
        for(int i=0;i<lim;i++)a[i]=a[i]*1LL*inv%mod;
    }
}
inline int min(const int &a,const int &b){return a>b?b:a;}
inline int max(const int &a,const int &b){return b>a?b:a;}
inline void Process_NTT(const Data &a,const Data &b,Data *c)
{
    int lim1 = a.number.size(), lim2 = b.number.size();
    init(max(lim1,lim2));
    for(int i = 0;i <= min(lim1,lim); i++)A_tmp[i]=a.number[i];
    for(int i = 0;i <= min(lim2,lim); i++)B_tmp[i]=b.number[i];
    NTT(A_tmp,1),NTT(B_tmp,1);
    for(int i = 0;i < lim; i++)A_tmp[i]=A_tmp[i]*1LL*B_tmp[i]%mod;
    NTT(A_tmp,-1);
    while(c->number.size()<lim)c->number.push_back(0);
    for(int i = 0;i < lim; i++)c->number[i] = A_tmp[i];
}