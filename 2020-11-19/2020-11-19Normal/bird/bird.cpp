#include<cstdio>
#include<cstring>
using namespace std;
#define p 1000000007
struct matrix
{
	int n,m;
	long long a[131][131];
}C,G,F,f;
matrix operator*(matrix x,matrix y)
{
	matrix z;z.n=x.n;z.m=y.m;
	for(int i=1;i<=z.n;i++)
	{
		for(int j=1;j<=z.m;j++)
		{
			z.a[i][j]=0;
			for(int k=1;k<=x.m;k++)
			{
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%p;
			}
		}
	}
	return z;
}
matrix operator+(matrix x,matrix y)
{
	matrix z;z.n=x.n;z.m=x.m;
	for(int i=1;i<=z.n;i++)
	{
		for(int j=1;j<=z.m;j++)z.a[i][j]=(x.a[i][j]+y.a[i][j])%p;
	}
	return z;
}
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("bird.in","r",stdin);
	freopen("bird.out","w",stdout);
	int n,k,a,b;scanf("%d%d%d%d",&n,&k,&a,&b);
	C.n=k;C.m=k;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(i==j+1||i==j||i==j-1)C.a[i][j]=1;
			else C.a[i][j]=0;
		}
	}
	long long pr=ksm(n-2,p-2);
	G.n=k;G.m=k;
	for(int i=1;i<=k;i++)
	{
		if(a<i&&i<b)
		{
			for(int j=1;j<=k;j++)
			{
				if(i==j+1||i==j||i==j-1)G.a[i][j]=pr;
				else G.a[i][j]=0;
			}
		}
		else for(int j=1;j<=k;j++)G.a[i][j]=0;
	}
	F.n=k;F.m=1;
	for(int i=1;i<=k;i++)F.a[i][1]=0;
	f=F;
	f.a[k/2][1]=1;
	int T=n-2;
	while(T>0)
	{
		if(T&1)
		{
			F=C*F+G*f;
			f=C*f;
		}
		G=C*G+G*C;
		C=C*C;
		T>>=1;
	}
	long long ss=0;
	if(k/2>1)ss=ss+F.a[k/2-1][1];
	ss=ss+F.a[k/2][1];
	if(k/2<k)ss=ss+F.a[k/2+1][1];
	printf("%lld\n",ss%p);
	return 0;
}