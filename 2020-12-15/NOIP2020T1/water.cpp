#include<cstdio>
#include<cstring>
using namespace std;
struct fenshu
{
	long long a,b;
}f[110000];
inline void operator+=(fenshu &x,fenshu y)
{
	x.a+=y.a;
	x.b+=y.b;
	x.a+=x.b/1000000000000000000ll;
	x.b%=1000000000000000000ll;
}
inline void operator/=(fenshu &x,int y)
{
	x.b=(x.b+x.a%y*1000000000000000000ll)/y;
	x.a/=y;
}
inline int operator%(fenshu x,int y){return (x.a%y*1000000000000000000ll+x.b)%y;}
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
	for(int i=1;i<=m;i++)f[i]=(fenshu){36,279705600000000000ll};
	for(int i=m+1;i<=n;i++)f[i]=(fenshu){0,0};
	int head=1,tail=1;
	for(int i=1;i<=n;i++)if(p[i]==0)list[tail++]=i;
	while(head<tail)
	{
		int x=list[head];
		if(d[x]==0){head++;continue;}
		f[x]/=d[x];
		for(int j=1;j<=d[x];j++)
		{
			int y=bian[x][j];
			f[y]+=f[x];
			p[y]--;
			if(p[y]==0)list[tail++]=y;
		}
		head++;
	}
	for(int i=1;i<=n;i++)
	{
		if(d[i]==0)
		{
			fenshu one=(fenshu){36,279705600000000000ll};
			while(f[i]%2==0&&one%2==0)f[i]/=2,one/=2;
			while(f[i]%3==0&&one%3==0)f[i]/=3,one/=3;
			while(f[i]%5==0&&one%5==0)f[i]/=5,one/=5;
			if(f[i].a>0)printf("%lld%018lld ",f[i].a,f[i].b);
			else printf("%lld ",f[i].b);
			if(one.a>0)printf("%lld%018lld\n",one.a,one.b);
			else printf("%lld\n",one.b);
		}
	}
	return 0;
}