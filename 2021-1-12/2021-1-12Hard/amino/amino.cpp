#include<cstdio>
#include<cstring>
using namespace std;
int to[512][512];
unsigned f[512][19683];
char opt[110],a[110];
int main()
{
	freopen("amino.in","r",stdin);
	freopen("amino.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	int A=n/2;
	int B=n-A;
	for(int i=0;i<1<<B;i++)
	{
		for(int j=0;j<1<<B;j++)
		{
			int y=0;
			for(int k=0,l=1;k<B;k++,l*=3)
			{
				if(j&1<<k)y+=2*l;
				else if(i&1<<k)y+=l;
			}
			to[i][j]=y;
		}
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s%s",opt+1,a);
		if(opt[1]=='I')
		{
			int x;scanf("%d",&x);
			int y=0,yy=0;
			for(int j=0;j<A;j++)y|=a[j]-'0'<<j;
			for(int j=A;j<n;j++)yy|=a[j]-'0'<<j-A;
			for(int j=0;j<1<<B;j++)f[y][to[yy][j]]+=x;
		}
		else
		{
			unsigned ss=0;
			int x=0,y=0,yy=0;
			for(int j=0,l=1;j<B;j++,l*=3)
			{
				if(a[A+j]=='*')yy+=2*l;
				else if(a[A+j]=='1')yy+=l;
			}
			for(int j=0;j<A;j++)
			{
				if(a[j]=='*')y|=1<<j;
				else if(a[j]=='1')x|=1<<j;
			}
			for(int j=y;j>0;j=j-1&y)ss+=f[x|j][yy];
			ss+=f[x][yy];
			printf("%u\n",ss);
		}
	}
	return 0;
}