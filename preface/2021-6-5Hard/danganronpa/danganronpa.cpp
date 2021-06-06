#include<cstdio>
#include<cstring>
using namespace std;
int e[110][110];
int main()
{
	freopen("danganronpa.in","r",stdin);
	freopen("danganronpa.out","w",stdout);
	int n;scanf("%d",&n);
	int m=n*(n-1)/2;
	for(int i=0;i<1<<m;i++)
	{
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			for(int k=j+1;k<=n;k++)
			{
				if(i>>cnt&1)
				{
					e[j][k]=1;
					e[k][j]=0;
				}
				else
				{
					e[j][k]=0;
					e[k][j]=1;
				}
				cnt++;
			}
		}
		bool bk=true;
		for(int j=1;j<(1<<n)-1;j++)
		{
			bool bbk=true;
			for(int k=1;k<=n;k++)
			{
				if(j>>k-1&1)
				{
					for(int l=1;l<=n;l++)
					{
						if((j>>l-1&1)==0)
						{
							if(e[k][l]==0){bbk=false;break;}
						}
					}
					if(bbk==false)break;
				}
			}
			if(bbk){bk=false;break;}
		}
		if(bk)
		{
			for(int j=1;j<=n;j++)
			{
				for(int k=1;k<=n;k++)
				{
					if(k<=j)putchar(' ');
					else printf("%d",e[j][k]);
				}
				putchar('\n');
			}
			putchar('\n');
		}
	}
	return 0;
}
