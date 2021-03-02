#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[210000];
bool b[210000],bb[110000];
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n*2-2;i++)scanf("%d",&a[i]);
	sort(a+1,a+2*n-1);
	memset(b,false,sizeof(b));
	memset(bb,false,sizeof(bb));
	int s=0;
	for(int i=1;i<=n*2-2;i++)
	{
		if(a[i]>i)
		{
			for(int j=1;j<=n-2;j++)printf("-1 ");
			printf("-1\n");
			return 0;
		}
		if(i==a[i]&&i!=n)b[i]=bb[i]=true,s++;
	}
	int j,sr=0;long long ss=0;
	for(int i=1;i<s;i++)printf("-1 ");
	for(j=n*2-2;j>=1;j--)
	{
		if(b[j]==false)
		{
			sr++;ss+=a[j];
			if(sr==s)break;
		}
	}
	printf("%lld",ss);
	for(int i=1;i<=n*2-2;i++)
	{
		if(bb[a[i]]==false)
		{
			b[i]=true;
			bb[a[i]]=true;
			if(j<=i)sr--,ss-=a[i];
			s++;
			for(j--;j>=1;j--)
			{
				if(b[j]==false)
				{
					sr++;ss+=a[j];
					if(sr==s)break;
				}
			}
			printf(" %lld",ss);
		}
	}
	for(int i=s+1;i<n;i++)printf(" -1");
	putchar('\n');
	return 0;
}