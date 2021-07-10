#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
set<int> p[210000];
struct node
{
	int l,r,lc,rc,c;
	long long cc;
}tr[410000];int len;
int L[210000],col[210000],v[210000];
inline int mymax(int x,int y){return x>y?x:y;}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		tr[now].c=mymax(tr[tr[now].lc].c,tr[tr[now].rc].c);
		tr[now].cc=tr[tr[now].lc].cc+tr[tr[now].rc].cc;
	}
	else tr[now].c=L[l],tr[now].cc=v[l];
}
void change(int now,int x,int c,int cc)
{
	if(tr[now].l==tr[now].r){tr[now].c=c;tr[now].cc=cc;return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)change(lc,x,c,cc);
	else change(rc,x,c,cc);
	tr[now].c=mymax(tr[lc].c,tr[rc].c);
	tr[now].cc=tr[lc].cc+tr[rc].cc;
}
long long ss;
int search(int now,int x,int c)
{
	if(tr[now].c<c&&tr[now].l==x){ss+=tr[now].cc;return -1;}
	if(tr[now].l==tr[now].r)return tr[now].l;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(x<=mid)
	{
		int re=search(lc,x,c);
		if(re==-1)re=search(rc,mid+1,c);
		return re;
	}
	else return search(rc,x,c);
}
int t[110],tv[110],tt;
int main()
{
	freopen("gp.in","r",stdin);
	freopen("gp.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&col[i],&v[i]);
		p[col[i]].insert(i);
	}
	for(int i=1;i<=n;i++)
	{
		int l=0;
		for(set<int>::iterator it=p[i].begin();it!=p[i].end();it++)
		{
			L[*it]=l;
			l=*it;
		}
	}
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if(opt==1)
		{
			int x,c,cc;scanf("%d%d%d",&x,&c,&cc);
			set<int>::iterator it=p[col[x]].upper_bound(x);
			if(it!=p[col[x]].end())
			{
				L[*it]=L[x];
				change(1,*it,L[x],v[*it]);
			}
			p[col[x]].erase(x);
			col[x]=c;v[x]=cc;
			it=p[c].insert(x).first;
			if(it!=p[c].begin())
			{
				it--;
				L[x]=*it;
			}
			else L[x]=0;
			it=p[c].upper_bound(x);
			if(it!=p[c].end())
			{
				L[*it]=x;
				change(1,*it,x,v[*it]);
			}
			change(1,x,L[x],cc);
		}
		else
		{
			int x,k;scanf("%d%d",&x,&k);
			ss=tt=0;int ps=search(1,x,x);
			while(ps!=-1&&k>0)
			{
				if(v[L[ps]]<v[ps])ss+=v[ps]-v[L[ps]];
				else
				{
					tt++;
					t[tt]=ps;
					tv[tt]=v[ps];
					v[ps]=v[L[ps]];
				}
				k--;
				if(ps<n)ps=search(1,ps+1,x);
				else break;
			}
			for(int j=1;j<=tt;j++)v[t[j]]=tv[j];
			printf("%lld\n",ss);
		}
	}
	return 0;
}
