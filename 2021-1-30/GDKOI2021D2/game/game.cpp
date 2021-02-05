#include<cstdio>
#include<cstring>
using namespace std;
template<typename T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline long long ksm(long long x,long long k)
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
long long EA[1010000],EB[1010000],p[1010000];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n;read(n);
	for(int i=0;i<n;i++)
	{
		long long x,y;read(x);read(y);
		p[i]=x*ksm(y,998244351)%998244353;
	}
	EA[n]=EB[n]=0;
	for(int i=n-1;i>=1;i--)
	{
		long long Omega=ksm(998244354-EA[i+1]*p[i]%998244353,998244351);
		EA[i]=Omega*(998244354-p[i])%998244353;
		EB[i]=Omega*(p[i]*EB[i+1]%998244353+1)%998244353;
	}
	long long Zeta=ksm(p[0]*(998244354-EA[1])%998244353,998244351);
	printf("%lld\n",Zeta*(p[0]*EB[1]%998244353+1)%998244353);
	return 0;
}
