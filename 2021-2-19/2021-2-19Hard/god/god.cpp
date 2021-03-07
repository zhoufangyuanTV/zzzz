#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node{long long k,b;}N[310000];
inline bool cmp(node x,node y){return x.k>y.k;}
long long s[310000],l[310000],r[310000],x[310000],y[310000],c[310000];
int p[310000],plen;
struct Query{long long x;int p;}Q[310000];
inline bool cm(Query x,Query y){return x.x<y.x;}
unsigned long long Ans[310000];
int main()
{
	freopen("god.in","r",stdin);
	freopen("god.out","w",stdout);
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)scanf("%lld%lld%lld%lld%lld",&s[i],&l[i],&r[i],&x[i],&y[i]);
	for(int i=1;i<=m;i++)scanf("%lld",&c[i]);
	c[0]=0;
	for(int i=1;i<=m;i++)c[i]=c[i-1]-c[i];
	for(int i=1;i<=n;i++)
	{
		N[i].b=c[r[i]]-c[l[i]-1]+s[i]*(r[i]-l[i]+1);
		N[i].k=(x[i]+y[i])*(r[i]-l[i]+1);
	}
	sort(N+1,N+n+1,cmp);
	plen=1;p[1]=1;
	for(int i=2;i<=n;i++)
	{
		while(plen>1&&(long double)(N[p[plen]].b-N[i].b)/(N[i].k-N[p[plen]].k)<=(long double)(N[p[plen-1]].b-N[p[plen]].b)/(N[p[plen]].k-N[p[plen-1]].k))plen--;
		p[++plen]=i;
	}
	for(int i=1;i<=q;i++){scanf("%lld",&Q[i].x);Q[i].p=i;}
	sort(Q+1,Q+q+1,cm);
	int j=1;
	for(int i=1;i<=q;i++)
	{
		while(j+1<=plen&&(unsigned long long)Q[i].x*(unsigned long long)N[p[j+1]].k+(unsigned long long)N[p[j+1]].b<(unsigned long long)Q[i].x*(unsigned long long)N[p[j]].k+(unsigned long long)N[p[j]].b)j++;
		Ans[Q[i].p]=(unsigned long long)Q[i].x*(unsigned long long)N[p[j]].k+(unsigned long long)N[p[j]].b;
	}
	for(int i=1;i<=q;i++)printf("%llu\n",Ans[i]);
	return 0;
}