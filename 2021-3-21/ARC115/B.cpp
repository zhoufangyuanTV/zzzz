#include<cstdio>
#include<cstring>
using namespace std;
int a[510][510],b[510][510],c[510][510];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)scanf("%d",&c[i][j]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=2;j<=n;j++)b[i][j]=c[i][j]-c[i][1];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=2;j<=n;j++)a[j][i]=c[j][i]-c[1][i];
	}
	bool bk=true;
	for(int i=2;i<=n;i++)
	{
		for(int j=2;j<=n;j++)if(a[i][j]!=a[i][1]){bk=false;break;}
		if(bk==false)break;
	}
	if(bk==false)
	{
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=2;i<=n;i++)
	{
		for(int j=2;j<=n;j++)if(b[j][i]!=b[1][i]){bk=false;break;}
		if(bk==false)break;
	}
	if(bk==false)
	{
		puts("No");
		return 0;
	}
	int A=0,B;
	for(int i=2;i<=n;i++)if(A<-a[i][1])A=-a[i][1];
	B=c[1][1]-A;
	printf("%d",A);
	for(int i=2;i<=n;i++)printf(" %d",A+a[i][1]);
	putchar('\n');
	printf("%d",B);
	for(int i=2;i<=n;i++)printf(" %d",B+b[1][i]);
	putchar('\n');
	return 0;
}