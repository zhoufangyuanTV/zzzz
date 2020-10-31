#include<cstdio>
#include<cstring>
using namespace std;
int f[6100];
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	memset(f,0,sizeof(f));f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j>=1;j--)f[j]=(f[j*2]+f[j-1])%998244353;
		f[0]=0;
	}
	printf("%d\n",f[k]);
	return 0;
}