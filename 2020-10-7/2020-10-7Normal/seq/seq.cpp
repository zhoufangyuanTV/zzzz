#include<cstdio>
#include<cstring>
using namespace std;
void read(int &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
int s[110000];
long long a[110000];
int main()
{
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	int m;scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&s[i]);
	int n;scanf("%d",&n);
	while(n--)
	{
		long long k;scanf("%lld%lld%lld",&a[0],&a[1],&k);
		int i=1,j=1;
		int maxs=-1,mins=-1;
		if(s[j]==0)
		{
			maxs=mins=0;
			j++;
		}
		while(i<=s[m])
		{
			if(i==s[j])
			{
				if(maxs==-1||a[maxs]<a[i])maxs=i;
				if(mins==-1||a[i]<a[mins])mins=i;
				j++;
			}
			if((a[i]>0&&a[i-1]>0)||(a[i]<0&&a[i-1]<0)||(a[i]==0&&a[i-1]==0))break;
			a[i+1]=k*a[i]+a[i-1];
			i++;
		}
		if(j<=m)
		{
			if(a[i]==0&&a[i-1]==0)
			{
				if(maxs==-1||a[maxs]<0)maxs=s[j];
				if(mins==-1||0<a[mins])mins=s[j];
			}
			else if(a[i]<0&&a[i-1]<0)
			{
				if(maxs==-1)maxs=s[j];
				if(mins==-1)mins=s[m];
				else
				{
					int mr=mins;
					while(i<=s[m]&&a[i]>=a[mr])
					{
						if(i==s[j])
						{
							if(maxs==-1||a[maxs]<a[i])maxs=i;
							if(mins==-1||a[i]<a[mins])mins=i;
							j++;
						}
						a[i+1]=k*a[i]+a[i-1];
						i++;
					}
					if(j<=m)mins=s[m];
				}
			}
			else
			{
				if(mins==-1)mins=s[j];
				if(maxs==-1)maxs=s[m];
				else
				{
					int mr=maxs;
					while(i<=s[m]&&a[i]<=a[mr])
					{
						if(i==s[j])
						{
							if(maxs==-1||a[maxs]<a[i])maxs=i;
							if(mins==-1||a[i]<a[mins])mins=i;
							j++;
						}
						a[i+1]=k*a[i]+a[i-1];
						i++;
					}
					if(j<=m)maxs=s[m];
				}
			}
		}
		printf("%d %d\n",maxs,mins);
	}
	return 0;
}