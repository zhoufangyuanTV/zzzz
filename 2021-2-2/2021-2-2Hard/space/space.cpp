#include<cstdio>
#include<cstring>
using namespace std;
long long f[210000];
long long g[210000],a[210000];
int main()
{
	freopen("space.in","r",stdin);
	freopen("space.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	f[1]=1;
	for(int i=2;i<=n;i++)f[i]=(998244353-f[998244353%i])*(998244353/i)%998244353;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if(opt==0)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			for(int j=l;j<=r;j++)a[j]=(a[j]+x)%998244353;
		}
		else
		{
			int N,M;scanf("%d%d",&N,&M);
			for(int j=1;j<=M;j++)g[j]=0;
			long long s=0,ss=0;
			for(int j=M+1;j<=N;j++)
			{
				long long K=12*f[j]%998244353*f[j-1]%998244353*f[j-2]%998244353;
				g[j]=(((j-1)*s-ss+998244353)%998244353*K+a[j])%998244353;
				s=(s+j*g[j])%998244353;
				ss=(ss+j*j%998244353*g[j])%998244353;
			}
			printf("%lld\n",g[N]);
		}
	}
	return 0;
}
