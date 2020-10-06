#pragma GCC optimize("Ofast")
#include<ctime>
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
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
map<int,set<int>> MS[1010000];
int f[1010000],s[1010000];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int a[1100][1100];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	clock_t t0,t1,t2,t3;
	t0=clock();
	int n,m,q,k;read(n);read(m);read(q);read(k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			read(a[i][j]);
			f[(i-1)*m+j]=(i-1)*m+j;
			s[(i-1)*m+j]=1;
			if(i>1&&a[i][j]==a[i-1][j])
			{
				int ff=find((i-2)*m+j);
				f[ff]=(i-1)*m+j;
				s[(i-1)*m+j]+=s[ff];
			}
			if(j>1&&a[i][j]==a[i][j-1])
			{
				int ff=find((i-1)*m+j-1);
				f[ff]=(i-1)*m+j;
				s[(i-1)*m+j]+=s[ff];
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)find((i-1)*m+j);
	}
	t1=clock();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i>1&&a[i][j]!=a[i-1][j])
			{
				MS[f[(i-1)*m+j]][a[i-1][j]].insert(f[(i-2)*m+j]);
			}
			if(j>1&&a[i][j]!=a[i][j-1])
			{
				MS[f[(i-1)*m+j]][a[i][j-1]].insert(f[(i-1)*m+j-1]);
			}
			if(i<n&&a[i][j]!=a[i+1][j])
			{
				MS[f[(i-1)*m+j]][a[i+1][j]].insert(f[i*m+j]);
			}
			if(j<m&&a[i][j]!=a[i][j+1])
			{
				MS[f[(i-1)*m+j]][a[i][j+1]].insert(f[(i-1)*m+j+1]);
			}
		}
	}
	t2=clock();
	for(int i=1;i<=q;i++)
	{
		int x;read(x);
		set<int> &S=MS[f[1]][x];
		for(set<int>::iterator it=S.begin();it!=S.end();it++)
		{
			f[*it]=f[1];
			s[f[1]]+=s[*it];
			for(map<int,set<int>>::iterator jt=MS[*it].begin();jt!=MS[*it].end();jt++)
			{
				for(set<int>::iterator kt=(*jt).second.begin();kt!=(*jt).second.end();kt++)
				{
					if(f[f[*kt]]==f[1])continue;
					MS[f[1]][(*jt).first].insert(*kt);
				}
			}
		}
		MS[f[1]].erase(x);
		write(s[1]);
	}
	t3=clock();
	fprintf(stderr,"%lf\n",double(t3-t0)/CLOCKS_PER_SEC);
	fprintf(stderr,"%lf %lf %lf\n",double(t1-t0)/CLOCKS_PER_SEC,double(t2-t1)/CLOCKS_PER_SEC,double(t3-t2)/CLOCKS_PER_SEC);
	return 0;
}