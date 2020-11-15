#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long T[11][11];
int a[110];
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)scanf("%lld",&T[i][j]);
	}
	for(int i=1;i<n;i++)a[i]=i;
	long long ss=0;
	do
	{
		long long s=0;
		a[0]=0;a[n]=0;
		for(int i=1;i<=n;i++)s+=T[a[i-1]][a[i]];
		if(s==k)ss++;
	}while(next_permutation(a+1,a+n));
	printf("%lld\n",ss);
	return 0;
}