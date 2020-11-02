#include<cstdio>
#include<cstring>
using namespace std;
const long long p=4611686018427387904ll;
inline long long mul(long long x,long long y){return x*y-(long long)((long double)x*y/p)*p;}
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void write(int x)
{
	long long y=10;
	while(y<=x)y*=10;
	while(y!=1){y=y/10;putchar(x/y+'0');x=x%y;}
	putchar('\n');
}
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=mul(s,x);
		x=mul(x,x);
		k>>=1;
	}
	return s;
}
inline long long ksm(long long k)
{
	long long s=1,x=2;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
inline long long lowbit(long long x){return x&-x;}
int main()
{
	freopen("journey.in","r",stdin);
	freopen("journey.out","w",stdout);
	int t;read(t);
	while(t--)
	{
		int a,b,n;read(a);read(b);read(n);
		int cnt=0;
		while(a%2==0&&b%2==0)
		{
			cnt+=n;a/=2;b/=2;
		}
		if(a%2==0||b%2==0)printf("%lld\n",ksm(cnt));
		else
		{
			long long aa=ksm(a,n),bb=ksm(b,n);
			if((aa^bb)==0)printf("%lld\n",p%1000000007*ksm(cnt)%1000000007);
			else printf("%lld\n",lowbit(aa^bb)%1000000007*ksm(cnt)%1000000007);
		}
	}
	return 0;
}