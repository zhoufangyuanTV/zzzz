#include<cstdio>
#include<cstring>
using namespace std;
int root;
struct treap
{
	int l,r,c,size;
	int cc,lc,rc,mc;
}tr[110000];int len;
inline int mymin(int x,int y){return x<y?x:y;}
inline void update(int x)
{
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	tr[x].cc=tr[tr[x].l].lc+tr[tr[x].r].rc+1;
	tr[x].lc=mymin(tr[tr[x].l].cc+tr[tr[x].r].lc,tr[tr[x].l].lc+tr[tr[x].r].mc+1);
	tr[x].rc=mymin(tr[tr[x].l].rc+tr[tr[x].r].cc,tr[tr[x].l].mc+tr[tr[x].r].rc+1);
	tr[x].mc=mymin(tr[tr[x].l].rc+tr[tr[x].r].lc,tr[tr[x].l].mc+tr[tr[x].r].mc+1);
}
void split(int now,int k,int &x,int &y)
{
	if(now==0)x=y=0;
	else
	{
		if(k<=tr[tr[now].l].size)
		{
			y=now;split(tr[now].l,k,x,tr[y].l);
		}
		else
		{
			x=now;split(tr[now].r,k-tr[tr[now].l].size-1,tr[x].r,y);
		}
		update(now);
	}
}
int merge(int x,int y)
{
	if(x==0||y==0)return x+y;
	if(tr[x].c>tr[y].c)
	{
		tr[x].r=merge(tr[x].r,y);
		update(x);
		return x;
	}
	else
	{
		tr[y].l=merge(x,tr[y].l);
		update(y);
		return y;
	}
}
inline int new_node(int c)
{
	len++;
	tr[len].c=c;
	tr[len].l=tr[len].r=0;
	tr[len].cc=tr[len].size=1;
	tr[len].lc=tr[len].rc=tr[len].mc=0;
	return len;
}
int main()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	int n,q;scanf("%d%d",&n,&q);
	root=len=0;
	for(int i=1;i<=n;i++)
	{
		int p;scanf("%d",&p);
		root=merge(root,new_node(p));
	}
	printf("%d\n",tr[root].cc);
	for(int i=1;i<=q;i++)
	{
		int x;scanf("%d",&x);
		int a,b,c,d;
		split(root,x,a,c);
		split(a,x-1,a,b);
		split(c,1,c,d);
		root=merge(merge(a,c),merge(b,d));
		printf("%d\n",tr[root].cc);
	}
	return 0;
}