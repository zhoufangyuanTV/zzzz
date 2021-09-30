#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int root;
struct node
{
	int l,r,c,key,size;
	long long s1,s2;
}tr[110000];int len;
inline void update(int x)
{
	tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
	if(tr[tr[x].l].size&1)
	{
		tr[x].s1=tr[tr[x].l].s1+tr[tr[x].r].s1;
		tr[x].s2=tr[tr[x].l].s2+tr[tr[x].r].s2+tr[x].key;
	}
	else
	{
		tr[x].s1=tr[tr[x].l].s1+tr[tr[x].r].s2+tr[x].key;
		tr[x].s2=tr[tr[x].l].s2+tr[tr[x].r].s1;
	}
}
void split(int now,int key,int &x,int &y)
{
	if(now==0)x=y=0;
	else
	{
		if(key<tr[now].key)
		{
			y=now;split(tr[now].l,key,x,tr[y].l);
		}
		else
		{
			x=now;split(tr[now].r,key,tr[x].r,y);
		}
		update(now);
	}
}
int merge(int x,int y)
{
	if(x==0||y==0)return x+y;
	if(tr[x].c<tr[y].c)
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
inline int new_node(int key)
{
	len++;int now=len;
	tr[now].l=tr[now].r=0;
	tr[now].c=rand();tr[now].key=key;
	tr[now].size=1;
	tr[now].s1=key;tr[now].s2=0;
	return now;
}
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	int n;scanf("%d",&n);
	long long a=0,b=0,sb=0;
	root=len=0;
	for(int i=1;i<=n;i++)
	{
		long long X,A,B;scanf("%lld%lld%lld",&X,&A,&B);
		X%=A+B;
		int ga=X/A,gb=X/B;
		if(ga==0)b+=gb;
		else if(gb==0)a+=ga;
		else
		{
			sb+=gb;
			int x,y;
			split(root,ga+gb,x,y);
			root=merge(merge(x,new_node(ga+gb)),y);
		}
		bool fir=a+tr[root].s1>b+sb,sec=a+tr[root].s2>=b+sb;
		if(fir==sec)
		{
			if(fir)puts("Alice");
			else puts("Bob");
		}
		else
		{
			if(fir)puts("First");
			else puts("Second");
		}
	}
	return 0;
}