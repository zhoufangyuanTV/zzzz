#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void read(long long &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
long long a[2010000];
long long b[2010000];
long long c[2010000];
long long fc[2010000];
int main()
{
	freopen("history.in","r",stdin);
	freopen("history.out","w",stdout);
	int n;read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)b[i]=(b[i-1]+a[i])%998244353;
	for(int i=1;i<=n;i++)c[i]=(c[i-1]+b[i])%998244353;
	fc[1]=1;
	for(int i=2;i<=n;i++)fc[i]=(998244353-fc[998244353%i])*(998244353/i)%998244353;
	long long ss=0;
	for(int i=0;i<n/2;i++)
	{
		long long f=fc[2*i+1]*fc[2*i+2]%998244353;
		ss=(ss+(c[n-i-1]-c[i+1]-c[n-2*i-2]+1996488706)*f)%998244353;
		f=fc[2*i+1];
		ss=(ss+b[i+1]*f)%998244353;
		if(2*i+3<=n)
		{
			f=fc[2*i+2]*fc[2*i+3]%998244353;
			ss=(ss+(c[n-1]-c[2*i+2]-c[n-i-2]+c[i+1]+1996488706)*f)%998244353;
			f=fc[2*i+2];
			ss=(ss+(b[n]-b[n-i-1]+998244353)*f)%998244353;
		}
	}
	printf("%lld\n",ss);
	return 0;
}