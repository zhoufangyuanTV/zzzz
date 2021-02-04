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
long long jc[410],fjc[410];
inline long long C(int n,int m){return jc[n]*fjc[n-m]%p*fjc[m]%p;}
long long f[410][410],g[410][410],h[410][410];
int main()
{
	freopen("far.in","r",stdin);
	freopen("far.out","w",stdout);
	int n;scanf("%d%d",&n,&p);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	fjc[n]=ksm(jc[n],p-2);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	memset(f,0,sizeof(f));f[0][1]=0;g[0][1]=1;
	for(int i=1;i<=n-2;i++)
	{
		for(int j=1;i+j<n;j++)h[i][j]=ksm(ksm(2,i)+p-1,j);
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<i;j++)
		{
			for(int k=1;k<=i-j;k++)
			{
				f[i][j]=(f[i][j]+(f[i-j][k]+g[i-j][k]*(n-i+j-1))%p*h[k][j])%p;
				g[i][j]=(g[i][j]+g[i-j][k]*h[k][j])%p;
			}
			f[i][j]=f[i][j]*C(i,j)%p*ksm(2,j*(j-1)/2)%p;
			g[i][j]=g[i][j]*C(i,j)%p*ksm(2,j*(j-1)/2)%p;
		}
		f[i][i]=(n-1)*ksm(2,i*(i-1)/2);
		g[i][i]=ksm(2,i*(i-1)/2);
	}
	long long ss=0;
	for(int i=1;i<n;i++)ss=(ss+f[n-1][i])%p;
	printf("%lld\n",ss*ksm(n-1,p-2)%p);
	return 0;
}