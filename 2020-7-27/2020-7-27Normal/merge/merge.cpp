#include<cstdio>
#include<cstring>
using namespace std;
int ka[2100];
int f[2100][2100],a[2100],b[2100];
int main()
{
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	int n;scanf("%d",&n);
	ka[1]=1;
	for(int i=2;i<=n;i++)ka[i]=ka[i-1]*(4*i-2)/(i+1);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);a[n+1]=n+1;
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	memset(f,0,sizeof(f));
	for(int i=0;i<=n+1;i++)f[i][0]=1;
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[i][j]=(f[i][j-1]+f[i-1][j])%998244353;
			int k=i,kj=j;
			while(k-1>0&&kj>0&&a[k-1]==b[kj])k--,kj--;
			f[i][j]=(f[i][j]-1ll*f[k][kj]*ka[i-k]%998244353+998244353)%998244353;
			/*
			for(int k=0;k<=j;k++)
			{
				if(k<j&&a[i-1]==b[k+1])continue;
				f[i][j]=(f[i][j]+f[i-1][k])%998244353;
			}*/
		}
	}
	printf("%d\n",f[n+1][n]);
	return 0;
}
