#include<cstdio>
#include<cstring>
using namespace std;
int rootx,rooty;
struct node
{
	int f,l,r,size;
	long long c;
}tr[410000];
void dfs(int x)
{
	if(x==0)return ;
	dfs(tr[x].l);
	dfs(tr[x].r);
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	tr[x].c=tr[tr[x].l].c+tr[tr[x].r].c+tr[x].size;
}
long long solve(int x,int y)
{
	if(x==0||y==0)return tr[x+y].c;
	if(tr[x].size<tr[y].size)return solve(x,tr[y].l)+tr[tr[y].r].c+tr[x].size+tr[y].size;
	else return tr[tr[x].l].c+solve(tr[x].r,y)+tr[x].size+tr[y].size;
}
void rotate(int x)
{
	int f=tr[x].f;
	if(rootx==tr[x].f)rootx=x;
	if(rooty==tr[x].f)rooty=x;
	if(x==tr[f].l)
	{
		tr[f].l=tr[x].r;
		tr[x].r=f;
		tr[x].f=tr[f].f;
		tr[f].f=x;
		if(tr[f].l!=0)tr[tr[f].l].f=f;
	}
	else
	{
		tr[f].r=tr[x].l;
		tr[x].l=f;
		tr[x].f=tr[f].f;
		tr[f].f=x;
		if(tr[f].r!=0)tr[tr[f].r].f=f;
	}
	tr[f].size=tr[tr[f].l].size+tr[tr[f].r].size+1;
	tr[f].c=tr[tr[f].l].c+tr[tr[f].r].c+tr[f].size;
	while(x!=0)
	{
		tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
		tr[x].c=tr[tr[x].l].c+tr[tr[x].r].c+tr[x].size;
		x=tr[x].f;
	}
}
bool b[410000];
int leng;
long long cc;
void dfs2(int x)
{
	if(x==0)return ;
	b[x]=true;
	dfs2(tr[x].r);
	leng++;
}
void rotate2(int x)
{
	int f=tr[x].f;
	if(rootx==tr[x].f)rootx=x;
	if(rooty==tr[x].f)rooty=x;
	if(x==tr[f].l)
	{
		if(b[f])b[x]=true,leng++;
		cc+=-tr[tr[x].l].size+tr[tr[f].r].size;
		tr[f].l=tr[x].r;
		tr[x].r=f;
		tr[x].f=tr[f].f;
		tr[f].f=x;
		if(tr[f].l!=0)tr[tr[f].l].f=f;
	}
	else
	{
		if(b[f])b[f]=false,leng--;
		cc+=-tr[tr[x].r].size+tr[tr[f].l].size;
		tr[f].r=tr[x].l;
		tr[x].l=f;
		tr[x].f=tr[f].f;
		tr[f].f=x;
		if(tr[f].r!=0)tr[tr[f].r].f=f;
	}
	tr[f].size=tr[tr[f].l].size+tr[tr[f].r].size+1;
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
}
int main()
{
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&tr[i].l,&tr[i].r);
		if(tr[i].l!=0)tr[tr[i].l].f=i;
		if(tr[i].r!=0)tr[tr[i].r].f=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&tr[n+i].l,&tr[n+i].r);
		if(tr[n+i].l!=0)tr[n+i].l+=n;
		if(tr[n+i].r!=0)tr[n+i].r+=n;
		if(tr[n+i].l!=0)tr[tr[n+i].l].f=n+i;
		if(tr[n+i].r!=0)tr[tr[n+i].r].f=n+i;
	}
	for(int i=1;i<=n;i++)if(tr[i].f==0)rootx=i;
	for(int i=1;i<=m;i++)if(tr[n+i].f==0)rooty=n+i;
	dfs(rootx);dfs(rooty);
	if(m==1)
	{
		memset(b,false,sizeof(b));
		leng=0;
		dfs2(rootx);
		cc=tr[rootx].c;
		printf("%lld\n",cc+leng+1);
		int q;scanf("%d",&q);
		while(q--)
		{
			int opt,x;scanf("%d%d",&opt,&x);
			rotate2(x);
			printf("%lld\n",cc+leng+1);
		}
	}
	printf("%lld\n",solve(rootx,rooty));
	int q;scanf("%d",&q);
	while(q--)
	{
		int opt,x;scanf("%d%d",&opt,&x);
		if(opt==2)x+=n;
		rotate(x);
		printf("%lld\n",solve(rootx,rooty));
	}
	return 0;
}