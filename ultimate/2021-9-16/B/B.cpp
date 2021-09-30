#include<cstdio>
#include<cstring>
using namespace std;
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
long long a[310][310];
int p[310],b[310],c[310],d[310];
inline long long plus(long long x,long long y){return x+y<1000000007?x+y:x+y-1000000007;}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	int n,x;scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)scanf("%d",&d[i]);
	for(int i=2;i<=n;i++)scanf("%d%d%d",&p[i],&b[i],&c[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)a[i][j]=d[i];
			else if(i<j)
			{
				if(i==p[j])a[i][j]=b[j];
				else a[i][j]=x;
			}
			else if(i>j)
			{
				if(j==p[i])a[i][j]=c[i];
				else a[i][j]=x;
			}
		}
	}
	long long ss=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i][i]==0)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[j][i]>0)
				{
					for(int k=i;k<=n;k++)a[i][k]=plus(a[i][k],a[j][k]);
					break;
				}
			}
			if(a[i][i]==0){ss=0;break;}
		}
		ss=ss*a[i][i]%1000000007;
		long long g=ksm(1000000007-a[i][i],1000000005);
		for(int j=i+1;j<=n;j++)
		{
			long long f=g*a[j][i]%1000000007;
			for(int k=i;k<=n;k++)a[j][k]=(a[j][k]+a[i][k]*f)%1000000007;
		}
	}
	printf("%lld\n",ss);
	return 0;
}