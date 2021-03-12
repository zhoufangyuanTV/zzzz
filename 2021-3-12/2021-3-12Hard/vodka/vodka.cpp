#include<cstdio>
#include<cstring>
using namespace std;
struct poly{int a[2004];};
inline poly operator*(poly x,poly y)
{
	poly z;
	for(int i=0;i<=2003;i++)
	{
		z.a[i]=0;
		for(int j=0;j<=i;j++)z.a[i]=(z.a[i]+x.a[j]*y.a[i-j])%2003;
	}
	return z;
}
poly ksm(poly x,int k)
{
	poly s;
	memset(s.a,0,sizeof(s.a));s.a[0]=1;
	while(k>0)
	{
		if(k&1)s=s*x;
		x=x*x;
		k>>=1;
	}
	return s;
}
inline int ksm(int x,int k)
{
	int s=1;
	while(k>0)
	{
		if(k&1)s=s*x%2003;
		x=x*x%2003;
		k>>=1;
	}
	return s;
}
int S[3100][3100];
int main()
{
	freopen("vodka.in","r",stdin);
	freopen("vodka.out","w",stdout);
	int n,K,L,F;scanf("%d%d%d%d",&n,&K,&L,&F);K%=2003;
	S[1][1]=1;
	for(int i=2;i<=F;i++)
	{
		S[i][1]=1;
		for(int j=2;j<=i;j++)S[i][j]=(S[i-1][j-1]+j*S[i-1][j])%2003;
	}
	poly f;
	memset(f.a,0,sizeof(f.a));
	for(int i=1;i<=F&&i<=2003;i++)f.a[i]=S[F][i];
	f=ksm(f,L);
	int ss=0,s=1;
	for(int i=1;i<=2003&&i<=n;i++)
	{
		s=s*(n-i+1ll)%2003;
		ss=(ss+ksm(K,n-i)*s%2003*f.a[i])%2003;
	}
	printf("%d\n",ss*ksm(ksm(K,n),2001)%2003);
	return 0;
}