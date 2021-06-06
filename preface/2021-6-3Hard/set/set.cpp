#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long lim,c[210000];
int n,a[210000];
struct node
{
	long long a,b;
}Ans[10010000];int len;
inline bool cmp(node x,node y){return x.a*y.b<y.a*x.b;}
long long gcd(long long x,long long y){return y==0?x:gcd(y,x%y);}
void dfs(int k,long long s)
{
	if(k>1)Ans[++len]=(node){s,k-1};
	for(int i=a[k-1]+1;i<=n;i++)
	{
		if((s+c[i])*n*2<=lim*k)
		{
			a[k]=i;
			dfs(k+1,s+c[i]);
			a[k]=0;
		}
		else break;
	}
}
int main()
{
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	sort(c+1,c+n+1);
	int gg=0;
	for(int i=1;i<=n;i++)gg+=c[i]==c[1];
	if(gg>20||m<=1<<gg)
	{
		while(m--)printf("%lld/1\n",c[1]);
		return 0;
	}
	int step=c[n]-c[1]+1;
	for(lim=c[1]*n*2;lim<c[n]*n*2+step;lim+=step)
	{
		len=0;
		a[0]=0;
		dfs(1,0);
		if(m<=len)break;
	}
	sort(Ans+1,Ans+len+1,cmp);
	for(int i=1;i<=m;i++)
	{
		long long t=gcd(Ans[i].a,Ans[i].b);
		printf("%lld/%lld\n",Ans[i].a/t,Ans[i].b/t);
	}
	return 0;
}
