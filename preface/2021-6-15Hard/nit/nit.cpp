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
int f[5100][5100],a[5100];
inline void plus(int &x,int y){x==-1?x=y:x+y<998244353?x+=y:x+=y-998244353;}
int main()
{
	freopen("nit.in","r",stdin);
	freopen("nit.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	long long fm=ksm(m,998244351);
	memset(f,-1,sizeof(f));f[n][0]=0;
	for(int i=n-1;i>=1;i--)
	{
		for(int j=0;j<=n-i;j++)
		{
			if(a[i]==a[i+1])
			{
				if(f[i+1][j]!=-1)plus(f[i][j],(f[i+1][j]+fm)%998244353);
			}
			else
			{
				if(f[i+1][j]!=-1)plus(f[i][j],f[i+1][j]*fm%998244353*(m-2)%998244353);
				if(f[i+1][j+1]!=-1)plus(f[i][j],(f[i+1][j+1]+1)*fm%998244353);
				if(j==0&&f[i+1][j]!=-1)plus(f[i][j],(f[i+1][j]+1)*fm%998244353);
				if(j>0&&f[i+1][j-1]!=-1)plus(f[i][j],f[i+1][j-1]*fm%998244353);
			}
		}
	}
	long long ss=0;
	for(int i=0;i<=n;i++)
	{
		if(f[1][i]!=-1)plus(ss,f[1][i]);
	}
	printf("%lld\n",ss);
	return 0;
}
