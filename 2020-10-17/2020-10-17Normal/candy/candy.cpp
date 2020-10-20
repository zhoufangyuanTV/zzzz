#include<cstdio>
#include<cstring>
using namespace std;
int f[110000];
int main()
{
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			int a,b,k;scanf("%d%d%d",&a,&b,&k);
			f[b]=0;
			for(int j=b-1;j>=a;j--)
			{
				if(f[j+1]!=0&&(j*k>n||f[j*k]!=0))f[j]=0;
				else if(f[j+1]!=1&&(j*k>n||f[j*k]!=1))f[j]=1;
				else f[j]=2;
			}
			ss=ss^f[a];
		}
		puts(ss?"Alice":"Bob");
	}
	return 0;
}