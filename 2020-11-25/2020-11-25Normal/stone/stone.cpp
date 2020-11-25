#include<cstdio>
#include<cstring>
#include<vector>
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
	int x,y,next;
}a[610000];int len,last[310000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fg[3100][3100];
vector<int> g[310000];
void dfs(int st,int x,int fa,int d)
{
	for(int i=0;i<g[st].size();i++)
	{
		if(fg[x][g[st][i]]<d)fg[x][g[st][i]]=d;
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(st,y,x,d+1);
	}
}
int main()
{
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	int n;read(n);
	len=0;memset(last,0,sizeof(last));
	for(int i=2;i<=n;i++)
	{
		int f;read(f);
		ins(f,i);ins(i,f);
	}
	int q;read(q);
	for(int i=1;i<=q;i++)
	{
		int k;read(k);
		while(k--)
		{
			int p;read(p);
			g[p].push_back(i);
		}
	}
	memset(fg,0,sizeof(fg));
	for(int i=1;i<=n;i++)if(g[i].size()>0)dfs(i,i,0,0);
	for(int i=1;i<=n;i++)
	{
		int ss=0x3f3f3f3f;
		for(int j=1;j<=q;j++)if(fg[i][j]<ss)ss=fg[i][j];
		printf("%d\n",ss);
	}
	return 0;
}