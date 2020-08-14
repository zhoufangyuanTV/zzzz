#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
namespace tree
{
	struct treap
	{
		int f,l,r,c,key,len,dep,size;
		long long lenc,cc;
		int ccc;
	}tr[1010000];
	inline void update(int x)
	{
		tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
		tr[x].lenc=tr[tr[x].l].lenc+tr[tr[x].r].lenc+tr[x].len;
		tr[x].cc=tr[tr[x].l].cc+tr[tr[x].r].cc+1ll*tr[x].key*tr[x].len;
		if(tr[x].l!=0)tr[tr[x].l].f=x;if(tr[x].r!=0)tr[tr[x].r].f=x;
	}
	inline void pushdown(int x)
	{
		tr[tr[x].l].key+=tr[x].ccc;
		tr[tr[x].l].cc+=1ll*tr[x].ccc*tr[tr[x].l].lenc;
		tr[tr[x].l].ccc+=tr[x].ccc;
		tr[tr[x].r].key+=tr[x].ccc;
		tr[tr[x].r].cc+=1ll*tr[x].ccc*tr[tr[x].r].lenc;
		tr[tr[x].r].ccc+=tr[x].ccc;
		tr[x].ccc=0;
	}
	void split(int now,int c,int &x,int &y)
	{
		if(now==0)x=y=0;
		else
		{
			pushdown(now);
			if(c<=tr[now].dep)
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
			pushdown(x);
			tr[x].r=merge(tr[x].r,y);
			update(x);
			return x;
		}
		else
		{
			pushdown(y);
			tr[y].l=merge(x,tr[y].l);
			update(y);
			return y;
		}
	}
	inline int find(int x){while(tr[x].f!=0)x=tr[x].f;return x;}
	inline int top(int x){while(tr[x].l!=0)x=tr[x].l;return x;}
}
struct node
{
	int son[26],len,fail,size;
}tr[1010000];int trlen;
int a[110000];
int main()
{
	int n,sig;scanf("%d%d",&n,&sig);
	trlen=1;memset(tr,0,sizeof(tr));
	memset(tree::tr,0,sizeof(tree::tr));
	tr[1].len=-1;tr[1].fail=1;tr[1].size=0;
	tr[0].len=0;tr[0].fail=1;tr[0].size=0;
	tree::tr[0].dep=0;
	long long ss=0;int j=1;a[0]=-1;
	for(int i=1;i<=n;i++)
	{
		long long x;scanf("%lld",&x);
		if(sig==1)x^=ss;a[i]=x;
		while(a[i]!=a[i-tr[j].len-1])j=tr[j].fail;
		if(tr[j].son[x]==0)
		{
			tr[j].son[x]=++trlen;
			tr[trlen].len=tr[j].len+2;
			if(j==1)tr[trlen].fail=0;
			else
			{
				int k=tr[j].fail;
				while(j>1&&a[i]!=a[i-tr[k].len-1])k=tr[k].fail;
				tr[trlen].fail=tr[k].son[x];
			}
			tree::tr[trlen].c=rand();
			tree::tr[trlen].len=tr[trlen].len-tr[tr[trlen].fail].len;
			tree::tr[trlen].dep=tree::tr[tr[trlen].fail].dep+1;
			tree::tr[trlen].size=1;
			tree::tr[trlen].lenc=tree::tr[trlen].len;
		}
		j=tr[j].son[x];
		int k=j,dj=tree::tr[j].dep+1,y=0;
		while(k!=0)
		{
			int fk=tree::find(k);
			int aa,bb;tree::split(fk,dj,aa,bb);
			tree::tr[aa].f=0;tree::tr[bb].f=0;
			int tp=tree::top(aa);
			y=tree::merge(aa,y);
			dj=tree::tr[tp].dep;
			k=tr[tp].fail;
		}
		tree::tr[y].key++;
		tree::tr[y].cc+=tree::tr[y].lenc;
		tree::tr[y].ccc++;
		ss+=tree::tr[y].cc;
		printf("%lld\n",ss);
	}
	return 0;
}