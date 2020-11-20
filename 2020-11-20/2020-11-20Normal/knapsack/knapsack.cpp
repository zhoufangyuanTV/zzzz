#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
long long f[21000][510];
int g[21000][510];
int a[21000],c[21000];
struct Query{int l,r,m,p;};
inline bool cmp(Query x,Query y){return x.l<y.l;}
vector<Query> Q[21];
long long Ansf[110000];
int Ansg[110000];
vector<Query>::iterator jt[21];
inline int plus(int x,int y){return x+y<998244353?x+y:x+y-998244353;}
void solve(int d,int l,int r)
{
	if(l==r)
	{
		while(jt[d]!=Q[d].end()&&jt[d]->l==l)
		{
			if(a[l]<=jt[d]->m)
			{
				Ansf[jt[d]->p]=c[l];
				Ansg[jt[d]->p]=1;
			}
			else Ansf[jt[d]->p]=Ansg[jt[d]->p]=0;
			jt[d]++;
		}
		return ;
	}
	int mid=(l+r)/2;
	solve(d+1,l,mid);
	solve(d+1,mid+1,r);
	for(int i=0;i<a[mid];i++)f[mid][i]=0,g[mid][i]=1;
	for(int i=a[mid];i<=500;i++)f[mid][i]=c[mid],g[mid][i]=1;
	for(int i=mid-1;i>=l;i--)
	{
		for(int j=0;j<=500;j++)f[i][j]=f[i+1][j],g[i][j]=g[i+1][j];
		for(int j=500;j>=a[i];j--)
		{
			if(f[i][j]<f[i+1][j-a[i]]+c[i])
			{
				f[i][j]=f[i+1][j-a[i]]+c[i];
				g[i][j]=g[i+1][j-a[i]];
			}
			else if(f[i][j]==f[i+1][j-a[i]]+c[i])g[i][j]=plus(g[i][j],g[i+1][j-a[i]]);
		}
	}
	for(int i=0;i<a[mid+1];i++)f[mid+1][i]=0,g[mid+1][i]=1;
	for(int i=a[mid+1];i<=500;i++)f[mid+1][i]=c[mid+1],g[mid+1][i]=1;
	for(int i=mid+2;i<=r;i++)
	{
		for(int j=0;j<=500;j++)f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
		for(int j=500;j>=a[i];j--)
		{
			if(f[i][j]<f[i-1][j-a[i]]+c[i])
			{
				f[i][j]=f[i-1][j-a[i]]+c[i];
				g[i][j]=g[i-1][j-a[i]];
			}
			else if(f[i][j]==f[i-1][j-a[i]]+c[i])g[i][j]=plus(g[i][j],g[i-1][j-a[i]]);
		}
	}
	for(int i=mid+1;i<=r;i++)
	{
		for(int j=500;j>=1;j--)
		{
			if(f[i][j]==f[i][j-1])g[i][j]-=g[i][j-1];
		}
	}
	while(jt[d]!=Q[d].end()&&jt[d]->r<=r)
	{
		int p=jt[d]->p,L=jt[d]->l,R=jt[d]->r,m=jt[d]->m;
		Ansf[p]=0;
		Ansg[p]=1;
		for(int i=0;i<=m;i++)
		{
			if(Ansf[p]<f[L][i]+f[R][m-i])
			{
				Ansf[p]=f[L][i]+f[R][m-i];
				Ansg[p]=1ll*g[L][i]*g[R][m-i]%998244353;
			}
			else if(Ansf[p]==f[L][i]+f[R][m-i])Ansg[p]=(Ansg[p]+1ll*g[L][i]*g[R][m-i])%998244353;
		}
		if(Ansf[p]==0)Ansg[p]=0;
		jt[d]++;
	}
}
int main()
{
	freopen("knapsack.in","r",stdin);
	freopen("knapsack.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&c[i],&a[i]);
	int q;scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int l,r,m;scanf("%d%d%d",&l,&r,&m);
		int L=1,R=n,D=0;
		int mid=(L+R)/2;
		while(L<R&&(r<=mid||l>=mid+1))
		{
			if(r<=mid)R=mid;
			else L=mid+1;
			mid=(L+R)/2;
			D++;
		}
		Q[D].push_back((Query){l,r,m,i});
	}
	for(int i=0;i<=20;i++)sort(Q[i].begin(),Q[i].end(),cmp);
	for(int i=0;i<=20;i++)jt[i]=Q[i].begin();
	solve(0,1,n);
	for(int i=1;i<=q;i++)printf("%lld %d\n",Ansf[i],Ansg[i]);
	return 0;
}