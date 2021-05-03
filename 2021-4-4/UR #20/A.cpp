#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long jc[110000],fjc[110000];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%998244353*fjc[m]%998244353;}
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
int tot[110000];
long long f[110000],g[110000];
int elen;
long long e[110000],re[110000],ee[110000];
int t[110000],rt[110000],tt[110000];
void dfs(int x,int fa)
{
	tot[x]=1;f[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			tot[x]+=tot[y];
			f[x]=f[x]*g[y]%998244353*C(tot[x]-1,tot[y])%998244353;
		}
	}
	elen=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			elen++;
			e[elen]=re[elen]=ee[elen]=g[y];
			t[elen]=rt[elen]=tt[elen]=tot[y];
		}
	}
	e[0]=re[elen+1]=1;
	t[0]=rt[elen+1]=0;
	for(int i=1;i<=elen;i++)
	{
		t[i]+=t[i-1];
		e[i]=e[i]*e[i-1]%998244353*C(t[i],t[i-1])%998244353;
	}
	for(int i=elen;i>=1;i--)
	{
		rt[i]+=rt[i+1];
		re[i]=re[i]*re[i+1]%998244353*C(rt[i],rt[i+1])%998244353;
	}
	g[x]=f[x];
	for(int i=1;i<=elen;i++)
	{
		g[x]=(g[x]+e[i-1]*re[i+1]%998244353*C(t[i-1]+rt[i+1],t[i-1])%998244353*ee[i]%998244353*C(tot[x]-1,tt[i]-1))%998244353;
	}
}
int main()
{
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%998244353;
	fjc[n]=ksm(jc[n],998244351);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%998244353;
	dfs(1,0);
	printf("%lld\n",f[1]);
	return 0;
}