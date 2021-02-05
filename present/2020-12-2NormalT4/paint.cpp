#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
int n,m,block;
int f[210000],siz[210000],col[210000];
int findf(int x){return f[x]==x?x:f[x]=findf(f[x]);}
void dfs(int x,int y,int zx)
{
	f[(x-1)*m+y]=zx;
	siz[zx]++;
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||yy<1||xx>n||yy>m)continue;
		if(col[(xx-1)*m+yy]==col[(x-1)*m+y])dfs(xx,yy,zx);
	}
}
int main()
{
	freopen("paint","r",stdin);
	freopen("paint","w",stdout);
	scanf("%d%d",&n,&m);
	block=sqrt(n*m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)scanf("%d",&col[(i-1)*m+j]);
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(f[(i-1)*m+j]==0)
			{
				siz[(i-1)*m+j]=0;
				dfs(i,j,(i-1)*m+j);
			}
		}
	}
	while(m--)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		int ff=findf((x-1)*m+y);
		col[ff]=c;
	}
	return 0;
}