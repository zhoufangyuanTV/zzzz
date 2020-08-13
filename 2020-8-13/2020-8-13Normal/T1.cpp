#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
int block[110000];
int f[110000],a[110000];
struct QwQ{int l,r,p;}Q[110000];
inline bool cmp(QwQ x,QwQ y){return block[x.l]^block[y.l]?x.l<y.l:block[x.l]&1?x.r<y.r:x.r>y.r;}
int Ans[110000];
long long ss,cnt[110000];int b[110000],s;
inline void add(int x){ss=(ss+cnt[x]*(x-1))%1000000007;cnt[x]=cnt[x]*x%1000000007;b[x]++;if(b[x]==1)s--;}
inline void del(int x){ss=(ss+cnt[x]*(f[x]-1))%1000000007;cnt[x]=cnt[x]*f[x]%1000000007;b[x]--;if(b[x]==0)s++;}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	int bk=n/sqrt(m*2/3);
	for(int i=1;i<=n;i++)block[i]=(i-1)/bk+1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].p=i;
	sort(Q+1,Q+m+1,cmp);
	ss=100000;s=100000;
	for(int i=1;i<=100000;i++)f[i]=ksm(i,1000000005);
	for(int i=1;i<=100000;i++)cnt[i]=1;
	for(int i=1;i<=100000;i++)b[i]=0;
	for(int i=Q[1].l;i<=Q[1].r;i++)add(a[i]);
	int l=Q[1].l,r=Q[1].r;
	for(int i=1;i<=m;i++)
	{
		while(l>Q[i].l)add(a[--l]);
		while(r<Q[i].r)add(a[++r]);
		while(l<Q[i].l)del(a[l++]);
		while(r>Q[i].r)del(a[r--]);
		Ans[Q[i].p]=(ss-s+1000000007)%1000000007;
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}