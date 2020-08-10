#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
int root[81000],T;
struct treap
{
	int l,r,c,key,size;
	int t;
}tr[10010000];queue<int> Q;
int v[81000];
inline void update(int x){tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;}
void split(int now,int c,int &x,int &y)
{
	if(now==0)x=y=0;
	else
	{
		if(T!=tr[now].t)
		{
			int new_node=Q.front();Q.pop();
			tr[new_node]=tr[now];
			tr[new_node].t=T;
			now=new_node;
		}
		if(c<tr[now].key)
		{
			y=now;split(tr[now].l,c,x,tr[y].l);
		}
		else
		{
			x=now;split(tr[now].r,c,tr[x].r,y);
		}
		update(now);
	}
}
int merge(int x,int y)
{
	if(x==0||y==0)return x+y;
	if(tr[x].c<tr[y].c)
	{
		if(T!=tr[x].t)
		{
			int new_node=Q.front();Q.pop();
			tr[new_node]=tr[x];
			tr[new_node].t=T;
			x=new_node;
		}
		tr[x].r=merge(tr[x].r,y);
		update(x);
		return x;
	}
	else
	{
		if(T!=tr[y].t)
		{
			int new_node=Q.front();Q.pop();
			tr[new_node]=tr[y];
			tr[new_node].t=T;
			y=new_node;
		}
		tr[y].l=merge(x,tr[y].l);
		update(y);
		return y;
	}
}
int rk(int x,int c)
{
	if(x==0)return 0;
	if(c<tr[x].key)return rk(tr[x].l,c);
	else return tr[tr[x].l].size+1+rk(tr[x].r,c);
}
void clean(int x)
{
	if(x==0)return ;
	if(T!=tr[x].t)return ;
	clean(tr[x].l);
	clean(tr[x].r);
	Q.push(x);
}
struct node
{
	int x,y,next;
}a[161000];int len,last[81000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fa[81000][17],dep[81000],tot[81000];
void dfs(int x)
{
	for(int i=1;1<<i<dep[x];i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0])
		{
			T=y;
			int a,b;
			split(root[x],v[y],a,b);
			int new_node=Q.front();Q.pop();
			tr[new_node].t=T;
			tr[new_node].size=1;
			tr[new_node].c=rand();
			tr[new_node].key=v[y];
			tr[new_node].l=tr[new_node].r=0;
			root[y]=merge(merge(a,new_node),b);
			fa[y][0]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			tot[x]+=tot[y];
		}
	}
}
void cl(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x][0])cl(y);
	}
	T=x;clean(root[x]);
}
char s[11];
int main()
{
	freopen("forest11.in","r",stdin);
	freopen("forest.out","w",stdout);
	int n,m,t;scanf("%*d%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	root[0]=0;
	for(int i=1;i<=10000000;i++)Q.push(i);
	memset(fa,0,sizeof(fa));
	for(int i=1;i<=n;i++)
	{
		if(fa[i][0]==0)
		{
			T=i;
			int new_node=Q.front();Q.pop();
			tr[new_node].t=T;
			tr[new_node].size=1;
			tr[new_node].c=rand();
			tr[new_node].key=v[i];
			tr[new_node].l=tr[new_node].r=0;
			root[i]=new_node;
			dep[i]=1;
			dfs(i);
		}
	}
	int lastans=0;
	while(t--)
	{
		int x,y;scanf("%s%d%d",s+1,&x,&y);x^=lastans;y^=lastans;
		if(s[1]=='Q')
		{
			int k;scanf("%d",&k);k^=lastans;
			if(x<0||y<0)printf("!\n");
			if(x>80000||y>80000)printf("! %d %d\n",x,y);
			if(dep[x]<dep[y])x^=y^=x^=y;
			int fx=x,fy=y;
			for(int i=16;i>=0;i--)if(1<<i<=dep[fx]-dep[y])fx=fa[fx][i];
			if(fx!=y)
			{
				for(int i=16;i>=0;i--)
				{
					if(1<<i<dep[fx]&&fa[fx][i]!=fa[fy][i])
					{
						fx=fa[fx][i];fy=fa[fy][i];
					}
				}
				fx=fa[fx][0];
			}
			int l=1,r=1000000000;
			while(l<r)
			{
				int mid=(l+r)/2;
				if(k<=rk(root[x],mid)+rk(root[y],mid)-rk(root[fx],mid)-rk(root[fa[fx][0]],mid))r=mid;
				else l=mid+1;
			}
			printf("%d\n",lastans=r);
		}
		else
		{
			int rtx=x,rty=y;
			for(int i=16;i>=0;i--)if(1<<i<dep[rtx])rtx=fa[rtx][i];
			for(int i=16;i>=0;i--)if(1<<i<dep[rty])rty=fa[rty][i];
			if(tot[rtx]<tot[rty])x^=y^=x^=y,rtx^=rty^=rtx^=rty;
			tot[rtx]+=tot[rty];
			cl(rty);
			ins(x,y);ins(y,x);
			T=y;
			int a,b;
			split(root[x],v[y],a,b);
			int new_node=Q.front();Q.pop();
			tr[new_node].t=T;
			tr[new_node].size=1;
			tr[new_node].c=rand();
			tr[new_node].key=v[y];
			tr[new_node].l=tr[new_node].r=0;
			root[y]=merge(merge(a,new_node),b);
			fa[y][0]=x;dep[y]=dep[x]+1;dfs(y);
		}
	}
	return 0;
}