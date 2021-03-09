#include<cstdio>
#include<cstring>
using namespace std;
inline int lowbit(int x){return x&-x;}
int n,a[110000];long long c[110000];
inline void change(int x,int s)
{
	while(x<=n)
	{
		c[x]+=s;
		x+=lowbit(x);
	}
}
inline long long sum(int x)
{
	long long s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
int main()
{
	int m,p;scanf("%d%d%d",&n,&m,&p);
	a[0]=0;for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)a[i]=(a[i]-a[i-1]+p)%p;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
	{
		c[i]+=a[i];
		if(i+lowbit(i)<=n)c[i+lowbit(i)]+=c[i];
	}
	for(int i=1;i<=m;i++)
	{
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if(opt==1)
		{
			int cc;scanf("%d",&cc);
			int cl=(a[l]+cc)%p,cr=(a[r+1]-cc%p+p)%p;
			change(l,cl-a[l]);change(r+1,cr-a[r+1]);
			a[l]=cl;a[r+1]=cr;
		}
		else printf("%lld\n",sum(r)/p-sum(l)/p);
	}
	return 0;
}