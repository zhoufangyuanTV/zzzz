#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[11000];int len,last[5100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int m,c[5100];
long long f[5100][5100];
void dfs(int x,int fa)
{
	for(int i=m;i>=c[x];i--)f[x][i]=f[x][i-c[x]];
	for(int i=0;i<c[x];i++)f[x][i]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			for(int i=0;i<=m;i++)f[y][i]=f[x][i];
			dfs(y,x);
			for(int i=0;i<=m;i++)f[x][i]=(f[x][i]+f[y][i])*499122177%998244353;
		}
	}
}
int main()
{
	freopen("luge.in","r",stdin);
	freopen("luge.out","w",stdout);
	int n;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	f[1][0]=1;
	dfs(1,0);
	printf("%lld\n",f[1][m]);
	return 0;
}