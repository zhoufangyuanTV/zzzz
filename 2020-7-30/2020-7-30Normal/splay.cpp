#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct QwQ
{
	int opt,val;
}Q[110000];
int a[110000];
int root;
struct ky{int fa,dep,lc,rc;};
struct treap
{
	int l,r,c;
	ky key;
	int bk;
}tr[110000];
inline void pushdown(int x)
{
	if(tr[x].l>0)tr[tr[x].l].key.dep+=tr[x].bk;
	if(tr[x].l>0)tr[tr[x].l].bk+=tr[x].bk;
	if(tr[x].r>0)tr[tr[x].r].key.dep+=tr[x].bk;
	if(tr[x].r>0)tr[tr[x].r].bk+=tr[x].bk;
	tr[x].bk=0;
}
void split(int now,int c,int &x,int &y)
{
	if(now==0)x=y=0;
	else
	{
		pushdown(now);
		if(c<now)
		{
			y=now;split(tr[now].l,c,x,tr[y].l);
		}
		else
		{
			x=now;split(tr[now].r,c,tr[x].r,y);
		}
	}
}
int merge(int x,int y)
{
	if(x==0||y==0)return x+y;
	if(tr[x].c<tr[y].c)
	{
		pushdown(x);
		tr[x].r=merge(tr[x].r,y);
		return x;
	}
	else
	{
		pushdown(y);
		tr[y].l=merge(x,tr[y].l);
		return y;
	}
}
int main()
{
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	int n;scanf("%d",&n);int vc=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&Q[i].opt);
		if(Q[i].opt==1)
		{
			scanf("%d",&Q[i].val);
			vc++;a[vc]=Q[i].val;
		}
	}
	sort(a+1,a+vc+1);
	for(int i=1;i<=n;i++)
	{
		if(Q[i].opt==1)
		{
			Q[i].val=lower_bound(a+1,a+vc+1,Q[i].val)-a;
		}
	}
	for(int i=1;i<=vc;i++)
	{
		tr[i].l=tr[i].r=tr[i].bk=0;
		tr[i].c=rand();
	}
	root=0;int rbt=0;
	for(int i=1;i<=n;i++)
	{
		if(Q[i].opt==1)
		{
			int c=Q[i].val;
			if(root==0)rbt=c;
			int x,y;split(root,c,x,y);
			int xx=x;
			while(tr[xx].r>0)pushdown(xx),xx=tr[xx].r;
			int xdep=tr[xx].key.dep;
			int yy=y;
			while(tr[yy].l>0)pushdown(yy),yy=tr[yy].l;
			int ydep=tr[yy].key.dep;
			if(xdep>ydep)
			{
				tr[xx].key.rc=c;
				tr[c].key=(ky){xx,xdep+1,0,0};
			}
			else
			{
				tr[yy].key.lc=c;
				tr[c].key=(ky){yy,ydep+1,0,0};
			}
			root=merge(merge(x,c),y);
			printf("%d\n",tr[c].key.dep);
		}
		else if(Q[i].opt==2)
		{
			int rt=root;
			while(tr[rt].l>0)pushdown(rt),rt=tr[rt].l;
			int fa=tr[rt].key.fa,rc=tr[rt].key.rc;
			if(fa==0)
			{
				printf("1\n");
				continue;
			}
			int x,y;split(root,fa-1,x,y);
			if(y>0)tr[y].key.dep+=1;
			if(y>0)tr[y].bk+=1;
			printf("%d\n",tr[rt].key.dep);
			tr[rt].key.fa=0;tr[rt].key.rc=rbt;tr[rt].key.dep=1;
			tr[rbt].key.fa=rt;rbt=rt;
			tr[fa].key.lc=rc;tr[rc].key.fa=fa;
			root=merge(x,y);
		}
		else if(Q[i].opt==4)
		{
			int rt=root;
			while(tr[rt].l>0)pushdown(rt),rt=tr[rt].l;
			int fa=tr[rt].key.fa,rc=tr[rt].key.rc;
			if(fa==0)
			{
				printf("1\n");
				tr[rbt=rc].key.fa=0;
				int x;split(root,rt,rt,x);
				if(x>0)tr[x].key.dep-=1;
				if(x>0)tr[x].bk-=1;
				root=x;
				continue;
			}
			int x,y;split(root,fa-1,x,y);split(x,rt,rt,x);
			if(x>0)tr[x].key.dep-=1;
			if(x>0)tr[x].bk-=1;
			printf("%d\n",tr[rt].key.dep);
			tr[fa].key.lc=rc;tr[rc].key.fa=fa;
			root=merge(x,y);
		}
		else if(Q[i].opt==3)
		{
			int rt=root;
			while(tr[rt].r>0)pushdown(rt),rt=tr[rt].r;
			int fa=tr[rt].key.fa,lc=tr[rt].key.lc;
			if(fa==0)
			{
				printf("1\n");
				continue;
			}
			int x,y;split(root,fa,x,y);
			printf("%d\n",tr[rt].key.dep);
			if(x>0)tr[x].key.dep+=1;
			if(x>0)tr[x].bk+=1;
			tr[rt].key.fa=0;tr[rt].key.lc=rbt;tr[rt].key.dep=1;
			tr[rbt].key.fa=rt;rbt=rt;
			tr[fa].key.rc=lc;tr[lc].key.fa=fa;
			root=merge(x,y);
		}
		else
		{
			int rt=root;
			while(tr[rt].r>0)pushdown(rt),rt=tr[rt].r;
			int fa=tr[rt].key.fa,lc=tr[rt].key.lc;
			if(fa==0)
			{
				printf("1\n");
				tr[rbt=lc].key.fa=0;
				int x;split(root,rt-1,x,rt);
				if(x>0)tr[x].key.dep-=1;
				if(x>0)tr[x].bk-=1;
				root=x;
				continue;
			}
			int x,y;split(root,fa,x,y);split(y,rt-1,y,rt);
			if(y>0)tr[y].key.dep-=1;
			if(y>0)tr[y].bk-=1;
			printf("%d\n",tr[rt].key.dep);
			tr[fa].key.rc=lc;tr[lc].key.fa=fa;
			root=merge(x,y);
		}
	}
	return 0;
}