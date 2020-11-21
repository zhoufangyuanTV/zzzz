#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[262144][37],g[262144][37],F[262144][37],G[262144][37],a[110],c[110];
inline int plus(int x,int y){return x+y<1000000007?x+y:x+y-1000000007;}
int plen,p[110];
int main()
{
	freopen("repair.in","r",stdin);
	freopen("repair.out","w",stdout);
	int n;long long K;scanf("%d%lld",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int z=0;c[0]=0;
	for(int i=1;i<=n;i++)
	{
		if(c[z]<a[i])
		{
			if(z>0&&c[z]+1<a[i])
			{
				z++;c[z]=c[z-1]+1;
			}
			c[++z]=a[i];
		}
		a[i]=z;
	}
	c[z+1]=c[z]+1;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));g[0][0]=1;
	memset(F,0,sizeof(F));
	memset(G,0,sizeof(G));
	for(int i=0;i<=z+1;i++)G[0][i]=1;
	for(int i=1;i<1<<n;i++)
	{
		plen=0;
		for(int j=1;j<=n;j++)if((i|1<<j-1)==i)p[++plen]=j;
		for(int j=a[p[plen]];j<=a[p[plen]]+1;j++)
		{
			for(int pp=1;pp<=plen;pp++)
			{
				int k=p[pp];
				if((i|1<<k-1)==i)
				{
					if(a[k]==j)
					{
						f[i][j]=plus(f[i][j],F[i-(1<<k-1)][j-1]);
						g[i][j]=plus(g[i][j],G[i-(1<<k-1)][j-1]);
					}
					else if(c[a[k]]==c[j]-1)
					{
						f[i][j]=plus(f[i][j],f[i-(1<<k-1)][j-1]);
						g[i][j]=plus(g[i][j],g[i-(1<<k-1)][j-1]);
						f[i][j]=plus(f[i][j],f[i-(1<<k-1)][j]);
						g[i][j]=plus(g[i][j],g[i-(1<<k-1)][j]);
					}
					else
					{
						f[i][j]=plus(f[i][j],f[i-(1<<k-1)][j]);
						g[i][j]=plus(g[i][j],g[i-(1<<k-1)][j]);
					}
				}
			}
			if(plen>1)f[i][j]=(f[i][j]+K*c[j]%1000000007*g[i][j])%1000000007;
		}
		for(int j=1;j<=z+1;j++)
		{
			F[i][j]=plus(F[i][j-1],f[i][j]);
			G[i][j]=plus(G[i][j-1],g[i][j]);
		}
	}
	long long b=0;
	for(int i=1,j=0;i<n;i++,j=j*2+1)b+=j;
	b=b%1000000007;
	if(g[(1<<n)-1][z+1]>0)
	{
		int ss=(f[(1<<n)-1][z+1]+b*g[(1<<n)-1][z+1])%1000000007;
		printf("%d %d\n",c[z]+1,ss);
	}
	else
	{
		int ss=(f[(1<<n)-1][z]+b*g[(1<<n)-1][z])%1000000007;
		printf("%d %d\n",c[z],ss);
	}
	return 0;
}