#include<cstdio>
#include<cstring>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
struct node
{
	int x,y,next;
}a[4010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int z,dfn[1010000],low[1010000];
int sta[1010000],top;
int f[1010000],g[1010000];
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++z;sta[++top]=x;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(dfn[y]==0)
			{
				dfs(y,x);
				if(low[y]<low[x])low[x]=low[y];
				else
				{
					int i,cnt=0;
					do
					{
						i=sta[top--];
						g[++cnt]=i;
					}while(i!=y);
					for(i=1;i<=cnt;i++)f[g[i]]+=cnt+1;
					f[x]+=cnt;
				}
			}
			else low[y]=mymin(low[y],dfn[x]);
		}
	}
}
char s[1100][1100];
long long ss=0;
void dfs(int x,int y,int d)
{}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	memset(s,'#',sizeof(s));
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	len=0;memset(last,0,sizeof(last));
	int stx,sty;
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
					if(s[x][y]!='#')dfs((i-1)*m+j,(x-1)*m+y);
				}
			}
		}
	}
	memset(dfn,0,sizeof(dfn));
	memset(f,0,sizeof(f));
	z=top=0;
	dfs((stx-1)*m+sty,0);
	f[(stx-1)*m+sty]++;
	return 0;
}