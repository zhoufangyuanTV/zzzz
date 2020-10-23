#include<cstdio>
#include<cstring>
using namespace std;
int n,a[310000];
bool pand(int x)
{
	int ss=0;
	for(int i=0;i<=n;ss+=a[i+1]-a[i],i+=2)if(x<=ss&&ss<a[i])ss=a[i];
	return x<=ss;
}
int main()
{
	scanf("%d",&n);
	int ss=0,s=0;a[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		ss=ss+a[i];
		if(i%2==1)s=s+a[i];
	}
	if(n%2==0)
	{
		if(s<ss-s)printf("%d %d\n",ss-s,s);
		else printf("%d %d\n",s,ss-s);
	}
	else
	{
		int l=s*2-ss,r=s;
		while(l<r)
		{
			int mid=(l+r+1)/2;
			if(pand(mid))l=mid;
			else r=mid-1;
		}
		printf("%d %d\n",ss-s+l,s-l);
	}
	return 0;
}