#include<cstdio>
#include<cstring>
using namespace std;
int p;
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
long long jc[110],fjc[110];
inline long long C(int n,int m){return n<m?0:jc[n]*fjc[n-m]%p*fjc[m]%p;}
long long f[110][110][110],g[110][110][110];
int main()
{
	freopen("far.in","r",stdin);
	freopen("far.out","w",stdout);
	int n;scanf("%d%d",&n,&p);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	fjc[n]=ksm(jc[n],p-2);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	memset(f,0,sizeof(f));f[0][0][1]=1;
	memset(g,0,sizeof(g));
	for(int i=1;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			for(int k=1;k<=j-i+1;k++)
			{
				for(int l=1;l<=j-k-i+2;l++)
				{
					f[i][j][k]=(f[i][j][k]+f[i-1][j-k][l]*ksm(ksm(2,l)+p-1,k))%p;
					g[i][j][k]=(g[i][j][k]+g[i][j-k][l]*ksm(ksm(2,l)+p-1,k))%p;
				}
				f[i][j][k]=f[i][j][k]*C(j,k)%p*ksm(2,k*(k-1)/2)%p;
				g[i][j][k]=g[i][j][k]*C(j-1,k)%p*ksm(2,k*(k-1)/2)%p;
				g[i][j][k]=(g[i][j][k]+f[i][j][k]*k%p*jc[j-1]%p*fjc[j])%p;
			}
		}
	}
	long long ss=0;
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=n-i;j++)
		{
			ss=(ss+g[i][n-1][j]*i)%p;
		}
	}
	printf("%lld\n",ss);
	return 0;
}
