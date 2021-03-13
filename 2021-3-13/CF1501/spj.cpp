#include<cstdio>
#include<cstring>
using namespace std;
int a[210000];
char c[1100];
int main()
{
	freopen("C.in","r",stdin);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	FILE *fp=fopen("C.out","r");
	fscanf(fp,"%s",c+1);
	if(strcmp(c+1,"YES")==0)
	{
		int A,B,C,D;fscanf(fp,"%d%d%d%d",&A,&B,&C,&D);
		if(A==B||A==C||A==D||B==C||B==D||C==D)puts("Wrong1");
		else if(A<1||B<1||C<1||D<1||A>n||B>n||C>n||D>n)puts("wrong2");
		else
		{
			if(a[A]+a[B]!=a[C]+a[D])puts("wrong3");
			else puts("Accept");
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			for(int k=i+1;k<=n;k++)
			{
				if(k==j)continue;
				for(int l=k+1;l<=n;l++)
				{
					if(l==j)continue;
					if(a[i]+a[j]==a[k]+a[l])
					{
						puts("Worng");
						return 0;
					}
				}
			}
		}
	}
	puts("Accept");
	return 0;
}