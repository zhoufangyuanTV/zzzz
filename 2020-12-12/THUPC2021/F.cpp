#include<cstdio>
#include<cstring>
using namespace std;
int a[1100],g[1100];
char Ans[1100][1100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d",&a[i]);
	memset(Ans,0,sizeof(Ans));
	if(n%2==0)
	{
		for(int i=1;i<=m;i++)
		{
			if(a[i]>n/2)
			{
				puts("No");
				return 0;
			}
			for(int j=1;j<=n;j++)
			{
				if(a[i]>0&&(j&1)==(i&1))
				{
					a[i]--;
					Ans[j][i]='1';
				}
				else Ans[j][i]='0';
			}
		}
	}
	else
	{
		int p=-1,t=0;
		for(int i=1;i<=m;i++)
		{
			int A=a[i];t^=1;
			if(A>n/2+1)
			{
				puts("No");
				return 0;
			}
			if(A==n/2+1)
			{
				if(t==1)p=i;
				else
				{
					if(p==-1)
					{
						for(int j=1;j<i;j++)
						{
							int AA=a[j];
							for(int k=1;k<=n;k++)
							{
								if(AA>0&&((j&1)!=(k&1)))
								{
									AA--;
									Ans[k][j]='1';
								}
								else Ans[k][j]='0';
							}
						}
						p=i;
					}
					else
					{
						t=1;
						for(int j=p+1;j<i;j++)
						{
							for(int k=1;k<=n;k++)Ans[k][j]='0';
							t=t^1;
							int AA=a[j];
							for(int k=t?n-1:n;k>=1;k-=2)
							{
								if(Ans[k][j-1]=='1')break;
								if(AA>0)AA--,Ans[k][j]='1';
							}
							for(int k=t?1:2;k<=n;k+=2)
							{
								if(Ans[k][j-1]=='1')break;
								if(AA>0)AA--,Ans[k][j]='1';
							}
						}
						p=i;
					}
					t=1;
				}
			}
			for(int j=1;j<=n;j++)Ans[j][i]='0';
			for(int j=t?1:2;j<=n;j+=2)
			{
				if(A==0)break;
				if(Ans[j][i-1]=='1')
				{
					puts("No");
					return 0;
				}
				A--;Ans[j][i]='1';
			}
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++)puts(Ans[i]+1);
	return 0;
}