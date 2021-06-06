#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int h[110],a[110];
int main()
{
	freopen("jumps.in","w",stdout);
	srand(time(0));
	int n=20,m=10;
	for(int i=0;i<n;i++)h[i]=i+1;
	random_shuffle(h,h+n);
	printf("%d %d\n",n,m);
	printf("%d",h[0]);
	for(int i=1;i<n;i++)printf(" %d",h[i]);
	printf("\n");
	for(int i=1;i<=m;i++)
	{
		a[1]=rand()%n;
		a[2]=rand()%n;
		a[3]=rand()%n;
		a[4]=rand()%n;
		sort(a+1,a+5);
		while(a[2]==a[3])
		{
			a[1]=rand()%n;
			a[2]=rand()%n;
			a[3]=rand()%n;
			a[4]=rand()%n;
			sort(a+1,a+5);
		}
		printf("%d %d %d %d\n",a[1],a[2],a[3],a[4]);
	}
	return 0;
}
