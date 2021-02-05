#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int l,r,lc,rc,S,T;
}tr[210000];int len;
int a[110000];
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	if(tr[lc].T<tr[rc].T)
	{
		if(tr[lc].S<tr[rc].T)tr[x].S=tr[lc].S;
		else tr[x].S=tr[rc].S;
		tr[x].T=tr[lc].T;
	}
	else tr[x].S=tr[rc].S,tr[x].T=tr[rc].T;
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		update(now);
	}
	else tr[now].S=l,tr[now].T=a[l];
}
void change(int now,int x,int c)
{
	if(tr[now].l==tr[now].r){tr[now].T=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(lc,x,c);
	else change(rc,x,c);
	update(now);
}
int ft(int now,int x)
{
	if(x<=tr[now].S)return tr[now].T;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)
	{
		if(x<tr[rc].T)return ft(lc,x);
		else return ft(lc,tr[rc].T);
	}
	else
	{
		int T=ft(rc,x);
		if(tr[now].l<=T&&T<=mid)return ft(lc,T);
		else return T;
	}
}
int main()
{
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(i<a[i])a[i]=i;
	}
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int opt,x;scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			int y;scanf("%d",&y);
			if(x<y)y=x;
			change(1,x,y);
		}
		else printf("%d\n",ft(1,x));
	}
	return 0;
}
