#include<cstdio>
#include<cstring>
using namespace std;
long long jc[110];
int a[110][110],f[110],ff[110],cnt[110],cntt[110];
int find(int x){return f[x]!=x?f[x]=find(f[x]):x;}
int ffind(int x){return ff[x]!=x?ff[x]=ffind(ff[x]):x;}
int main()
{
	jc[0]=1;
	for(int i=1;i<=100;i++)jc[i]=jc[i-1]*i%998244353;
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
	}
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		for(int j=1;j<i;j++)
		{
			bool bk=true;
			for(int k=1;k<=n;k++)
			{
				if(a[i][k]+a[j][k]>m){bk=false;break;}
			}
			if(bk)f[find(j)]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		ff[i]=i;
		for(int j=1;j<i;j++)
		{
			bool bk=true;
			for(int k=1;k<=n;k++)
			{
				if(a[k][i]+a[k][j]>m){bk=false;break;}
			}
			if(bk)ff[ffind(j)]=i;
		}
	}
	memset(cnt,0,sizeof(cnt));
	memset(cntt,0,sizeof(cntt));
	for(int i=1;i<=n;i++)cnt[find(i)]++,cntt[ffind(i)]++;
	long long ss=1;
	for(int i=1;i<=n;i++)
	{
		ss=ss*jc[cnt[i]]%998244353*jc[cntt[i]]%998244353;
	}
	printf("%lld\n",ss);
	return 0;
}