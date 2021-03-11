#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
bitset<101> a[110][110];
int f[110][110],g[110][110];
inline void pl(int &x,int y){x+y<1000000007?x+=y:x+=y-1000000007;}
int main()
{
	freopen("roche.in","r",stdin);
	freopen("roche.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m,q;scanf("%d%d%d",&n,&m,&q);
		if(n*m>40000)return 0;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j].reset();
		for(int i=1;i<=q;i++)
		{
			int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			for(int x=x1;x<=x2;x++)
			{
				for(int y=y1;y<=y2;y++)a[x][y].set(i);
			}
		}
		int s=0,ss=0;
		for(int i=n;i>=1;i--)
		{
			for(int j=m;j>=1;j--)
			{
				f[i][j]=1;g[i][j]=1;
				for(int k=i+1;k<=n;k++)
				{
					for(int l=j+1;l<=m;l++)
					{
						if((a[i][j]&a[k][l]).any())
						{
							if(f[i][j]<f[k][l]+1)f[i][j]=f[k][l]+1,g[i][j]=g[k][l];
							else if(f[i][j]==f[k][l]+1)pl(g[i][j],g[k][l]);
						}
					}
				}
				if(s<f[i][j])s=f[i][j],ss=g[i][j];
				else if(s==f[i][j])pl(ss,g[i][j]);
			}
		}
		printf("%d %d\n",s,ss);
	}
	return 0;
}