#include<cstdio>
#include<cstring>
using namespace std;
char a[1100];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		int len=0;
		for(int i=1;i<=26;i++)
		{
			for(int j=1;j<=233;j++)
			{
				if(j>n)break;
				a[++len]=i+'a'-1;
				n-=j;
			}
			if(n==0)break;
		}
		a[len+1]='\0';
		puts(a+1);
	}
	return 0;
}