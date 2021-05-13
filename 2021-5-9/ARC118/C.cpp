#include<cstdio>
#include<cstring>
using namespace std;
bool a[11000];
int main()
{
	memset(a,false,sizeof(a));
	for(int i=6;i<=10000;i+=6)a[i]=true;
	for(int i=10;i<=10000;i+=10)a[i]=true;
	for(int i=15;i<=10000;i+=15)a[i]=true;
	int n;scanf("%d",&n);
	printf("6 10 15");a[6]=a[10]=a[15]=false;
	n-=3;
	for(int i=1;i<=10000;i++)
	{
		if(n==0)return 0;
		if(a[i]){printf(" %d",i);n--;}
	}
	return 0;
}