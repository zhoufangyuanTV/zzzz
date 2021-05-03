#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long dis[210000];
int n,fa[210000],dep[210000],son[210000],tot[210000];
void dfs(int x)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			dis[y]=dis[x]+a[k].c;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
int z,ys[210000],yss[210000],top[210000];
int out[210000];
void dfs(int x,int tp)
{
	ys[x]=++z;yss[z]=x;top[x]=tp;
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])dfs(y,y);
	}
	out[x]=z;
}
inline int kth(int x,int k)
{
	while(dep[x]-dep[top[x]]<k)
	{
		k-=dep[x]-dep[top[x]]+1;
		x=fa[top[x]];
	}
	return yss[ys[x]-k];
}
int block,blk[210000];
int val[210000],h[2100][2100];
int bt[210000],tag[210000];
long long cc[210000];
inline bool cmp(int x,int y){return ys[val[x]]<ys[val[y]];}
int U[2100],B;
void pushdown(int x)
{
	for(int i=(x-1)*block+1;i<=x*block&&i<=n;i++)
	{
		val[i]=kth(val[i],bt[x]-tag[i]);
		tag[i]=0;
	}
	bt[x]=0;
}
inline long long mymin(long long x,long long y){return x<y?x:y;}
void build(int x)
{
	B=0;
	for(int i=(x-1)*block+1;i<=x*block&&i<=n;i++)U[++B]=i;
	sort(U+1,U+B+1,cmp);
	h[x][0]=1;h[x][1]=U[1];cc[x]=dis[val[U[1]]];
	for(int i=2;i<=B;i++)
	{
		if(out[val[h[x][h[x][0]]]]<ys[val[U[i]]])
		{
			h[x][++h[x][0]]=U[i];
			cc[x]=mymin(cc[x],dis[val[U[i]]]);
		}
	}
}
void plus(int x)
{
	bt[x]++;
	B=0;
	for(int i=1;i<=h[x][0];i++)
	{
		val[h[x][i]]=fa[val[h[x][i]]];
		tag[h[x][i]]++;
		U[++B]=h[x][i];
	}
	sort(U+1,U+B+1,cmp);
	h[x][0]=1;h[x][1]=U[1];cc[x]=dis[val[U[1]]];
	for(int i=2;i<=B;i++)
	{
		if(out[val[h[x][h[x][0]]]]<ys[val[U[i]]])
		{
			h[x][++h[x][0]]=U[i];
			cc[x]=mymin(cc[x],dis[val[U[i]]]);
		}
	}
}
int main()
{
	freopen("tearssp.in","r",stdin);
	freopen("tearssp.out","w",stdout);
	int m,root;scanf("%d%d%d",&n,&m,&root);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	dis[root]=0;
	fa[root]=root;dep[root]=1;dfs(root);
	z=0;dfs(root,root);
	block=int(sqrt(n)*0.8+0.5);
	for(int i=1;i<=n;i++)blk[i]=(i-1)/block+1;
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	memset(bt,0,sizeof(bt));
	memset(tag,0,sizeof(tag));
	for(int i=1;i<=blk[n];i++)build(i);
	while(m--)
	{
		int t,l,r;scanf("%d%d%d",&t,&l,&r);
		if(t==1)
		{
			if(blk[l]==blk[r])
			{
				pushdown(blk[l]);
				for(int i=l;i<=r;i++)val[i]=fa[val[i]];
				build(blk[l]);
			}
			else
			{
				pushdown(blk[l]);pushdown(blk[r]);
				for(int i=l;i<=blk[l]*block;i++)val[i]=fa[val[i]];
				for(int i=(blk[r]-1)*block+1;i<=r;i++)val[i]=fa[val[i]];
				build(blk[l]);build(blk[r]);
				for(int i=blk[l]+1;i<blk[r];i++)plus(i);
			}
		}
		else
		{
			long long ss=0x3f3f3f3f3f3f3f3fll;
			if(blk[l]==blk[r])
			{
				pushdown(blk[l]);
				for(int i=l;i<=r;i++)ss=mymin(ss,dis[val[i]]);
			}
			else
			{
				pushdown(blk[l]);pushdown(blk[r]);
				for(int i=l;i<=blk[l]*block;i++)ss=mymin(ss,dis[val[i]]);
				for(int i=(blk[r]-1)*block+1;i<=r;i++)ss=mymin(ss,dis[val[i]]);
				for(int i=blk[l]+1;i<blk[r];i++)ss=mymin(ss,cc[i]);
			}
			printf("%lld\n",ss);
		}
	}
	return 0;
}
