#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int c[110000];
int z,in[110000],out[110000];
int block,blk[110000];
int cnt,ce[110000];
int sta[110000],top;
vector<int> pos[110000];
void dfs(int x,int fa)
{
	in[x]=++z;
	int t=top;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			if(block<=top-t)
			{
				ce[++cnt]=x;
				pos[x].push_back(cnt);
				while(top>t)blk[sta[top--]]=cnt;
			}
		}
	}
	sta[++top]=x;
	out[x]=z;
}
long long ss=0;
int ctt[130000];
void dfs1(int x,int fa){}
void dfs2(int x,int fa)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(blk[y]==blk[x]&&y!=fa)
		{}
	}
}
vector<int> e[110000];
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	block=1423;
	blk[1]=1;cnt=1;
	z=top=0;dfs(1,0);
	if(top>0)
	{
		ce[++cnt]=1;
		pos[1].push_back(cnt);
		while(top>0)blk[sta[top--]]=cnt;
	}
	for(int i=2;i<=cnt;i++)e[blk[ce[i]]].push_back(i);
	for(int i=1;i<=n;i++)
	{
		for(int k=last[i];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(blk[y]!=blk[i])
			{
				dfs()
			}
		}
	}
	return 0;
}