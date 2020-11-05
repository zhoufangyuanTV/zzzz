#include<cstdio>
#include<cstring>
using namespace std;
const int dx[8]={-1,-1,0,1,1,1,0,-1};
const int dy[8]={0,1,1,1,0,-1,-1,-1};
char a[2100][2100];
struct node
{
	int x,y,d;
}list[4010000];
int upx,upy,downx,downy,tdx,tdy;
bool b[2100][2100];
int bfs(int stx,int sty,int edx,int edy)
{
	int head=1,tail=2;
	b[stx][sty]=false;
	list[1]=(node){stx,sty,0};
	while(head<tail)
	{
		int x=list[head].x,y=list[head].y,d=list[head].d;
		if(x==edx&&y==edy)return d;
		for(int i=0;i<8;i++)
		{
			int xx=list[head].x+dx[i],yy=list[head].y+dy[i];
			if(b[xx][yy]==true)
			{
				b[xx][yy]=false;
				if(xx==edx&&yy==edy)return d+1;
				list[tail++]=(node){xx,yy,d+1};
			}
		}
		head++;
	}
}
int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	upx=n+1;downx=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='X')
			{
				if(i<upx)upx=i,upy=j;
				if(i>downx)downx=i,downy=j;
			}
			if(a[i][j]=='*')tdx=i,tdy=j;
		}
	}
	upx--;downx++;
	for(int i=0;i<=m+1;i++)b[0][i]=b[n+1][i]=false;
	for(int i=0;i<=n+1;i++)b[i][0]=b[i][m+1]=false;
	if(tdx>upx+1)
	{
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='X')b[i][j]=false;
				else b[i][j]=true;
			}
		}
		for(int i=1;i<=upx+1;i++)b[i][upy+1]=false;
		ss=ss+bfs(tdx,tdy,upx,upy);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='X')b[i][j]=false;
				else b[i][j]=true;
			}
		}
		for(int i=1;i<=upx+1;i++)b[i][upy-1]=false;
		ss=ss+bfs(tdx,tdy,upx,upy);
		printf("%d\n",ss);
	}
	else if(tdx<downx-1)
	{
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='X')b[i][j]=false;
				else b[i][j]=true;
			}
		}
		for(int i=downx-1;i<=n;i++)b[i][downy-1]=false;
		ss=ss+bfs(tdx,tdy,downx,downy);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='X')b[i][j]=false;
				else b[i][j]=true;
			}
		}
		for(int i=downx-1;i<=n;i++)b[i][downy+1]=false;
		ss=ss+bfs(tdx,tdy,downx,downy);
		printf("%d\n",ss);
	}
	else
	{
		int l=m+1,r=0;
		for(int i=1;i<=m;i++)
		{
			if(a[tdx][i]=='X')
			{
				if(l==m+1)l=i;
				r=i;
			}
		}
		if(tdy<l)printf("%d\n",(r-tdy+1)*2);
		else printf("%d\n",(tdy-l+1)*2);
	}
	return 0;
}
