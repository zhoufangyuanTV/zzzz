#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct Query{int l,r,p;};
inline bool cmp(Query x,Query y){return x.l==y.l?x.r<y.r:x.l>y.l;}
int Ans[110000];
struct node
{
	int l,r,lc,rc;
	vector<Query> q;
}tr[210000];int len;
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
void change(int now,int l,int r,int q)
{
	if(tr[now].l==l&&tr[now].r==r){tr[now].q.push_back((Query){l,r,q});return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)change(lc,l,r,q);
	else if(l>=mid+1)change(rc,l,r,q);
	else
	{
		tr[now].q.push_back((Query){l,r,q});
		change(lc,l,mid,q);change(rc,mid+1,r,q);
	}
}
int a[110000];
long long c[110000],ic[110000],ac[110000];
long long count(int now)
{
	if(tr[now].l==tr[now].r)
	{
		for(vector<Query>::iterator it=tr[now].q.begin();it!=tr[now].q.end();it++)
		{
			Ans[it->p]=(Ans[it->p]+1ll*a[tr[now].l]*a[tr[now].l])%1000000007;
		}
		return 1ll*a[tr[now].l]*a[tr[now].l]%10000000007;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	sort(tr[now].q.begin(),tr[now].q.end(),cmp);
	int mi=1000000000,ma=1;
	c[mid]=ic[mid]=ac[mid]=0;
	for(int i=mid+1;i<=tr[now].r;i++)
	{
		if(a[i]<mi)mi=a[i];
		if(a[i]>ma)ma=a[i];
		ic[i]=(ic[i-1]+mi)%1000000007;
		ac[i]=(ac[i-1]+ma)%1000000007;
		c[i]=(c[i-1]+mi*ma)%1000000007;
	}
	vector<Query>::iterator jt=tr[now].q.begin();
	int nj=mid,xj=mid;mi=1000000001;ma=0;
	for(int i=mid;i>=tr[now].l;i--)
	{
		if(a[i]<mi)mi=a[i];
		if(a[i]>ma)ma=a[i];
		while(nj<tr[now].r&&mi<a[nj+1])nj++;
		while(xj<tr[now].r&&ma>a[xj+1])xj++;
		while(jt!=tr[now].q.end()&&jt->l==i&&(i!=tr[now].l||jt->r!=tr[now].r))
		{
			if(nj<xj)
			{
				if(jt->r<=nj)
				{
					Ans[jt->p]=(Ans[jt->p]+1ll*(jt->r-mid)*mi%1000000007*ma)%1000000007;
				}
				else if(jt->r<=xj)
				{
					Ans[jt->p]=(Ans[jt->p]+1ll*(nj-mid)*mi%1000000007*ma+(ic[jt->r]-ic[nj]+1000000007)*ma)%1000000007;
				}
				else Ans[jt->p]=(Ans[jt->p]+1ll*(nj-mid)*mi%1000000007*ma+(ic[xj]-ic[nj]+1000000007)*ma+c[jt->r]-c[xj]+1000000007)%1000000007;
			}
			else
			{
				if(jt->r<=xj)
				{
					Ans[jt->p]=(Ans[jt->p]+1ll*(jt->r-mid)*mi%1000000007*ma)%1000000007;
				}
				else if(jt->r<=nj)
				{
					Ans[jt->p]=(Ans[jt->p]+1ll*(xj-mid)*mi%1000000007*ma+mi*(ac[jt->r]-ac[xj]+1000000007))%1000000007;
				}
				else Ans[jt->p]=(Ans[jt->p]+1ll*(xj-mid)*mi%1000000007*ma+mi*(ac[nj]-ac[xj]+1000000007)+c[jt->r]-c[nj]+1000000007)%1000000007;
			}
			jt++;
		}
	}
	long long ss;
	if(nj<xj)ss=(1ll*(nj-mid)*mi%1000000007*ma+(ic[xj]-ic[nj])*ma+c[tr[now].r]-c[xj]+1000000007)%1000000007;
	else ss=(1ll*(xj-mid)*mi%1000000007*ma+mi*(ac[nj]-ac[xj]+1000000007)+c[tr[now].r]-c[nj]+1000000007)%1000000007;
	ss=(ss+count(lc))%1000000007;
	ss=(ss+count(rc))%1000000007;
	while(jt!=tr[now].q.end())
	{
		Ans[jt->p]=(Ans[jt->p]+ss)%1000000007;
		jt++;
	}
	return ss;
}
int main()
{
	//freopen("sequence.in","r",stdin);
	//freopen("sequence.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	len=0;bt(1,n);
	for(int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		change(1,l,r,i);
	}
	count(1);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}