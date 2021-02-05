#include<cstdio>
#include<cstring>
using namespace std;
long long f[310][310];
bool a[310][310];
int jmp[310];
int main()
{
	freopen("catalan.in","r",stdin);
	freopen("catalan.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	memset(a,false,sizeof(a));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		a[x][y]=true;
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)f[i+1][i]=f[i][i]=1;
	for(int i=1;i<=n;i++)jmp[i]=i;
	for(int j=2;j<=n;j++)
	{
		for(int i=1;i<=j;i++)if(a[j][i])jmp[i]=j;
		for(int i=j-1;i>=1;i--)
		{
			int l=j,r=i;
			while(l>i&&!a[l][i])l--;
			while(r<j&&!a[i][r+1])r++;
			int g=i;
			for(int k=i+1;k<l;k++)if(g<jmp[k])g=jmp[k];
			for(int k=l;k<=r;k++)
			{
				if(g<jmp[k])g=jmp[k];
				if(k==g)f[i][j]=(f[i][j]+f[i+1][k]*f[k+1][j])%998244353;
			}
		}
	}
	printf("%lld\n",f[1][n]);
	return 0;
}
