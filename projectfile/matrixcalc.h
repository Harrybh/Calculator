#define MATRIX_SIZE 110
long long gcd(long long a, long long b){return b?gcd(b,a%b):a;}
template <typename T>inline T abs(T const &x){return x<0?-x:x;}
template <typename T>inline void swap(T *x,T *y)
{
    T t = *y;
    *y = *x;
    *x = t;
}
struct myMatrix
{
    double mtx[MATRIX_SIZE][MATRIX_SIZE];
    int n;
    void Gauss()
    {
        for(int i=1,k;i<=n;i++)
        { 
            k=i;
            double del = 0;
            for(int j=i+1;j<=n;j++)if(mtx[j][i]>mtx[k][i])k=j;
            if(abs(del=mtx[k][i])<1e-8)continue;
            for(int j=i;j<=n+1;j++)swap(&mtx[k][j],&mtx[i][j]);
            for(int j=i;j<=n+1;j++)mtx[i][j]=mtx[i][j]/del;
            for(k=1;k<=n;k++)
            if(k!=i)
            {
                del=mtx[k][i];
                for(int j=i;j<=n+1;j++)mtx[k][j]=mtx[k][j]-mtx[i][j]*del;
            }
        }
    }
    void Inv()
    {
    	for(int i=1;i<=n;i++)mtx[i][i+n]=1;
    	for(int i=1,k;i<=n;i++)
        { 
            k=i;
            double del = 0;
            for(int j=i+1;j<=n;j++)if(mtx[j][i]>mtx[k][i])k=j;
        	if(abs(del=mtx[k][i])<1e-8)continue;
            for(int j=i;j<=n+n;j++)swap(&mtx[k][j],&mtx[i][j]);
            for(int j=i;j<=n+n;j++)mtx[i][j]=mtx[i][j]/del;
            for(k=1;k<=n;k++)
            if(k!=i)
            {
                del=mtx[k][i];
                for(int j=i;j<=n+n;j++)mtx[k][j]=mtx[k][j]-mtx[i][j]*del;
            }
        }
	}
	void Clm()
	{
		Gauss();
	}
	int Rank()
	{
		int cur=n;
		for(int i=1,k;i<=n;i++)
        { 
            k=i;
            double del = 0;
            for(int j=i+1;j<=n;j++)if(mtx[j][i]>mtx[k][i])k=j;
            if(abs(del=mtx[k][i])<1e-8)
			{
				cur--;
				continue;
			}
            for(int j=i;j<=n+1;j++)swap(&mtx[k][j],&mtx[i][j]);
            for(int j=i;j<=n+1;j++)mtx[i][j]=mtx[i][j]/del;
            for(k=1;k<=n;k++)
            if(k!=i)
            {
                del=mtx[k][i];
                for(int j=i;j<=n+1;j++)mtx[k][j]=mtx[k][j]-mtx[i][j]*del;
            }
        }
        return cur;
	}
    myMatrix operator * (const myMatrix &b)const
    {
        myMatrix c;
        c.n=n;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)c.mtx[i][j]=0;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        for(int k=1;k<=n;k++)c.mtx[i][j]+=mtx[i][k]*b.mtx[k][j];
        return c;
    }
    myMatrix operator ^ (const int &k)const
    {
        myMatrix c,a;
        c.n=a.n=n;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)c.mtx[i][j]=0;
        for(int i=1;i<=n;i++)c.mtx[i][i]=1;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)a.mtx[i][j]=mtx[i][j];
        int t=k;
        while(t)
        {
            if(t&1)c=c*a;
            a=a*a;
            t>>=1;
        }
        return c;
    }
};
double Det(myMatrix x)
{
    if(x.n==2)return x.mtx[1][1]*x.mtx[2][2]-x.mtx[1][2]*x.mtx[2][1];
    if(x.n==1)return x.mtx[1][1];
    int n=x.n;
    myMatrix tmp;
    double ans=0;
    tmp.n=n-1;
    for(int t=1;t<=n;t++)
    {
        for(int i=2;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(j==t)continue;
            tmp.mtx[i-1][j>t?j-1:j]=x.mtx[i][j];
        }
        ans+=x.mtx[1][t]*Det(tmp)*(t&1?1:-1);
    }
    return ans;
}
