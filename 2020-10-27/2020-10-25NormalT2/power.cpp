#include<cstdio>
#include<cstring>
using namespace std;
long long f[10010000],A[10010000];
int main()
{
	freopen("power.in","r",stdin);
	freopen("power.out","w",stdout);
	f[1]=1;
	for(int i=2;i<=10000001;i++)f[i]=f[998244353%i]*(998244353-998244353/i)%998244353;
	A[0]=1;A[1]=1;
	for(int i=2;i<=10000001;i++)A[i]=((2*i-1)*A[i-1]+(3*i-3)*A[i-2])%998244353*f[i]%998244353;
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		printf("%lld\n",(A[n+1]-A[n]+998244353)*f[2]%998244353);
	}
	return 0;
}