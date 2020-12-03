#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
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
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool b[510000];
int dis[510000],dep[510000];
inline int mymin(int x,int y){return x<y?x:y;}
void dfs1(int x,int fa)
{
	dis[x]=b[x]?0:0x3f3f3f3f;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dep[y]=dep[x]+1;
			dfs1(y,x);
			dis[x]=mymin(dis[x],dis[y]+1);
		}
	}
}
void dfs2(int x,int fa,int d)
{
	dis[x]=mymin(dis[x],d+1);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs2(y,x,dis[x]);
	}
}
int top[510000];
void dfs3(int x,int fa,int tp)
{
	top[x]=tp;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(dis[y]==dis[x]-1)dfs3(y,x,tp);
			else dfs3(y,x,y);
		}
	}
}
void dfs4(int x)
{
	if(b[x]==false)return ;
	b[x]=false;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(dis[y]==dis[x]-1)dfs4(y);
	}
}
int O[510000];
inline bool cmp(int x,int y){return dep[x]>dep[y];}
int Ans[510000];
int main()
{
	freopen("shepherd.in","r",stdin);
	freopen("shepherd.out","w",stdout);
	int n,m;read(n);read(m);
	len++;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	memset(b,false,sizeof(b));
	for(int i=1;i<=m;i++)
	{
		read(O[i]);
		b[O[i]]=true;
	}
	dep[1]=1;
	dfs1(1,0);
	dfs2(1,0,0x3f3f3f3f);
	dfs3(1,0,1);
	sort(O+1,O+m+1,cmp);
	int ss=0;
	memset(b,true,sizeof(b));
	for(int i=1;i<=m;i++)
	{
		if(b[O[i]])
		{
			Ans[++ss]=top[O[i]];
			dfs4(top[O[i]]);
		}
	}
	printf("%d\n",ss);
	for(int i=1;i<ss;i++)printf("%d ",Ans[i]);
	printf("%d\n",Ans[ss]);
	return 0;
}