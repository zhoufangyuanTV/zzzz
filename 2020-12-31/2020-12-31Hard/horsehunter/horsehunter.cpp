#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void write(long long x)
{
	long long y=10;
	while(y<=x)y=y*10;
	while(y!=1){y=y/10;putchar(x/y+'0');x=x%y;}
	putchar('\n');
}
int n,a[1010000];
long long ss;
void dfs(int k,long long s)
{
	if(k==n+1)
	{
		if(ss<s)ss=s;
	}
	else
	{
		if(a[k]==0)dfs(k+1,s);
		for(int i=k;i<=n+1;i++)
		{
			if(a[i]==0)
			{
				for(int j=k;j<i;j++)a[j]++;
				break;
			}
			a[i]--;
			dfs(k,s+(k^i));
		}
	}
}
int main()
{
	freopen("horsehunter.in","r",stdin);
	freopen("horsehunter.out","w",stdout);
	int m;read(n);read(m);
	for(int i=1;i<=n;i++)read(a[i]);a[n+1]=0;
	ss=0;dfs(1,0);write(ss);
	for(int i=1;i<=m;i++)
	{
		int x;read(x);read(a[x]);
		ss=0;dfs(1,0);write(ss);
	}
	return 0;
}