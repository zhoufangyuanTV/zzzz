#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int mmp[1100][1100];
int fa[1100];
int findfa(int x){return fa[x]!=x?fa[x]=findfa(fa[x]):x;}
int x[310000],y[310000],len;
int main(int argc,char* argv[])
{
	int se=1;
	sscanf(argv[1],"%d",&se);
	srand(se);
	freopen("in","w",stdout);
	memset(mmp,0,sizeof(mmp));
	len=0;
	int n=500,m=124750;
	for(int i=0;i<n;i++)mmp[i][i]=1;
	for(int i=0;i<n;i++)fa[i]=i;
	for(int i=1;i<n;i++)
	{
		int xx=rand()%n,yy=rand()%n;
		int fx=findfa(xx),fy=findfa(yy);
		while(fx==fy)
		{
			xx=rand()%n,yy=rand()%n;
			fx=findfa(xx),fy=findfa(yy);
		}
		x[len]=xx;y[len]=yy;
		fa[fx]=fy;
		mmp[xx][yy]=mmp[yy][xx]=1;
		len++;
	}
	for(int i=n;i<=m;i++)
	{
		int xx=rand()%n,yy=rand()%n;
		while(mmp[xx][yy]==1)xx=rand()%n,yy=rand()%n;
		x[len]=xx;y[len]=yy;
		mmp[xx][yy]=mmp[yy][xx]=1;
		len++;
	}
	printf("%d %d\n",n,m);
	for(int i=0;i<m;i++)printf("%d %d\n",x[i],y[i]);
	for(int i=0;i<n-1;i++)printf("%d ",i);
	return 0;
}