#include<cstdio>
#include<cstring>
using namespace std;
int popcnt[1024];
int len,a[1024];
int n,m,f,cnt[21];
long long ss;
void dfs(int k)
{
	if(k==n+1)
	{
		for(int i=1;i<=m;i++)if(cnt[i]!=f)break;
		ss++;
	}
	else
	{
		for(int i=1;i<=len;i++)
		{
			bool bk=true;
			for(int j=1;j<=m;j++)
			{
				if((a[i]|1<<j-1)==a[i])cnt[j]++;
				if(cnt[j]>f||cnt[j]+n-k<f)bk=false;
			}
			if(bk)dfs(k+1);
			for(int j=1;j<=m;j++)
			{
				if((a[i]|1<<j-1)==a[i])cnt[j]--;
			}
		}
	}
}
int main()
{
	freopen("algebra.in","r",stdin);
	freopen("algebra.out","w",stdout);
	scanf("%d%d%d",&n,&m,&f);
	popcnt[0]=0;
	if(f==0){len=1;a[1]=0;}
	else len=0;
	for(int i=1;i<1<<m;i++)
	{
		popcnt[i]=popcnt[i>>1]+(i&1);
		if(f==popcnt[i])a[++len]=i;
	}
	ss=0;
	dfs(1);
	printf("%lld\n",ss);
	return 0;
}
