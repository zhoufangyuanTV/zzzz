#include<cstdio>
#include<cstring>
using namespace std;
int a[110];
long long b[110][110];
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			long long ss=0;
			for(int k=i;k<=j;k++)ss+=a[k];
			b[i][j]=ss;
		}
	}
	while(m--)
	{
		int op;scanf("%d",&op);
		if(op==1)
		{
			int p,x;scanf("%d%d",&p,&x);
			a[p]=x;
			for(int i=1;i<=n;i++)
			{
				for(int j=i;j<=n;j++)
				{
					long long ss=0;
					for(int k=i;k<=j;k++)ss+=a[k];
					if(ss<b[i][j])b[i][j]=ss;
				}
			}
		}
		else
		{
			int l,r;scanf("%d%d",&l,&r);
			printf("%lld\n",b[l][r]);
		}
	}
	return 0;
}