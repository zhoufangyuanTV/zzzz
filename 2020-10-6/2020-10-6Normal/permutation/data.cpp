#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int p[100001];
int main()
{
	freopen("permutation.in","w",stdout);
	int n=100000,q=20000;
	printf("%d %d\n",n,q);
	for(int i=1;i<=n;i++)p[i]=i;
	random_shuffle(p+1,p+n+1);
	for(int i=1;i<n;i++)printf("%d ",p[i]);
	printf("%d\n",p[n]);
	for(int i=1;i<=n;i++)
	{
		int x=rand()%(n-1)+1;
		printf("%d\n",x);
	}
	return 0;
}