#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
struct node
{
	int l,r,lc,rc,min,max;
	long long c,cc;
}tr[410000];int len;
inline int mymin(int x,int y){return x<y?x:y;}
long long dfs(int x,int c)
{
	if(tr[x].max<=c)return tr[x].c;
	if(c<=tr[x].min)return 1ll*c*(tr[x].r-tr[x].l+1);
	int lc=tr[x].lc,rc=tr[x].rc;
	if(c<=tr[rc].min)return dfs(lc,c)+1ll*c*(tr[rc].r-tr[rc].l+1);
	else return tr[x].cc+dfs(rc,c);
}
void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].min=mymin(tr[lc].min,tr[rc].min);
	tr[x].max=tr[rc].max;
	tr[x].cc=dfs(lc,tr[rc].min);
	tr[x].c=tr[x].cc+tr[rc].c;
}
int f[210000];
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
	else tr[now].min=tr[now].max=tr[now].c=f[l];
}
void change(int now,int x,int c)
{
	if(tr[now].l==tr[now].r){tr[now].min=tr[now].max=tr[now].c=c;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(lc,x,c);
	else change(rc,x,c);
	update(now);
}
int findmin;
long long solve(int now,int l,int r,int c)
{
	if(c<=tr[now].min)return 1ll*c*(r-l+1);
	if(tr[now].l==l&&tr[now].r==r)
	{
		findmin=mymin(findmin,tr[now].min);
		return dfs(now,c);
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return solve(lc,l,r,c);
	else if(l>=mid+1)return solve(rc,l,r,c);
	else
	{
		long long cr=solve(rc,mid+1,r,c);
		return solve(lc,l,mid,findmin)+cr;
	}
}
int a[210000];
set<int> S[210000];
int main()
{
	freopen("team.in","r",stdin);
	freopen("team.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)
	{
		set<int>::iterator it=S[a[i]].begin();
		if(it==S[a[i]].end())f[i]=n;
		else f[i]=*it-1;
		S[a[i]].insert(i);
	}
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			set<int>::iterator it=S[a[x]].find(x);
			if(it!=S[a[x]].begin())
			{
				set<int>::iterator ti=it;
				it--;ti++;
				if(ti==S[a[x]].end())change(1,*it,n);
				else change(1,*it,*ti-1);
			}
			S[a[x]].erase(x);
			a[x]=y;
			it=S[y].insert(x).first;
			if(it!=S[y].begin())
			{
				set<int>::iterator ti=it;
				ti--;
				change(1,*ti,x-1);
			}
			it++;
			if(it==S[y].end())change(1,x,n);
			else change(1,x,*it-1);
		}
		else
		{
			findmin=y;
			printf("%lld\n",solve(1,x,y,y)-1ll*(y-x+1)*(y+x-2)/2);
		}
	}
	return 0;
}