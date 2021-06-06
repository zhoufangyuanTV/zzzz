#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n,m,a[610][610],h[610][610],l[610][610];
int e[610][610][5];
void dfs(int x,int y,int c)
{
	if(x==n+1)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<n;j++)printf("%d ",a[i][j]);
			printf("%d\n",a[i][n]);
		}
		exit(0);
	}
	else if(y==n+1)dfs(x+1,1,x);
	else
	{
		a[x][y]=-1;
		for(int i=c+1;i<=m;i++)
		{
			if(i==e[x][y][0]||i==e[x][y][1]||i==e[x][y][2]||i==e[x][y][3]||i==e[x][y][4])continue;
			if(h[x][i]!=-1&&l[y][i]!=-1)continue;
			if(h[x][i]!=-1)
			{
				int yy=h[x][i];
				bool bk=false;
				for(int j=1;j<=m;j++)
				{
					if(h[x][j]!=-1||l[yy][j]!=-1||j==e[x][yy][0]||j==e[x][yy][1]||j==e[x][yy][2]||j==e[x][yy][3]||j==e[x][yy][4])continue;
					bk=true;
					h[x][i]=-1;
					l[yy][i]=-1;
					h[x][j]=yy;
					l[yy][j]=x;
					a[x][yy]=j;
					break;
				}
				if(bk)
				{
					a[x][y]=i;
					h[x][i]=y;
					l[y][i]=x;
					dfs(x,y+1,i);
				}
			}
			else if(l[y][i]!=-1)
			{
				int xx=l[y][i];
				bool bk=false;
				for(int j=1;j<=m;j++)
				{
					if(h[xx][j]!=-1||l[y][j]!=-1||j==e[xx][y][0]||j==e[xx][y][1]||j==e[xx][y][2]||j==e[xx][y][3]||j==e[xx][y][4])continue;
					bk=true;
					h[xx][i]=-1;
					l[y][i]=-1;
					h[x][j]=y;
					l[y][j]=xx;
					a[xx][y]=j;
					break;
				}
				if(bk)
				{
					a[x][y]=i;
					h[x][i]=y;
					l[y][i]=x;
					dfs(x,y+1,i);
				}
			}
			else
			{
				a[x][y]=i;
				h[x][i]=y;
				l[y][i]=x;
				dfs(x,y+1,i);
			}
			if(a[x][y]!=-1)
			{
				h[x][a[x][y]]=-1;
				l[y][a[x][y]]=-1;
				a[x][y]=-1;
			}
		}
		for(int i=1;i<=c;i++)
		{
			if(i==e[x][y][0]||i==e[x][y][1]||i==e[x][y][2]||i==e[x][y][3]||i==e[x][y][4])continue;
			if(h[x][i]!=-1/**/||/*&&*/l[y][i]!=-1)continue;
			if(h[x][i]!=-1)
			{
				int yy=h[x][i];
				bool bk=false;
				for(int j=1;j<=m;j++)
				{
					if(h[x][j]!=-1||l[yy][j]!=-1||j==e[x][yy][0]||j==e[x][yy][1]||j==e[x][yy][2]||j==e[x][yy][3]||j==e[x][yy][4])continue;
					bk=true;
					h[x][i]=-1;
					l[yy][i]=-1;
					h[x][j]=yy;
					l[yy][j]=x;
					a[x][yy]=j;
					break;
				}
				if(bk)
				{
					a[x][y]=i;
					h[x][i]=y;
					l[y][i]=x;
					dfs(x,y+1,i);
				}
			}
			else if(l[y][i]!=-1)
			{
				int xx=l[y][i];
				bool bk=false;
				for(int j=1;j<=m;j++)
				{
					if(h[xx][j]!=-1||l[y][j]!=-1||j==e[xx][y][0]||j==e[xx][y][1]||j==e[xx][y][2]||j==e[xx][y][3]||j==e[xx][y][4])continue;
					bk=true;
					h[xx][i]=-1;
					l[y][i]=-1;
					h[x][j]=y;
					l[y][j]=xx;
					a[xx][y]=j;
					break;
				}
				if(bk)
				{
					a[x][y]=i;
					h[x][i]=y;
					l[y][i]=x;
					dfs(x,y+1,i);
				}
			}
			else
			{
				a[x][y]=i;
				h[x][i]=y;
				l[y][i]=x;
				dfs(x,y+1,i);
			}
			if(a[x][y]!=-1)
			{
				h[x][a[x][y]]=-1;
				l[y][a[x][y]]=-1;
				a[x][y]=-1;
			}
		}
	}
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d%d",&n,&m);
	memset(e,-1,sizeof(e));
	memset(h,-1,sizeof(h));
	memset(l,-1,sizeof(l));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=0;k<m-n;k++)scanf("%d",&e[i][j][k]);
		}
	}
	dfs(1,1,0);
	return 0;
}