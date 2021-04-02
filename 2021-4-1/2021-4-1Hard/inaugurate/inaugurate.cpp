#include<cstdio>
#include<cstring>
using namespace std;
int a[51000];
int f[51000][2],g[51000][2];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("inaugurate.in","r",stdin);
	freopen("inaugurate.out","w",stdout);
	int id,n,m;scanf("%d%d%d",&id,&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	if(id==1)
	{
		for(int i=1;i<=m;i++)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			f[0][0]=0;f[0][1]=-1061109568;
			for(int j=1;j<=x;j++)f[j][0]=f[j][1]=-1061109568;
			for(int j=l;j<=r;j++)
			{
				for(int k=0;k<=x;k++)
				{
					g[k][0]=f[k][0];g[k][1]=f[k][1];
					f[k][0]=f[k][1]=-1061109568;
				}
				for(int k=0;k<=x;k++)
				{
					f[k][0]=mymax(g[k][0],g[k][1]);
					f[k][1]=g[k][1];
					if(k>0)f[k][1]=mymax(f[k][1],mymax(g[k-1][0],g[k-1][1]));
					f[k][1]=f[k][1]+a[j];
				}
			}
			printf("%d\n",mymax(f[x][0],f[x][1]));
		}
		return 0;
	}
	if(id==2||id==3)
	{
		f[0][0]=0;f[0][1]=-1061109568;
		for(int j=1;j<=n;j++)f[j][0]=f[j][1]=-1061109568;
		for(int j=1;j<=n;j++)
		{
			for(int k=0;k<=n;k++)
			{
				g[k][0]=f[k][0];g[k][1]=f[k][1];
				f[k][0]=f[k][1]=-1061109568;
			}
			for(int k=0;k<=n;k++)
			{
				f[k][0]=mymax(g[k][0],g[k][1]);
				f[k][1]=g[k][1];
				if(k>0)f[k][1]=mymax(f[k][1],mymax(g[k-1][0],g[k-1][1]));
				f[k][1]=f[k][1]+a[j];
			}
		}
		for(int i=1;i<=m;i++)
		{
			int x;scanf("%*d%*d%d",&x);
			printf("%d\n",mymax(f[x][0],f[x][1]));
		}
		return 0;
	}
	if(id==6)
	{
		a[0]=0;
		for(int i=2;i<=n;i++)a[i]+=a[i-1];
		for(int i=1;i<=m;i++)
		{
			int l,r;scanf("%d%d%*d",&l,&r);
			printf("%d\n",a[r]-a[l-1]);
		}
		return 0;
	}
	return 0;
}