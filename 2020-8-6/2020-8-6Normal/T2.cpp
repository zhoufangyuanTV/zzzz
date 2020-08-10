#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[2510000],b[2510000];
int main()
{
	int n,m,n1,m1,md,nd;scanf("%d%d%d%d%d%d",&n,&m,&n1,&nd,&m1,&md);
	a[1]=n1;
	for(int i=2;i<=n;i++)a[i]=(a[i-1]*58+nd)%(m+1);
	sort(a+1,a+n+1);
	b[1]=m1;
	for(int i=2;i<=m;i++)b[i]=(b[i-1]*58+md)%(n+1);
	sort(b+1,b+m+1);
	long long sa=0,sb=0;int j=m;
	for(int i=1;i<=m;i++)sb+=b[i];
	long long ss=sb;
	for(int i=1;i<=n;i++)
	{
		sa+=a[i];
		while(j>0&&n-i<b[j])sb-=b[j],j--;
		if(sa+sb+1ll*(n-i)*(m-j)<ss)ss=sa+sb+1ll*(n-i)*(m-j);
	}
	printf("%lld\n",ss);
	return 0;
}