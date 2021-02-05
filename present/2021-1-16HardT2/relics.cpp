#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int a[210000];
struct Query{int l,r,p;};
long long Ans[210000];
struct node
{
	int l,r,lc,rc;
	vector<Query> c;
	vector<int> g;
	long long cc;
}Q[410000];int len;
void bQ(int l,int r)
{
	len++;int now=len;
	Q[now].l=l;Q[now].r=r;Q[now].lc=Q[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		Q[now].lc=len+1;bQ(l,mid);
		Q[now].rc=len+1;bQ(mid+1,r);
	}
}
void ins(int now,int l,int r,int p)
{
	if(Q[now].l==l&&Q[now].r==r){Q[now].g.push_back(p);return ;}
	int lc=Q[now].lc,rc=Q[now].rc;
	int mid=(Q[now].l+Q[now].r)/2;
	if(r<=mid)ins(lc,l,r,p);
	else if(l>=mid+1)ins(rc,l,r,p);
	else
	{
		Q[now].c.push_back({l,r,p});
		ins(lc,l,mid,p);ins(rc,mid+1,r,p);
	}
}
inline int mymin(int x,int y){return x<y?x:y;}
inline long long mymax(long long x,long long y){return x>y?x:y;}
inline bool cmp1(Query x,Query y){return x.l>y.l;}
inline bool cmp2(Query x,Query y){return x.r<y.r;}
struct UnQuery{int l,r,x,p;};
inline bool cp1(UnQuery x,UnQuery y){return x.x<y.x;}
inline bool cp2(UnQuery x,UnQuery y){return x.x>y.x;}
vector<UnQuery> uQ;
int h[210000],rlim[210000],llim[210000];
long long ss[210000];
struct point{long double x,y;};
inline point operator-(point x,point y){return {x.x-y.x,x.y-y.y};}
inline long double operator*(point x,point y){return x.x*y.y-x.y*y.x;}
inline long double mul(point p0,point p1,point p2){return (p1-p0)*(p2-p0);}
struct trnode
{
	int l,r,lc,rc,p;
	vector<point> c;
}tr[410000];int trlen;
void bt(int l,int r)
{
	int now=++trlen;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;bt(l,mid);
		tr[now].rc=trlen+1;bt(mid+1,r);
		auto lt=tr[tr[now].rc].c.begin(),rt=tr[tr[now].rc].c.begin();
	}
	else tr[now].c={{h[l],(1ll-l)*h[l]}},tr[now].p=1;
}
void solve(int now)
{
	if(Q[now].l==Q[now].r)
	{
		Q[now].cc=a[Q[now].l];
		for(int i:Q[now].g)Ans[i]=mymax(Ans[i],Q[now].cc);
		return ;
	}
	int mid=(Q[now].l+Q[now].r)/2;
	h[mid]=a[mid];
	for(int i=mid-1;i>=Q[now].l;i--)h[i]=mymin(h[i+1],a[i]);
	h[mid+1]=a[mid+1];
	for(int i=mid+2;i<=Q[now].r;i++)h[i]=mymin(h[i-1],a[i]);
	int j=mid+1;
	for(int i=mid;i>=Q[now].l;i--)
	{
		while(j<=Q[now].r&&h[i]<=h[j])j++;
		rlim[i]=j-1;
	}
	j=mid;
	for(int i=mid+1;i<=Q[now].r;i++)
	{
		while(j>=Q[now].l&&h[i]<=h[j])j--;
		llim[i]=j+1;
	}
	sort(Q[now].c.begin(),Q[now].c.end(),cmp1);
	uQ.clear();
	j=mid+1;ss[mid+1]=0;
	auto k=Q[now].c.begin();
	for(int i=mid;i>=Q[now].l;i--)
	{
		ss[i]=mymax(ss[i+1],1ll*h[i]*(rlim[i]-i+1));
		while(k!=Q[now].c.end()&&i==k->l)
		{
			if(rlim[i]<=k->r)Ans[k->p]=mymax(Ans[k->p],ss[i]);
			else
			{
				int l=i,r=mid;
				while(l<r)
				{
					int md=(l+r+1)/2;
					if(k->r<rlim[md])l=mid;
					else r=mid-1;
				}
				Ans[k->p]=mymax(Ans[k->p],ss[r+1]);
				uQ.push_back({i,r,k->r,k->p});
			}
			k++;
		}
	}
}
int main()
{
	freopen("relics.in","r",stdin);
	freopen("relics.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	len=0;bQ(1,n);
	for(int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		ins(1,l,r,i);
	}
	return 0;
}