#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int p[10010000];
bool b[10010000];
int cnt[10010000];
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
long long jc[10010000],fjc[10010000];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int tt,opt[210];
long long f[10010000],g[210];
int main()
{
	freopen("restoration.in","r",stdin);
	freopen("restoration.out","w",stdout);
	int n,m;read(n);read(m);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	for(int i=1;i<=n;i++)read(p[i]);
	for(int i=1;i<=n;i++)
	{
		if(b[i]==false)
		{
			b[i]=true;
			int x=i,y=1;
			for(x=p[x];x!=i;x=p[x])b[x]=true,y++;
			cnt[y]++;
		}
	}
	long long ss=1;
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]>0)
		{
			tt=0;
			g[0]=1;
			for(int j=1;j<=m;j++)
			{
				if(gcd(i*j,m)==j)opt[++tt]=j;
				g[j]=g[j-1]*i%998244353;
			}
			f[0]=1;
			for(int j=1;j<=cnt[i];j++)
			{
				f[j]=0;
				for(int k=1;k<=tt;k++)
				{
					if(opt[k]>j)break;
					f[j]=(f[j]+f[j-opt[k]]*jc[j-1]%998244353*fjc[j-opt[k]]%998244353*g[opt[k]-1])%998244353;
				}
			}
			ss=ss*f[cnt[i]]%998244353;
		}
	}
	printf("%lld\n",ss);
	return 0;
}
