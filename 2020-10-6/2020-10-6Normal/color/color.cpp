#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
void write(int x)
{
	int y=10;
	while(y<=x)y=y*10;
	while(y!=1){y=y/10;putchar(x/y+'0');x=x%y;}
	putchar('\n');
}
int f[1010000];vector<int> s[1010000];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int a[1100][1100];
vector<int> MS[1010000];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int n,m,q,k;read(n);read(m);read(q);read(k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			read(a[i][j]);
			f[(i-1)*m+j]=(i-1)*m+j;
			if(i>1&&a[i][j]==a[i-1][j])f[find((i-2)*m+j)]=(i-1)*m+j;
			if(j>1&&a[i][j]==a[i][j-1])f[find((i-1)*m+j-1)]=(i-1)*m+j;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)s[find((i-1)*m+j)].push_back((i-1)*m+j);
	}
	for(int ij:s[f[1]])
	{
		int i=(ij-1)/m+1,j=(ij-1)%m+1;
		if(i>1&&f[ij-m]!=f[1])MS[a[i-1][j]].push_back(f[ij-m]);
		if(j>1&&f[ij-1]!=f[1])MS[a[i][j-1]].push_back(f[ij-1]);
		if(i<n&&f[ij+m]!=f[1])MS[a[i+1][j]].push_back(f[ij+m]);
		if(j<m&&f[ij+1]!=f[1])MS[a[i][j+1]].push_back(f[ij+1]);
	}
	int ss=s[f[1]].size();
	for(int i=1;i<=q;i++)
	{
		int x;read(x);
		for(int it:MS[x])
		{
			if(f[it]!=f[1])
			{
				f[it]=f[1];
				for(int ij:s[it])
				{
					ss++;
					int i=(ij-1)/m+1,j=(ij-1)%m+1;
					if(i>1&&f[f[ij-m]]!=f[1])MS[a[i-1][j]].push_back(f[ij-m]);
					if(j>1&&f[f[ij-1]]!=f[1])MS[a[i][j-1]].push_back(f[ij-1]);
					if(i<n&&f[f[ij+m]]!=f[1])MS[a[i+1][j]].push_back(f[ij+m]);
					if(j<m&&f[f[ij+1]]!=f[1])MS[a[i][j+1]].push_back(f[ij+1]);
				}
			}
		}
		MS[x].clear();
		write(ss);
	}
	return 0;
}