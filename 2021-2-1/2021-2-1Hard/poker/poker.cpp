#include<cstdio>
#include<cstring>
using namespace std;
long long a[1100];
inline long long ksm(long long x,long long k)
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
long long G[710][710];
void Gauss(int n)
{
	for(int i=0;i<n;i++)
	{
		if(G[i][i]==0)
		{
			for(int j=i+1;j<n;j++)
			{
				if(G[j][i]!=0)
				{
					for(int k=0;k<=n;k++)G[i][k]^=G[j][k]^=G[i][k]^=G[j][k];
					break;
				}
			}
		}
		long long K=ksm(998244353-G[i][i],998244351);
		for(int j=0;j<n;j++)
		{
			if(i==j)continue;
			long long Ik=G[j][i]*K%998244353;
			for(int k=0;k<=n;k++)G[j][k]=(G[j][k]+G[i][k]*Ik)%998244353;
		}
	}
	for(int i=0;i<n;i++)G[i][n]=G[i][n]*ksm(G[i][i],998244351)%998244353;
}
int main()
{
	freopen("poker.in","r",stdin);
	freopen("poker.out","w",stdout);
	int n;long long m,k;scanf("%d%lld%lld",&n,&m,&k);
	long long A=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		A+=a[i];
	}
	A=ksm(A,998244351);
	for(int i=1;i<=n;i++)a[i]=a[i]*A%998244353;
	memset(G,0,sizeof(G));
	for(int i=0;i<m;i++)
	{
		if(i==k)
		{
			G[i][i]=1;
			G[i][m]=0;
			continue;
		}
		G[i][i]=1;
		for(int j=1;j<=n;j++)
		{
			int J=(i+j)%m;
			G[i][J]=(998244353-a[j])%998244353;
		}
		G[i][m]=1;
	}
	Gauss(m);
	printf("%lld\n",G[0][m]);
	return 0;
}