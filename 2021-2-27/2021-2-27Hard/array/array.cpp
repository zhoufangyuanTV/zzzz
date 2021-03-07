#include<cstdio>
#include<cstring>
using namespace std;
inline int lowbit(int x){return x&-x;}
int f[16384][16],g[16384],p[16385],pp[16385],a[16];
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)scanf("%d",&a[i]);
		g[0]=0;int plen=0;
		for(int i=0;i<1<<m-1;i++)
		{
			if(i>0)g[i]=g[i-lowbit(i)]+1;
			int k=g[i],l=g[i]+2;f[i][g[i]+1]=a[1];
			for(int j=2;j<=m;j++)
			{
				if((i|1<<j-2)==i)f[i][k--]=a[j];
				else f[i][l++]=a[j];
			}
			p[++plen]=i;
		}
		for(int i=2;i<=n;i++)
		{
			for(int i=1;i<=m;i++)
			{
				int x;scanf("%d",&x);
				a[x]=i;
			}
			int pplen=0;
			for(int j=1;j<=plen;j++)
			{
				bool bk=true,bbk=true;
				for(int k=2;k<=m;k++)
				{
					if(bk&&a[f[p[j]][k-1]]<a[f[p[j]][k]])bk=false;
					else if(!bk&&a[f[p[j]][k-1]]>a[f[p[j]][k]]){bbk=false;break;}
				}
				if(bbk)pp[++pplen]=p[j];
			}
			plen=pplen;
			for(int j=1;j<=plen;j++)p[j]=pp[j];
		}
		printf("%d\n",plen);
		if(plen>0)
		{
			int s=1;
			for(int i=2;i<=plen;i++)
			{
				bool bk;
				for(int j=1;j<=m;j++)
				{
					if(f[p[s]][j]<f[p[i]][j]){bk=false;break;}
					if(f[p[s]][j]>f[p[i]][j]){bk=true;break;}
				}
				if(bk)s=i;
			}
			for(int i=1;i<m;i++)printf("%d ",f[p[s]][i]);
			printf("%d\n",f[p[s]][m]);
		}
	}
	return 0;
}