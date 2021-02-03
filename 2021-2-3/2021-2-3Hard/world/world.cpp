#include<cstdio>
#include<cstring>
using namespace std;
char s[1100][1100],S[1100];
bool a[1100][1100],b[1100][1100],c[1100][1100],d[1100][1100],e[1100][1100];
int main()
{
	freopen("world.in","r",stdin);
	freopen("world.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",S+1);
			for(int j=1;j<=m;j++)a[i][j]=s[i][j]!=S[j];
		}
		bool bk=true;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)
			{
				for(int ii=i+1,jj=j+1;ii<=n&&jj<=m;ii+=2,jj+=2)
				{
					int k=a[i+1][j]^a[i][j+1]^a[ii-1][j]^a[ii][j+1]^a[i][jj-1]^a[i+1][jj]^a[ii-1][jj]^a[ii][jj-1];
					if(k==1){bk=false;break;}
				}
				if(bk==false)break;
			}
			if(bk==false)break;
		}
		puts(bk?"Yes":"No");
	}
	return 0;
}
