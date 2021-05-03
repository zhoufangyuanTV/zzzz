#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int p[410000],s;
bool b[410000];
int mu[410000];
int D[410000];
vector<int> d[410000];
long long f[410000],g[410000];
long long F[410000],G[410000];
long long fg[410000];
inline void plus(long long &x,long long y){x+y<998244353?x+=y:x+=y-998244353;}
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int main()
{
	freopen("lalaland.in","r",stdin);
	freopen("lalaland.out","w",stdout);
	int n,m,op;read(n);read(m);read(op);
	memset(b,true,sizeof(b));
	s=0;b[1]=false;mu[1]=1;
	for(int i=2;i<=m;i++)
	{
		if(b[i])
		{
			p[++s]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=s&&i*p[j]<=m;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)
			{
				mu[i*p[j]]=0;
				break;
			}
			else mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=i;j<=m;j+=i)D[j]++;
		d[i].resize(D[i]);
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=i;j<=m;j+=i)d[j][--D[j]]=i;
	}
	long long ss=0;
	for(int i=1;i<=m;i++)
	{
		for(int k:d[i])
		{
			ss=ss+mu[k]*(fg[k]*i*2+1ll*i*i);
			plus(fg[k],i);
		}
		f[i]=ss=(ss%998244353+998244353)%998244353;
	}
	ss=0;
	memset(fg,0,sizeof(fg));
	for(int i=1;i<=m;i++)
	{
		for(int k:d[i])
		{
			if(mu[i]==1)
			{
				ss=ss+mu[k]*(fg[k]*2+1);
				fg[k]==998244352?fg[k]=0:fg[k]++;
			}
			else if(mu[i]==-1)
			{
				ss=ss+mu[k]*(1-fg[k]*2);
				fg[k]==0?fg[k]=998244352:fg[k]--;
			}
		}
		g[i]=ss=(ss%998244353+998244353)%998244353;
	}
	for(int i=1;i<=m;i++)
	{
		for(int k:d[i])G[i]+=g[k]*mu[i/k];
		G[i]=(G[i]%998244353+998244353)%998244353;
	}
	ss=0;
	for(int i=1;i<=n;i++)
	{
		int x;read(x);
		if(op==1)x=(19891989*ss+x)%m+1;
		for(int k:d[x])
		{
			long long S=(F[k]+1)*f[x]%998244353;
			ss=(ss+S*G[k])%998244353;
			plus(F[k],S);
		}
		if(op==1)printf("%lld\n",ss);
	}
	if(op==0)printf("%lld\n",ss);
	return 0;
}