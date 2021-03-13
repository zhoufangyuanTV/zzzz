#include<cstdio>
#include<cstring>
using namespace std;
int p;
long long jc[110],fjc[110];
long long ksm(long long x,long long k)
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
inline long long C(int n,int m){return jc[n]*fjc[n-m]%p*fjc[m]%p;}
long long f[110][11000];
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int n;scanf("%d%d",&n,&p);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	fjc[n]=ksm(jc[n],p-2);
	for(int i=n-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%p;
	memset(f,0,sizeof(f));
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			f[i][j*j+(i-j)*(i-j)]=(f[i][j*j+(i-j)*(i-j)]+C(i-1,j-1))%p;
			for(int k=1;k<j*j;k++)f[i][k+(i-j)*(i-j)]=(f[i][k+(i-j)*(i-j)]-C(i-1,j-1)*f[j][k]%p+p)%p;
		}
	}
	long long ss=0;
	for(int i=1;i<n*n;i++)ss=(ss+f[n][i]*n%p*n%p*ksm((n*n-i+p)%p,p-2))%p;
	printf("%lld\n",ss);
	return 0;
}