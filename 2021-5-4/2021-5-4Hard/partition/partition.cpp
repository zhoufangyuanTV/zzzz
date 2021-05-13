#include<cstdio>
#include<cstring>
using namespace std;
int f[1010000],a[1010000];
inline int plus(int x,int y){return x+y<998244353?x+y:x+y-998244353;}
int main()
{
	freopen("partition.in","r",stdin);
	freopen("partition.out","w",stdout);
	int n,k,p;scanf("%d%d%d",&n,&k,&p);
	for(int i=0;i<p;i++)scanf("%d",&a[i]);
	if(k==0&&p==1)
	{
		if(a[0])
		{
			int ss=0;
			memset(f,0,sizeof(f));f[0]=1;
			for(int i=1;i*i<=n;i++)
			{
				for(int j=i;j<=n;j++)f[j]=plus(f[j],f[j-i]);
				for(int j=i;j<=n;j++)f[j]=plus(f[j],f[j-i]);
				ss=plus(ss,f[n-i*i]);
			}
			printf("%d\n",ss);
		}
		else puts("0");
	}
	else
	{
		int ss=0;
		memset(f,0,sizeof(f));f[0]=1;
		for(int i=1;i*((i-1)*k+2)/2<=n;i++)
		{
			if(a[i%p])
			{
				for(int j=n-i;j>=0;j-=i)ss=plus(ss,f[j]);
			}
			for(int j=n;j>=i*k;j--)f[j]=f[j-i*k];
			for(int j=0;j<i*k;j++)f[j]=0;
			for(int j=i;j<=n;j++)f[j]=plus(f[j],f[j-i]);
		}
		printf("%d\n",ss);
	}
	return 0;
}