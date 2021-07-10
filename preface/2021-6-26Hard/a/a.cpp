#include<cstdio>
#include<cstring>
using namespace std;
int f[110000][3],a[110000];
void solve(int l,int r)
{
	int c=f[r][3-a[l]-a[r]];
	if(c-l>1)
	{
		if(f[c][a[r]]<l)
		{
			for(int i=l+1;i<c;i++)printf("%d %d\n",i,r);
		}
		else
		{
			printf("%d %d\n",l,c);
			solve(l,c);
		}
	}
	if(r-c>1)
	{
		printf("%d %d\n",c,r);
		solve(c,r);
	}
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;scanf("%d",&n);
	f[0][0]=f[0][1]=f[0][2]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f[i][0]=f[i-1][0];
		f[i][1]=f[i-1][1];
		f[i][2]=f[i-1][2];
		f[i][a[i]]=i;
		if(i>1&&a[i-1]==a[i])
		{
			puts("no");
			return 0;
		}
	}
	if(a[1]==a[n]||f[n][0]==0||f[n][1]==0||f[n][2]==0)
	{
		puts("no");
		return 0;
	}
	puts("yes");
	solve(1,n);
	return 0;
}
