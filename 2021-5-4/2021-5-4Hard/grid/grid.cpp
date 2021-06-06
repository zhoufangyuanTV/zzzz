#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int e[601][601][6];
int Ans[601][601];
int p[601][601],v[601][601];
bool b[601][601];
int sta[601];
int match[601];
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int n,m;read(n);read(m);
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			for(register int k=1;k<=m-n;k++)read(e[i][j][k]);
			sort(e[i][j]+1,e[i][j]+m-n+1);
			e[i][j][0]=1;
		}
	}
	for(register int c=1;c<=m;c++)
	{
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=n;j++)
			{
				if(Ans[i][j]!=0)b[i][j]=false;
				else if(e[i][j][0]<=m-n&&e[i][j][e[i][j][0]]==c)
				{
					b[i][j]=false;
					e[i][j][0]++;
				}
				else b[i][j]=true;
			}
		}
		for(register int i=1;i<=n;i++)
		{
			p[i][0]=1;
			register int k=0,kk=n;
			for(register int j=i-1;j>=1;j--)
			{
				if(b[i][j])p[i][++k]=j;
				else p[i][kk--]=j;
			}
			for(register int j=n;j>=i;j--)
			{
				if(b[i][j])p[i][++k]=j;
				else p[i][kk--]=j;
			}
		}
		for(register int j=1;j<=n;j++)
		{
			register int k=0,kk=n;
			for(register int i=j;i>=1;i--)
			{
				if(b[i][j])v[i][j]=++k;
				else v[i][j]=kk--;
			}
			for(register int i=n;i>j;i--)
			{
				if(b[i][j])v[i][j]=++k;
				else v[i][j]=kk--;
			}
		}
		register int top=n;
		for(register int i=1;i<=n;i++)sta[i]=i,match[i]=0;
		while(top>0)
		{
			register int x=sta[top--];
			for(;p[x][0]<=n;p[x][0]++)
			{
				register int y=p[x][p[x][0]];
				if(match[y]==0){match[y]=x;break;}
				else
				{
					if(v[x][y]<v[match[y]][y]){sta[++top]=match[y];p[match[y]][0]++;match[y]=x;break;}
				}
			}
		}
		for(register int j=1;j<=n;j++)
		{
			if(b[match[j]][j])Ans[match[j]][j]=c;
		}
	}
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<n;j++)
		{
			printf("%d ",Ans[i][j]);
		}
		printf("%d\n",Ans[i][n]);
	}
	return 0;
}