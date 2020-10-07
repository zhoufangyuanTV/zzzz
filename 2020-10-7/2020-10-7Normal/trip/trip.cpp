#include<cstdio>
#include<cstring>
using namespace std;
int f[110][11000];
int g[110][110],gg[110][110];
int h[110][110][17];
int p[110],c[110];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
	int n,m,C,T;scanf("%d%d%d%d",&n,&m,&C,&T);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i],&c[i]);
		if(c[i]>C)c[i]=C;
	}
	memset(h,-1,sizeof(h));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		h[x][y][0]=c;
	}
	for(int i=1;1<<i<=C;i++)
	{
		for(int x=1;x<=n;x++)
		{
			for(int y=1;y<=n;y++)
			{
				h[x][y][i]=h[x][y][i-1];
			}
		}
		for(int x=1;x<=n;x++)
		{
			for(int y=1;y<=n;y++)
			{
				if(h[x][y][i-1]!=-1)
				{
					for(int z=1;z<=n;z++)
					{
						if(h[y][z][i-1]!=-1)
						{
							h[x][z][i]=mymax(h[x][z][i],h[x][y][i-1]+h[y][z][i-1]);
						}
					}
				}
			}
		}
	}
	memset(g,-1,sizeof(g));
	for(int i=1;i<=n;i++)g[i][i]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;1<<j<=c[i];j++)
		{
			if(c[i]>>j&1)
			{
				for(int x=1;x<=n;x++)gg[i][x]=g[i][x];
				for(int x=1;x<=n;x++)
				{
					if(gg[i][x]!=-1)
					{
						for(int y=1;y<=n;y++)
						{
							if(h[x][y][j]!=-1)g[i][y]=mymax(g[i][y],gg[i][x]+h[x][y][j]);
						}
					}
				}
			}
		}
	}
	memset(f,-1,sizeof(f));
	for(int i=1;i<=n;i++)f[i][0]=0;
	for(int i=0;i<=n*n;i++)
	{
		if(i>0)
		{
			for(int j=1;j<=n;j++)f[j][i]=mymax(f[j][i],f[j][i-1]);
		}
		for(int j=1;j<=n;j++)
		{
			if(i+p[j]<=n*n)
			{
				for(int k=1;k<=n;k++)
				{
					if(g[j][k]!=-1)f[j][i+p[j]]=mymax(f[j][i+p[j]],f[k][i]+g[j][k]);
				}
			}
		}
	}
	while(T--)
	{
		int s,q,d;scanf("%d%d%d",&s,&q,&d);
		if(f[s][q]<d)
		{
			printf("-1\n");
			continue;
		}
		int l=0,r=q;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(f[s][mid]>=d)r=mid;
			else l=mid+1;
		}
		printf("%d\n",q-r);
	}
	return 0;
}