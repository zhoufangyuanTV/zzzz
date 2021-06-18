#include<cstdio>
#include<cstring>
using namespace std;
double f[1048576],a[510],c[510][510];
int p[510],plen;
int main()
{
	freopen("tournament.in","r",stdin);
	freopen("tournament.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			double g=1/(a[i]+a[j]);
			c[i][j]=a[i]*g;
			c[j][i]=a[j]*g;
		}
	}
	f[(1<<n)-1]=1;
	for(int i=(1<<n)-1;i>=1;i--)
	{
		plen=0;
		for(int j=1;j<=n;j++)if(i>>j-1&1)p[++plen]=j;
		if(plen>1)
		{
			double g=f[i]/(plen-1);
			for(int j=1;j<plen;j++)
			{
				f[i^1<<p[j+1]-1]+=g*c[p[j]][p[j+1]];
				f[i^1<<p[j]-1]+=g*c[p[j+1]][p[j]];
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%.15lf\n",f[1<<i-1]);
	return 0;
}
