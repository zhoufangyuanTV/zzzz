#include<cstdio>
#include<cstring>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
int f[310][310][310];
int V[310][310],E[310][310],EE[310][310],F[310][310];
long long tong[310000];
int plen,p[310];
char a[310][310];
bool b[310][310];
int l,r,u,d;
void dfs(int x,int y)
{
	if(x<u)u=x;
	if(x>d)d=x;
	if(y<l)l=y;
	if(y>r)r=y;
	b[x][y]=false;
	for(int i=0;i<=3;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(b[xx][yy])dfs(xx,yy);
	}
}
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("village.in","r",stdin);
	freopen("village.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	memset(b,false,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='0')b[i][j]=true;
		}
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(b[i][j])
			{
				l=m;r=1;u=n;d=1;
				dfs(i,j);
				f[l-1][r+1][d+1]=mymax(f[l-1][r+1][d+1],u-1);
			}
		}
	}
	for(r=1;r<=m;r++)
	{
		for(l=r;l>=1;l--)
		{
			for(u=1;u<=n;u++)
			{
				f[l][r][u]=mymax(mymax(f[l][r][u],f[l][r][u-1]),mymax(f[l+1][r][u],f[l][r-1][u]));
			}
		}
	}
	memset(V,0,sizeof(V));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			V[i][j]=V[i-1][j]+V[i][j-1]-V[i-1][j-1];
			E[i][j]=E[i-1][j]+E[i][j-1]-E[i-1][j-1];
			EE[i][j]=EE[i-1][j]+EE[i][j-1]-EE[i-1][j-1];
			F[i][j]=F[i-1][j]+F[i][j-1]-F[i-1][j-1];
			if(a[i][j]=='1')
			{
				V[i][j]++;
				if(i>1&&a[i-1][j]=='1')E[i][j]++;
				if(j>1&&a[i][j-1]=='1')EE[i][j]++;
				if(i>1&&a[i-1][j]=='1'&&j>1&&a[i][j-1]=='1'&&a[i-1][j-1]=='1')F[i][j]++;
			}
		}
	}
	long long ss=0;
	for(l=1;l<=m;l++)
	{
		for(r=l;r<=m;r++)
		{
			u=0;plen=0;
			for(d=1;d<=n;d++)
			{
				int s=V[d-1][r]-V[d-1][l-1]-E[d][r]+E[d][l-1]-EE[d-1][r]+EE[d-1][l]+F[d][r]-F[d][l];
				tong[s+100000]++;
				plen++;p[plen]=s+100000;
				while(u<f[l][r][d])
				{
					u++;
					int sr=V[u-1][r]-V[u-1][l-1]-E[u][r]+E[u][l-1]-EE[u-1][r]+EE[u-1][l]+F[u][r]-F[u][l];
					tong[sr+100000]--;
				}
				s=V[d][r]-V[d][l-1]-E[d][r]+E[d][l-1]-EE[d][r]+EE[d][l]+F[d][r]-F[d][l];
				int gs=s-1+100000;
				if(gs>=0)ss=ss+tong[gs];
			}
			for(int i=1;i<=plen;i++)tong[p[i]]=0;
			plen=0;
		}
	}
	printf("%lld\n",ss);
	return 0;
}