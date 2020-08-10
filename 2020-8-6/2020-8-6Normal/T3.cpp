#include<cstdio>
#include<cstring>
using namespace std;
int f[2097152],g[2097152],map[151][11],fu[78733],gu[78733];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m,k;scanf("%d%d%d",&n,&m,&k);
		memset(map,0,sizeof(map));
		for(int i=1;i<=k;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			map[x][y]=1;
		}
		memset(f,-1,sizeof(f));f[(1<<2*m+1)-1]=0;
		fu[0]=1;fu[1]=(1<<2*m+1)-1;
		memset(g,-1,sizeof(g));gu[0]=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=fu[0];j++)
			{
				int w=f[fu[j]],v=fu[j]>>1;
				if(map[i][1]==1)v|=1|1<<m|1<<2*m;
				if(g[v]==-1)gu[++gu[0]]=v;
				g[v]=mymax(g[v],w);
			}
			fu[0]=gu[0];
			while(gu[0]>0)
			{
				f[gu[gu[0]]]=g[gu[gu[0]]];
				fu[gu[0]]=gu[gu[0]];
				g[gu[gu[0]]]=-1;
				gu[0]--;
			}
			for(int j=2;j<=m;j++)
			{
				for(int k=1;k<=fu[0];k++)
				{
					int w=f[fu[k]],u=fu[k],v=fu[k]>>1;
					if(map[i][j]==1)v|=1|1<<m|1<<2*m;
					if(g[v]==-1)gu[++gu[0]]=v;
					g[v]=mymax(g[v],w);
					if(!(u&1)&&!(u&2)&&map[i][j]==0)
					{
						int vv=v;vv|=1|1<<m-1|1<<m|1<<2*m-1|1<<2*m;
						if(g[vv]==-1)gu[++gu[0]]=vv;
						g[vv]=mymax(g[vv],w+1);
					}
					if(j>2&&!(u&1<<m-1)&&!(u&1<<m)&&!(u&1<<m+1)&&map[i][j]==0)
					{
						int vv=v;vv|=1|1<<m-2|1<<m-1|1<<m|1<<2*m-2|1<<2*m-1|1<<2*m;
						if(g[vv]==-1)gu[++gu[0]]=vv;
						g[vv]=mymax(g[vv],w+1);
					}
				}
				fu[0]=gu[0];
				while(gu[0]>0)
				{
					f[gu[gu[0]]]=g[gu[gu[0]]];
					fu[gu[0]]=gu[gu[0]];
					g[gu[gu[0]]]=-1;
					gu[0]--;
				}
			}
		}
		int ss=0;
		for(int i=1;i<=fu[0];i++)ss=mymax(ss,f[fu[i]]);
		printf("%d\n",ss);
	}
	return 0;
}