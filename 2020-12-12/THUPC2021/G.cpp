#include<cstdio>
#include<cstring>
using namespace std;
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
long long f[4096][4096],ff[4096][4096],a[21][21],c[4096][21];
int p[21],plen,pp[21],pplen,ppp[21],ppplen;
int main()
{
	int n,t;scanf("%d%d",&n,&t);
	for(int i=1;i<=n*(n-1);i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		long long p,q;scanf("%lld%lld",&p,&q);
		a[x][y]=p*ksm(q,998244351)%998244353;
	}
	for(int i=0;i<1<<n;i++)
	{
		plen=0;
		for(int j=1;j<=n;j++)if((1<<j-1|i)==i)p[++plen]=j;
		for(int j=1;j<=n;j++)
		{
			c[i][j]=1;
			for(int k=1;k<=plen;k++)c[i][j]=c[i][j]*(998244354-a[p[k]][j])%998244353;
		}
	}
	long long ss=0;
	memset(f,0,sizeof(f));f[1][1]=1;
	while(t--)
	{
		for(int i=0;i<1<<n;i++)
		{
			for(int j=i;j>0;j=j-1&i)ff[i][j]=f[i][j],f[i][j]=0;
		}
		for(int i=0;i<1<<n;i++)
		{
			for(int j=i;j>0;j=j-1&i)
			{
				if(ff[i][j]!=0)
				{
					plen=pplen=0;
					for(int k=1;k<=n;k++)
					{
						if((i|1<<k-1)==i)
						{
							if((j|1<<k-1)==j)pp[++pplen]=k;
							else p[++plen]=k;
						}
					}
					for(int k=(1<<n)-1^i;k>0;k=k-1&((1<<n)-1^i))
					{
						ppplen=0;
						for(int l=1;l<=n;l++)
						{
							if((k|1<<l-1)==k)ppp[++ppplen]=l;
						}
						long long swy=1;
						for(int y=1;y<=ppplen;y++)swy=swy*c[i^j][ppp[y]]%998244353;
						for(int y=1;y<=ppplen;y++)swy=swy*(998244354-c[j][ppp[y]])%998244353;
						f[i|k][k]=(f[i|k][k]+ff[i][j]*swy)%998244353;
					}
				}
			}
		}
		for(int i=1;i<1<<n;i++)ss=(ss+f[(1<<n)-1][i])%998244353;
	}
	printf("%lld\n",ss);
	return 0;
}