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
long long jc[11000],fjc[11000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	if(n<m)
	{
		puts("0");
		return 0;
	}
	jc[0]=1;
	for(int i=1;i<=n*2;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n*2]=ksm(jc[n*2],998244351);
	for(int i=n*2-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	long long ss=0;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			int x=0x3f3f3f3f;
			if(j!=0)x=mymin(x,i/j);
			if(j!=m)x=mymin(x,(n-i)/(m-j));
			ss=(ss+x*C(i+j,i)%998244353*C(n+m-i-j,n-i))%998244353;
		}
	}
	printf("%lld\n",ss);
	return 0;
}
