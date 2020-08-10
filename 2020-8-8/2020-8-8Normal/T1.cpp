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
long long jc[110000],fjc[110000];
long long a[51],f[51][51][1610][3];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	jc[0]=1;
	for(int i=1;i<=m;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[m]=ksm(jc[m],1000000005);
	for(int i=m-1;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	sort(a+1,a+n+1);
	memset(f,0,sizeof(f));f[0][1][0][2]=1;
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<=i+1;j++)
		{
			for(int k=0;k<=40*i;k++)
			{
				for(int l=0;l<=2;l++)
				{
					f[i+1][j+1][k][l]=(f[i+1][j+1][k][l]+f[i][j][k][l]*j%1000000007)%1000000007;
					f[i+1][j][k+a[i+1]][l]=(f[i+1][j][k+a[i+1]][l]+f[i][j][k][l]*(2*j-l)%1000000007)%1000000007;
					if(l>0)f[i+1][j][k][l-1]=(f[i+1][j][k][l-1]+f[i][j][k][l]*l%1000000007)%1000000007;
					if(i>1)f[i+1][j-1][k+2*a[i+1]][l]=(f[i+1][j-1][k+2*a[i+1]][l]+f[i][j][k][l]*(j-l)%1000000007)%1000000007;
					if(i>0&&l>0)f[i+1][j-1][k+a[i+1]][l-1]=(f[i+1][j-1][k+a[i+1]][l-1]+f[i][j][k][l]*l%1000000007)%1000000007;
				}
			}
		}
	}
	long long ss=0;
	for(int i=0;i<=40*n;i++)ss=(ss+f[n][0][i][0]*jc[m-i+n-1]%1000000007*fjc[m-i-1]%1000000007*fjc[n]%1000000007)%1000000007;
	printf("%lld\n",ss);
	return 0;
}