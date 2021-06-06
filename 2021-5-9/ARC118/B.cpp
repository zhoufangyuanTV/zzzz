#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long a[110000],b[110000];
struct node
{
	long long x;int p;
}c1[110000],c2[110000];
inline bool cmp(node x,node y){return x.x<y.x;}
int main()
{
	int k;long long n,m;scanf("%d%lld%lld",&k,&n,&m);
	for(int i=1;i<=k;i++)scanf("%lld",&a[i]);
	int l1=0,l2=0;
	long long s=0;
	for(int i=1;i<=k;i++)
	{
		b[i]=m*a[i]/n;
		long long dl=a[i]*m-b[i]*n,dr=(b[i]+1)*n-a[i]*m;
		if(dl<dr)
		{
			l1++;
			c1[l1].x=dr;
			c1[l1].p=i;
		}
		else
		{
			b[i]++;
			l2++;
			c2[l2].x=dl;
			c2[l2].p=i;
		}
		s+=b[i];
	}
	if(s==m)
	{
		for(int i=1;i<=k;i++)printf("%lld ",b[i]);
	}
	else if(s<m)
	{
		sort(c1+1,c1+l1+1,cmp);
		for(int i=1;i<=m-s;i++)
		{
			b[c1[i].p]++;
		}
		for(int i=1;i<=k;i++)printf("%lld ",b[i]);
	}
	else if(s>m)
	{
		sort(c2+1,c2+l2+1,cmp);
		for(int i=1;i<=s-m;i++)
		{
			b[c2[i].p]--;
		}
		for(int i=1;i<=k;i++)printf("%lld ",b[i]);
	}
	return 0;
}