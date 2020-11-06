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
long long jc[1010000],fjc[1010000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
long long ksm(long long x,long long k)
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
int fa[1010000],p[1010000];
long long f[1010000];
int a[1010000],tot[1010000];
int list[1010000];
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	int n;read(n);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[n]=ksm(jc[n],1000000005);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	memset(p,0,sizeof(p));
	for(int i=2;i<=n;i++)
	{
		read(fa[i]);
		p[fa[i]]++;
	}
	for(int i=1;i<=n;i++)f[i]=1;
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		tot[i]=0;
	}
	int head=1,tail=1;
	for(int i=1;i<=n;i++)if(p[i]==0)list[tail++]=i;
	while(head<tail)
	{
		int x=list[head];
		a[x]--;tot[x]++;
		a[fa[x]]+=a[x];
		tot[fa[x]]+=tot[x];
		f[fa[x]]=f[fa[x]]*f[x]%1000000007*C(a[fa[x]],a[x])%1000000007*C(tot[fa[x]],tot[x])%1000000007;
		p[fa[x]]--;
		if(p[fa[x]]==0)list[tail++]=fa[x];
		head++;
	}
	printf("%lld\n",f[1]);
	return 0;
}