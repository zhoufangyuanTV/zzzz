#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
struct node
{
	int x,y,c,next;
}a[1100];int len,last[1100];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int fa[1100],g[1100];
long long d[1100];
bool leaf[1100];
void dfs(int x)
{
	g[x]=0;
	int gs=0;
	leaf[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			leaf[x]=false;
			d[y]=d[x]+a[k].c;
			dfs(y);
			if(g[x]<g[y])g[x]=g[y],gs=1;
			else if(g[x]==g[y])gs++;
		}
	}
	if(gs>1)g[x]++;
}
long long f[1100][11][1100];
inline long long mymin(long long x,long long y){return x<y?x:y;}
long long dfs(int x,int i,int j)
{
	if(leaf[x])return 0;
	if(i>g[x])i=g[x];
	if(f[x][i][j]!=-1)return f[x][i][j];
	long long s=0,sss=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			long long g,h=dfs(y,i,j),in,out;
			if(i>0)g=dfs(y,i-1,x);
			else g=0x3f3f3f3f3f3f3f3fll;
			in=mymin(a[k].c+g,j==0?0x3f3f3f3f3f3f3f3fll:d[y]-d[j]+h);
			out=mymin(a[k].c+g,a[k].c+h);
			sss=mymin(s+out,in+sss);
			s=s+in;
		}
	}
	return f[x][i][j]=mymin(s,sss);
}
int main()
{
	freopen("teleport.in","r",stdin);
	freopen("teleport.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	fa[1]=0;
	for(int i=2;i<=n;i++)
	{
		int c;scanf("%d%d",&fa[i],&c);
		ins(fa[i],i,c);
	}
	d[0]=d[1]=0;dfs(1);
	memset(f,-1,sizeof(f));
	for(int i=1;i<=m;i++)printf("%lld\n",dfs(1,i,0));
	return 0;
}