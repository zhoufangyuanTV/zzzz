#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int son[2],size;
}tr[18010000];int len;
long long a[310000];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("inception.in","r",stdin);
	freopen("inception.out","w",stdout);
	int n;long long x;scanf("%*d%d%lld",&n,&x);
	long long p=1;int t=0;
	while(p<=x)p<<=1,t++;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	if(x==0)
	{
		printf("%lld\n",(ksm(2,n)+998244352)%998244353);
		return 0;
	}
	sort(a+1,a+n+1);
	long long ss=1;
	for(int i=1;i<=n;i++)
	{
		int l1=i,r1,l2,r2;
		while(i<n&&a[l1]>>t-1==a[i+1]>>t-1)i++;
		r1=i;
		l2=i+1;
		while(i<n&&a[l1]>>t==a[i+1]>>t&&a[l1]>>t-1!=a[i+1]>>t-1)i++;
		r2=i;
		long long s=r2-l1+2;
		len=0;
		tr[0].son[0]=tr[0].son[1]=0;
		tr[0].size=0;
		for(int j=l1;j<=r1;j++)
		{
			int now=0;
			tr[now].size++;
			for(int k=t-2;k>=0;k--)
			{
				int c=a[j]>>k&1;
				if(tr[now].son[c]==0)
				{
					tr[now].son[c]=++len;
					tr[len].son[0]=tr[len].son[1]=0;
					tr[len].size=0;
				}
				now=tr[now].son[c];
				tr[now].size++;
			}
		}
		for(int j=l2;j<=r2;j++)
		{
			int now=0;
			bool bk=true;
			for(int k=t-2;k>=0;k--)
			{
				int c=a[j]>>k&1,cc=x>>k&1;
				if(cc==0)
				{
					if(tr[now].son[c^1]!=0)s+=tr[tr[now].son[c^1]].size;
					now=tr[now].son[c];
				}
				else now=tr[now].son[c^1];
				if(now==0){bk=false;break;}
			}
			if(bk==true)s+=tr[now].size;
		}
		ss=s%998244353*ss%998244353;
	}
	printf("%lld\n",(ss+998244352)%998244353);
	return 0;
}