#include<cstdio>
#include<cstring>
using namespace std;
inline int lowbit(int x){return x&-x;}
int f[1048576],ff[1048576],g[20][1048576],h[1048576],a[20],b[20],c[20];
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("pl.in","r",stdin);
	freopen("pl.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int i=0;i<n;i++)scanf("%d",&b[i]);
	for(int i=0;i<n;i++)h[1<<i]=i;
	for(int i=0;i<n;i++)
	{
		g[i][0]=0x3f3f3f3f;
		for(int j=1;j<1<<n;j++)g[i][j]=mymin(g[i][j-lowbit(j)],a[i]^b[h[lowbit(j)]]);
	}
	memset(f,63,sizeof(f));f[0]=0;
	for(int i=1;i<1<<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if((i|1<<j)==i)
			{
				if(f[i-(1<<j)]+g[j][(1<<n)-i-1+(1<<j)]<f[i])
				{
					f[i]=f[i-(1<<j)]+g[j][(1<<n)-i-1+(1<<j)];
					ff[i]=j;
				}
			}
		}
	}
	printf("%d\n",f[(1<<n)-1]);
	int x=(1<<n)-1;
	for(int i=0;i<n;i++){c[i]=ff[x]+1;x-=1<<ff[x];}
	for(int i=0;i<=n-2;i++)printf("%d ",c[i]);
	printf("%d\n",c[n-1]);
	return 0;
}