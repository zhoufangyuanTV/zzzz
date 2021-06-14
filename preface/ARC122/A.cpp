#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n;scanf("%d",&n);
	long long f,g,fs,gs;
	scanf("%lld",&gs);
	f=fs=0;g=1;
	for(int i=2;i<=n;i++)
	{
		long long x;scanf("%lld",&x);
		long long ff=f,gg=g,ffs=fs,ggs=gs;
		f=gg;
		g=(ff+gg)%1000000007;
		fs=(ggs-x*gg%1000000007+1000000007)%1000000007;
		gs=(ffs+ggs+x*ff+x*gg)%1000000007;
	}
	printf("%lld\n",(fs+gs)%1000000007);
	return 0;
}