#include<cstdio>
#include<cstring>
using namespace std;
inline long long ksm(long long x,long long k)
{
	long long ss=1;
	while(k>0)
	{
		if(k&1)ss=ss*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return ss;
}
int s;
long long g(int,int);
long long h(int,int);
long long f(int n,int k)
{
	if(n&1)n++;
	return (h(n,k)-g(n,k)+998244353)*499122177%998244353;
}
long long g(int n,int k)
{
	if(k==0)return 0;
	return k*f(n,k-1)%998244353;
}
long long h(int n,int k)
{
	long long ss1=1,ss2=1;
	for(int i=n+s-k+1;i<=n+s+1;i++)ss1=ss1*i%998244353;
	for(int i=s-k+1;i<=s+1;i++)ss2=ss2*i%998244353;
	return (ss1-ss2+998244353)*ksm(k+1,998244351)%998244353;
}
int main()
{
	freopen("pk.in","r",stdin);
	freopen("pk.out","w",stdout);
	int L,R,type;scanf("%d%d%d%d",&L,&R,&s,&type);
	if(type==1)printf("%lld\n",(h(R,s+1)-h(L-1,s+1)+998244353)%998244353);
	else
	{
		if(s&1)printf("%lld\n",(h(R,s+1)-h(L-1,s+1)-f(R,s+1)+f(L-1,s+1)+1996488706)%998244353);
		else printf("%lld\n",(f(R,s+1)-f(L-1,s+1)+998244353)%998244353);
	}
	return 0;
}