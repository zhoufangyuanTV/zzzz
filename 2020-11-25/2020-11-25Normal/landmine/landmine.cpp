#include<cstdio>
#include<cstring>
using namespace std;
long long f[1<<20];
inline long long mymax(long long x,long long y){return x>y?x:y;}
long long p[110],q[110],r[110],s[110];
int plen,a[110];
int main()
{
	freopen("landmine.in","r",stdin);
	freopen("landmine.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&p[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&q[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&r[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
	memset(f,0,sizeof(f));
	for(int i=1;i<1<<n;i++)
	{
		plen=0;
		for(int j=1;j<=n;j++)if((i|1<<j-1)==i)a[++plen]=j;
		a[0]=0;a[plen+1]=0;a[plen+2]=0;
		for(int j=1;j<=plen;j++)
		{
			f[i]=mymax(f[i],f[i-(1<<a[j]-1)]+(p[a[j-1]]-q[a[j]])*(p[a[j-1]]-q[a[j]])+(p[a[j]]-r[a[j+1]])*(p[a[j]]-r[a[j+1]])+(p[a[j+1]]-s[a[j+2]])*(p[a[j+1]]-s[a[j+2]]));
		}
	}
	printf("%lld\n",f[(1<<n)-1]);
	return 0;
}