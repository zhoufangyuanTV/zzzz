#include<cstdio>
#include<cstring>
using namespace std;
char a[2100][2100];
bool b[2100];
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	if(n>2000&&m>2000)return 0;
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			for(int k=1;k<=m;k++)
			{
				b[k]=true;
				for(int l=i;l<=j;l++)
				{
					if(a[l][k]=='#'){b[k]=false;break;}
				}
			}
			for(int k=1;k<=m;k++)
			{
				if(b[k])
				{
					for(int l=k+1;l<=m;l++)
					{
						if(a[i][l]=='#'||a[j][l]=='#')break;
						if(b[l])ss++;
					}
				}
			}
		}
	}
	printf("%lld\n",ss);
	return 0;
}