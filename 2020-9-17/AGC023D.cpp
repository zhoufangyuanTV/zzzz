#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
long long x[110000],p[110000];
int main()
{
	long long n,s;scanf("%lld%lld",&n,&s);
	for(int i=1;i<=n;i++)scanf("%lld %lld",&x[i],&p[i]);
	long long ss=0,l=1,r=n,ed=-1;
	while(l<=r)
	{
		if(x[r]<s){ss+=s-x[l];break;}
		if(s<x[l]){ss+=x[r]-s;break;}
		if(p[l]<p[r])
		{
			p[r]+=p[l];
			if(ed!=-1)ss+=abs(x[r]-ed);
			ed=x[r];
			l++;
		}
		else
		{
			p[l]+=p[r];
			if(ed!=-1)ss+=abs(x[l]-ed);
			ed=x[l];
			r--;
		}
	}
	printf("%lld\n",ss+(ed!=-1?x[n]-x[1]:0));
	return 0;
}