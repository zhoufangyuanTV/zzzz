#include<cstdio>
#include<cstring>
using namespace std;
int a[1010000],aa[1010000];
int p[1010000],g[1010000];
bool d[1010000];
int main()
{
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
	int t,n;scanf("%d",&t);
	for(int tt=1;tt<=t;tt++)
	{
		if(tt==1)
		{
			scanf("%d",&n);
			for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		}
		else
		{
			int tk;scanf("%d",&tk);
			for(int i=1;i<=tk;i++)
			{
				int x,y;scanf("%d%d",&x,&y);
				a[x]=y;
			}
		}
		for(int i=1;i<=n;i++)aa[i]=a[i];
		for(int i=1;i<n;i++)
		{
			int ap=-1,ip=-1;
			for(int j=1;j<=n;j++)
			{
				if(a[j]==-1)continue;
				if(ap==-1)ap=ip=j;
				if(a[j]>=a[ap])ap=j;
				if(a[j]<a[ip])ip=j;
			}
			p[i]=ap;g[i]=ip;
			a[ap]-=a[ip];
			a[ip]=-1;
		}
		for(int i=1;i<=n;i++)d[i]=false;
		for(int i=n-1;i>=1;i--)
		{
			if(d[p[i]]==true)
			{
				for(int i=1;i<=n;i++)d[i]=false;
			}
			else d[g[i]]=true;
		}
		int ss=0;
		for(int i=1;i<=n;i++)if(d[i]==false)ss++;
		printf("%d\n",ss);
		for(int i=1;i<=n;i++)a[i]=aa[i];
	}
	return 0;
}
