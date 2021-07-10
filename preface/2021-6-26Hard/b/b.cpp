#include<cstdio>
#include<cstring>
using namespace std;
int f[1010000];
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	int n;scanf("%d",&n);
	long long ss=0;
	for(int i=2*n-1;i>=1;i-=2)
	{
		f[i]=0;
		for(int j=i*3;j<=2*n;j+=i*2)
		{
			if(f[i]<=f[j])f[i]=f[j]+1;
		}
		ss+=i<<f[i];
	}
	printf("%lld\n",ss);
	return 0;
}
