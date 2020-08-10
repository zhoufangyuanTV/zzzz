#include<cstdio>
#include<cstring>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
struct node
{
	int x,y,c,next;
}a[11000];int len,last[5010];
inline void ins(int x,int y,int c)
{
	len++;a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long f[5010][2],g[5010];
inline long long mymin(long long x,long long y){return x<y?x:y;}
inline long long mymax(long long x,long long y){return x>y?x:y;}
void treedp(int x,int c)
{
	bool t0=true,to=true;
	long long t1=1,t2=1;
	long long pj=0,tg=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		treedp(y,a[k].c);
		if(c==a[k].c)
		{
			if(g[y]<f[y][0])t0=false;
			if(f[y][1]==g[y])t1=0;
			pj+=g[y];
		}
		else
		{
			if(g[y]<f[y][0])to=false;
			if(f[y][1]==g[y])t2=0;
			tg+=g[y];
		}
	}
	f[x][0]=pj+tg+mymax(t0?0:t1,to?0:t2);
	if(t1==1&&t2==1&&t0&&to)f[x][0]++;
	f[x][1]=pj+tg+mymax(t1,to?0:t2);
	if(to)g[x]=pj+tg;
	else g[x]=pj+tg+t2;
}
int n,m;
char map[110][110];
void dfs(int x,int y)
{
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(1<=xx&&xx<=n&&1<=yy&&yy<=m&&map[xx][yy]=='.')
		{
			map[xx][yy]='#';
			ins((x-1)*m+y,(xx-1)*m+yy,i&1);
			dfs(xx,yy);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",map[i]+1);
	len=0;memset(last,0,sizeof(last));
	int rtx,rty;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]=='.')
			{
				map[i][j]='#';
				rtx=i;rty=j;
				dfs(i,j);
				treedp((i-1)*m+j,0);
				printf("%d\n",mymin(f[(i-1)*m+j][0],f[(i-1)*m+j][1]));
				return 0;
			}
		}
	}
	printf("0\n");
	return 0;
}