#include<cstdio>
#include<cstring>
using namespace std;
long long f[8192][501][13];
int a[13],popcnt[8192];
int main()
{
	freopen("ranklist.in","r",stdin);
	freopen("ranklist.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	popcnt[0]=0;
	for(int i=1;i<1<<n;i++)popcnt[i]=popcnt[i>>1]+(i&1);
	int ma=-1,p=-1;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		if(ma<a[i]){ma=a[i];p=i;}
	}
	for(int i=0;i<n;i++)
	{
		m-=ma-a[i];
		a[i]=ma-a[i];
	}
	if(m<0)
	{
		puts("0");
		return 0;
	}
	//if(m>(n+1)*n/2)m=(n+1)*n/2;
	for(int i=0;i<=p;i++)f[1<<i][0][i]=1;
	if(n<=m)for(int i=p+1;i<n;i++)f[1<<i][n][i]=1;
	for(int i=1;i<1<<n;i++)
	{
		int g=n-popcnt[i];
		for(int j=0;j<=m;j++)
		{
			for(int k=0;k<n;k++)
			{
				if((i>>k&1)&&f[i][j][k]>0)
				{
					for(int l=0;l<k;l++)
					{
						if(i>>l&1)continue;
						if(a[l]<a[k])
						{
							if(j+g*(a[k]-a[l])<=m)f[i|1<<l][j+g*(a[k]-a[l])][l]+=f[i][j][k];
						}
						else f[i|1<<l][j][l]+=f[i][j][k];
					}
					for(int l=k+1;l<n;l++)
					{
						if(i>>l&1)continue;
						if(a[l]+1<a[k])
						{
							if(j+g*(a[k]-a[l])<=m)f[i|1<<l][j+g*(a[k]-a[l])][l]+=f[i][j][k];
						}
						else if(j+g<=m)f[i|1<<l][j+g][l]+=f[i][j][k];
					}
				}
			}
		}
	}
	long long ss=0;
	for(int i=0;i<=m;i++)for(int j=0;j<n;j++)ss+=f[(1<<n)-1][i][j];
	printf("%lld\n",ss);
	return 0;
}
