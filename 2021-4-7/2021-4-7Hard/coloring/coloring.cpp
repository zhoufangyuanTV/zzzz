#include<cstdio>
#include<cstring>
using namespace std;
long long f[510][510],a[510];
int main()
{
	freopen("coloring.in","r",stdin);
	freopen("coloring.out","w",stdout);
	int n,m,p;scanf("%d%d%d",&n,&m,&p);
	a[0]=1;
	for(int i=1;i<=m;i++)a[i]=a[i-1]*2%p;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			f[i][j]=a[m-j];
			for(int k=1;k<i;k++)
			{
				if(j-i+k<0)
				{
					if(m-i+k<0)f[i][j]=(f[i][j]+f[k][0]*a[m-j])%p;
					else f[i][j]=(f[i][j]+f[k][0]*a[i-k-j])%p;
				}
				else f[i][j]=(f[i][j]+f[k][j-i+k])%p;
			}
		}
		for(int j=0;j<m;j++)f[i][j]=(f[i][j]-f[i][m]+p)%p;
	}
	long long ss=1;
	for(int i=1;i<=n;i++)ss=(ss+f[i][0])%p;
	printf("%lld\n",ss);
	return 0;
}
