#include<cstdio>
#include<cstring>
using namespace std;
struct matrix
{
	int n,m,a[145][145];
}A,B,S,F;
matrix operator+(matrix x,matrix y)
{
	matrix z;z.n=x.n;z.m=x.m;
	for(int i=1;i<=z.n;i++)
	{
		for(int j=1;j<=z.m;j++)
		{
			z.a[i][j]=(x.a[i][j]+y.a[i][j])%1000000007;
		}
	}
	return z;
}
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
				z.a[i][j]=(z.a[i][j]+1ll*x.a[i][k]*y.a[k][j])%1000000007;
			}
		}
	}
	return z;
}
matrix ksm(matrix x,long long k)
{
	matrix s,f;s.n=f.n=x.n;s.m=f.m=x.m;
	for(int i=1;i<=x.n;i++)
	{
		for(int j=1;j<=x.m;j++)
		{
			s.a[i][j]=f.a[i][j]=i==j;
		}
	}
	while(k>0)
	{
		if(k&1)s=s*x+f;
		f=f*x+f;
		x=x*x;
		k>>=1;
	}
	return s;
}
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x;
		x=x*x;
		k>>=1;
	}
	return s;
}
char s[13],t[13];
int main()
{
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1);
	int c1,c2,c3,c4;scanf("%d%d%d%d",&c1,&c2,&c3,&c4);
	int ss=0,sr=0,sj=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='a'&&t[i]=='b')ss+=c1,sr++;
		else if(s[i]=='a'&&t[i]=='c')ss+=c1+c2,sj++;
		else if(s[i]=='b'&&t[i]=='c')ss+=c2,sr++;
		else if(s[i]=='b'&&t[i]=='a')ss+=c2+c3,sj++;
		else if(s[i]=='c'&&t[i]=='a')ss+=c3,sr++;
		else if(s[i]=='c'&&t[i]=='b')ss+=c3+c1,sj++;
	}
	long long GG=sr+sj*2+(c4-ss)/(c1+c2+c3)*3;
	matrix A;A.n=(n+1)*(n+1);A.m=(n+1)*(n+1);
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if(i>0)A.a[i*(n+1)+j+1][(i-1)*(n+1)+j+2]=i;
			if(j>0)A.a[i*(n+1)+j+1][i*(n+1)+j]=j;
			if(i+j<n)A.a[i*(n+1)+j+1][(i+1)*(n+1)+j+1]=n-i-j;
		}
	}
	printf("%lld\n",ksm(A,GG).a[sj*(n+1)+sr+1][1]%1000000007);
	return 0;
}