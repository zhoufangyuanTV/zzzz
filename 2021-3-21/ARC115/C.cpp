#include<cstdio>
#include<cstring>
using namespace std;
int a[110000];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		printf("%d ",a[i]+1);
		for(int j=i*2;j<=n;j+=i)
		{
			a[j]=mymax(a[j],a[i]+1);
		}
	}
	printf("%d\n",a[n]+1);
	return 0;
}