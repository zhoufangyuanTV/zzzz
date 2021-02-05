#include<cstdio>
#include<cstring>
using namespace std;
long long f[1953125];
int popcnt[1024];
int len,a[1024],aa[1024];
int main()
{
	freopen("algebra.in","r",stdin);
	freopen("algebra.out","w",stdout);
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	if(k==0){puts("1");return 0;}
	if(n!=m){puts("0");return 0;}
	if(k>n/2)k=n-k;
	popcnt[0]=0;len=0;
	for(int i=1;i<1<<m;i++)
	{
		popcnt[i]=popcnt[i>>1]+(i&1);
		if(k==popcnt[i])a[++len]=i;
	}
	for(int i=1;i<=len;i++)
	{
		int x=0,v=1;
		for(int j=1;j<=m;j++,v*=k+1)if((a[i]|1<<(j-1))==a[i])x=x+v;
		aa[i]=x;
	}
	int v=1;
	for(int i=1;i<=m;i++)v*=k+1;
	memset(f,0,sizeof(f));f[0]=1;
	for(int i=0;i<v;i++)
	{
		if(f[i]>0)
		{
			int x=i,y=0;
			for(int j=1;j<=m;j++)
			{
				if(x%(k+1)==k)y|=1<<j-1;
				x=x/(k+1);
			}
			for(int j=1;j<=len;j++)if((y&a[j])==0)f[i+aa[j]]+=f[i];
		}
	}
	printf("%lld\n",f[v-1]);
	return 0;
}