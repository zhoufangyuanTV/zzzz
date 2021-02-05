#include<cstdio>
#include<cstring>
using namespace std;
int a[110000];
long long b[110000];
long long Ans[210000];
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	memset(Ans,0,sizeof(Ans));
	for(int i=1;i<=n;i++)
	{
		long long sa=0,sb=0;
		for(int j=i;j<=n;j++)
		{
			sa+=a[j];sb+=b[j];
			if(sb>0)Ans[n+sa]++;
			if(sb<0)Ans[n-sa]++;
		}
	}
	for(int i=0;i<2*n;i++)printf("%lld ",Ans[i]);
	printf("%lld\n",Ans[2*n]);
	return 0;
}
