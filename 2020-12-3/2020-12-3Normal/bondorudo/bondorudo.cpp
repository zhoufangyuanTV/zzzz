#include<cstdio>
#include<cstring>
using namespace std;
bool b[110][110];
int main()
{
	freopen("bondorudo.in","r",stdin);
	freopen("bondorudo.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	if(m==n-1)
	{
		puts("1");
		for(int i=1;i<n;i++)printf("%d %d\n",i,i+1);
	}
	else if(m<n+(n+1)/2)
	{
		puts("2");
		memset(b,false,sizeof(b));
		printf("%d %d\n",1,n);b[1][n]=true;
		for(int i=1;i<n;i++){printf("%d %d\n",i,i+1);b[i][i+1]=true;}
		int gm=n;
		for(int i=1;i<=n;i++)
		{
			if(gm==m)break;
			for(int j=i+1;j<=n;j++)
			{
				if(gm==m)break;
				if(b[i][j]==false)
				{
					printf("%d %d\n",i,j);
					b[i][j]=true;
					gm++;
				}
			}
		}
	}
	else
	{
		puts("3");
		memset(b,false,sizeof(b));
		printf("%d %d\n",1,n);b[1][n]=true;
		for(int i=1;i<n;i++){printf("%d %d\n",i,i+1);b[i][i+1]=true;}
		for(int i=1;i<=(n+1)/2;i++)
		{
			if(i+(n+1)/2>n)
			{
				printf("%d %d",i,n);
				b[i][n]=true;
				break;
			}
			printf("%d %d\n",i,i+(n+1)/2);
			b[i][i+(n+1)/2]=true;
		}
		int gm=n+(n+1)/2;
		for(int i=1;i<=n;i++)
		{
			if(gm==m)break;
			for(int j=i+1;j<=n;j++)
			{
				if(gm==m)break;
				if(b[i][j]==false)
				{
					printf("%d %d\n",i,j);
					b[i][j]=true;
					gm++;
				}
			}
		}
	}
	return 0;
}
