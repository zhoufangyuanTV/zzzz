#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[110000];int len,last[51000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
long long c[51000];
long long ksm(long long x,long long k)
{
	long long s=0;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("centroid.in","r",stdin);
	freopen("centroid.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	if(m==1)
	{
		long long ss=0;
		for(int i=1;i<=n;i++)ss=(ss+c[i])%1000000007;
		printf("%lld\n",ss);
		return 0;
	}
	if(m==2)
	{
		long long ss=0;
		for(int i=1;i<n;i++)
		{
			if(a[i*2].x<a[i*2].y)ss=(ss+c[a[i*2].x])%1000000007;
			else ss=(ss+c[a[i*2].y])%1000000007;
		}
		printf("%lld\n",ss);
		return 0;
	}
	if(m==3)
	{
		long long ss=0;
		for(int x=1;x<=n;x++)
		{
			long long s=0;
			for(int k=last[x];k>0;k=a[k].next)s++;
			ss=(ss+c[x]*s%1000000007*(s-1)%1000000007*500000004%1000000007)%1000000007;
		}
		printf("%lld\n",ss);
		return 0;
	}
	bool A=false;int p;
	for(int i=1;i<=n;i++)
	{
		int s=0;
		for(int k=last[i];k>0;k=a[k].next)s++;
		if(s==n-1){A=true;p=i;break;}
	}
	if(A)
	{
		long long ss=c[p];
		for(int i=n-1;i>=n-m+1;i--)ss=ss*i%1000000007;
		for(int i=1;i<m;i++)ss=ss*ksm(i,1000000005)%1000000007;
		printf("%lld\n",ss);
		return 0;
	}
}