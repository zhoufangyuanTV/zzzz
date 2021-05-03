#include<cstdio>
#include<cstring>
using namespace std;
long long f[1024],a[110];
int main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%lld",&a[i]);
	memset(f,0,sizeof(f));f[0]=1;
	for(int i=1;i<1<<n;i++)
	{
		int cnt=0;
		for(int j=0;j<n;j++)
		{
			if(i>>j&1)cnt++;
		}
		int ct=cnt;
		for(int j=0;j<n;j++)
		{
			if(i>>j&1)
			{
				ct--;
				if(ct&1)f[i]=(f[i]-f[i^1<<j]*a[(cnt-1)&j]%998244353+998244353)%998244353;
				else f[i]=(f[i]+f[i^1<<j]*a[(cnt-1)&j])%998244353;
			}
		}
	}
	printf("%lld\n",f[(1<<n)-1]);
	return 0;
}
