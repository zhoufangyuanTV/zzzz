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
struct node
{
	int x,y,c,next;
	bool ring;
}a[2010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
	a[len].ring=false;
}
int z,dfn[510000],low[510000];
int sta[510000],top;bool v[510000];
inline int mymin(int x,int y){return x<y?x:y;}
bool bk;
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++z;
	sta[++top]=x;v[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(dfn[y]==0)
			{
				dfs(y,x);
				if(!bk)return ;
				if(low[y]<dfn[x])
				{
					if(low[x]<dfn[x]){bk=false;return ;}
					low[x]=mymin(low[x],low[y]);
				}
				if(low[y]<=dfn[x])a[k].ring=a[(k^1)+((k&1?1:-1)<<1)].ring=true;
			}
			else if(v[y])
			{
				if(dfn[y]<dfn[x]&&low[x]<dfn[x]){bk=false;return ;}
				low[x]=mymin(low[x],dfn[y]);
				a[k].ring=a[(k^1)+((k&1?1:-1)<<1)].ring=true;
			}
		}
	}
	if(dfn[x]==low[x])
	{
		int k;
		do
		{
			k=sta[top--];
			v[k]=false;
		}while(k!=x);
	}
}
long long f[510000];
int main()
{
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	f[0]=1;f[1]=1;
	for(int i=2;i<=500000;i++)f[i]=(f[i-1]+f[i-2]*(i-1))%998244353;
	int t;read(t);
	while(t--)
	{
		int n,m;read(n);read(m);
		len=0;memset(last,0,sizeof(last));
		for(int i=1;i<=m;i++)
		{
			int x,y;read(x);read(y);
			ins(x,y);ins(y,x);
		}
		z=0;
		memset(dfn,0,sizeof(dfn));
		bk=true;
		dfs(1,0);
		if(!bk){printf("0\n");continue;}
		long long ss=1;
		for(int i=1;i<=n;i++)
		{
			int s=0;
			for(int k=last[i];k>0;k=a[k].next)s+=!a[k].ring;
			ss=ss*f[s]%998244353;
		}
		printf("%lld\n",ss);
	}
	return 0;
}