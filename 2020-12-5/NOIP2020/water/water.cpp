#include<cstdio>
#include<cstring>
using namespace std;
long long gcd(long long x,long long y){return y==0?x:gcd(y,x%y);}
struct fenshu
{
	long long a,b;
}f[110000];
inline fenshu operator+(fenshu x,fenshu y)
{
	long long t=gcd(x.b,y.b);
	long long tx=y.b/t,ty=x.b/t;
	x.a*=tx;x.b*=tx;
	y.a*=ty;y.b*=ty;
	fenshu z;z.a=x.a+y.a;z.b=x.b;
	t=gcd(z.a,z.b);
	z.a/=t;z.b/=t;
	return z;
}
long long d[110000];
int p[110000],bian[110000][11];
int list[110000];
int main()
{
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&d[i]);
		for(int j=1;j<=d[i];j++)
		{
			scanf("%d",&bian[i][j]);
			p[bian[i][j]]++;
		}
	}
	int head=1,tail=1;
	for(int i=1;i<=m;i++)
	{
		list[tail++]=i;
		f[i]=(fenshu){1,1};
	}
	for(int i=m+1;i<=n;i++)f[i]=(fenshu){0,1};
	while(head<tail)
	{
		int x=list[head];
		if(d[x]==0){head++;continue;}
		f[x].b=f[x].b*d[x];
		for(int j=1;j<=d[x];j++)
		{
			int y=bian[x][j];
			f[y]=f[y]+f[x];
			p[y]--;
			if(p[y]==0)list[tail++]=y;
		}
		head++;
	}
	for(int i=1;i<=n;i++)
	{
		if(d[i]==0)
		{
			long long t=gcd(f[i].a,f[i].b);
			f[i].a/=t;f[i].b/=t;
			printf("%lld %lld\n",f[i].a,f[i].b);
		}
	}
	return 0;
}
