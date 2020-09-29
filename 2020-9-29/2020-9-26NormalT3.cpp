#include<cstdio>
#include<cstring>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
struct node{int x,y,next;};
struct graph
{
	node a[4010000];int len,last[2010000];
	inline void ins(int x,int y)
	{
		len++;a[len].x=x;a[len].y=y;
		a[len].next=last[x];last[x]=len;
	}
}Y,F;
int z,dfn[1010000],low[1010000];
int sta[1010000],top;
int cnt;
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++z;sta[++top]=x;
	for(int k=Y.last[x];k>0;k=Y.a[k].next)
	{
		int y=Y.a[k].y;
		if(y!=fa)
		{
			if(dfn[y]==0)
			{
				dfs(y,x);
				if(dfn[x]<=low[y])
				{
					cnt++;int i;
					do
					{
						i=sta[top--];
						F.ins(cnt,i);
						F.ins(i,cnt);
					}while(i!=y);
					F.ins(cnt,x);
					F.ins(x,cnt);
				}
				else low[x]=mymin(low[x],low[y]);
			}
			else low[x]=mymin(low[x],dfn[y]);
		}
	}
}
int n,m,stx,sty,fa[2010000],tot[2010000];
void dfs(int x)
{
	tot[x]=x<=n*m&&x!=(stx-1)*m+sty;
	for(int k=F.last[x];k>0;k=F.a[k].next)
	{
		int y=F.a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dfs(y);
			tot[x]+=tot[y];
		}
	}
}
bool f[1100][1100][4];
char s[1100][1100];
void dfs(int x,int y,int d)
{
	if(f[x][y][d])return ;
	f[x][y][d]=true;
	int xx=x+dx[d],yy=y+dy[d];
	int xxx=xx+dx[d],yyy=yy+dy[d];
	if(s[xxx][yyy]=='#')return ;
	for(int dd=0;dd<4;dd++)
	{
		int i=xx+dx[dd],j=yy+dy[dd];
		if(s[i][j]!='#')
		{
			if(fa[(i-1)*m+j]==fa[(xxx-1)*m+yyy]||fa[fa[(i-1)*m+j]]==(xxx-1)*m+yyy||(i-1)*m+j==fa[fa[(xxx-1)*m+yyy]])dfs(xx,yy,dd);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)s[i][0]=s[i][m+1]='#';
	for(int i=1;i<=m;i++)s[0][i]=s[n+1][i]='#';
	Y.len=0;memset(Y.last,0,sizeof(Y.last));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]!='#')
			{
				if(s[i][j]=='X')stx=i,sty=j;
				for(int d=0;d<4;d++)
				{
					int x=i+dx[d],y=j+dy[d];
					if(s[x][y]!='#')Y.ins((i-1)*m+j,(x-1)*m+y);
				}
			}
		}
	}
	F.len=0;memset(F.last,0,sizeof(F.last));
	memset(dfn,0,sizeof(dfn));
	z=top=0;cnt=n*m;
	dfs((stx-1)*m+sty,0);
	fa[(stx-1)*m+sty]=0;
	dfs((stx-1)*m+sty);
	int total=tot[(stx-1)*m+sty];
	memset(f,false,sizeof(f));
	for(int i=0;i<4;i++)if(s[stx+dx[i]][sty+dy[i]]!='#')dfs(stx,sty,i);
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i==stx&&j==sty)continue;
			for(int d=0;d<4;d++)
			{
				if(f[i][j][d])
				{
					int xx=i+dx[d],yy=j+dy[d];
					bool bk=true;
					for(int dd=0;dd<d;dd++)
					{
						if(f[i][j][dd])
						{
							int xxx=i+dx[dd],yyy=j+dy[dd];
							if(fa[(xx-1)*m+yy]==fa[(xxx-1)*m+yyy]||fa[fa[(xx-1)*m+yy]]==(xxx-1)*m+yyy||(xx-1)*m+yy==fa[fa[(xxx-1)*m+yyy]]){bk=false;break;}
						}
					}
					if(bk)
					{
						if(fa[fa[(xx-1)*m+yy]]==(i-1)*m+j)ss=ss+tot[fa[(xx-1)*m+yy]];
						else ss=ss+total-tot[(i-1)*m+j];
					}
				}
			}
		}
	}
	printf("%lld\n",ss);
	return 0;
}