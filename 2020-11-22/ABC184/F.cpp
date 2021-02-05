#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1048576],b[1048576],c[110];
int main()
{
	int n,t;scanf("%d%d",&n,&t);
	int al=0,bl=0;
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	int ng=n/2;n=n-ng;
	for(int i=0;i<1<<ng;i++)
	{
		long long s=0;
		for(int j=1;j<=ng;j++)if((i|1<<j-1)==i)s+=c[j];
		if(s<=t)a[++al]=s;
	}
	for(int i=0;i<1<<n;i++)
	{
		long long s=0;
		for(int j=1;j<=n;j++)if((i|1<<j-1)==i)s+=c[ng+j];
		if(s<=t)b[++bl]=s;
	}
	sort(a+1,a+al+1);
	sort(b+1,b+bl+1);
	int j=bl,ss=0;
	for(int i=1;i<=al;i++)
	{
		while(j>0&&a[i]+b[j]>t)j--;
		if(j>0&&a[i]+b[j]>ss)ss=a[i]+b[j];
	}
	printf("%d\n",ss);
	return 0;
}