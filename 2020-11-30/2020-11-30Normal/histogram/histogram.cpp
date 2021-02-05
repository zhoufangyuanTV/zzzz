#include<cstdio>
#include<cstring>
using namespace std;
long long a[210000],b[210000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
inline long long mymin(long long x,long long y){return x<y?x:y;}
int main()
{
	freopen("histogram.in","r",stdin);
	freopen("histogram.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		long long A=0x3f3f3f3f3f3f3f3fll;
		long long B=0x3f3f3f3f3f3f3f3fll;
		for(int j=i;j<=n;j++)
		{
			A=mymin(A,a[j]);
			B=mymin(B,b[j]);
			ss=mymax(ss,A*B*(j-i+1));
		}
	}
	printf("%lld\n",ss);
	return 0;
}
