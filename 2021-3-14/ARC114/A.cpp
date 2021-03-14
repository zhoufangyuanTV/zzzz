#include<cstdio>
#include<cstring>
using namespace std;
int a[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int b[110];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	long long ss=0x3f3f3f3f3f3f3f3fll;
	for(int i=0;i<1<<15;i++)
	{
		bool bbk=true;
		for(int j=1;j<=n;j++)
		{
			bool bk=false;
			for(int k=0;k<15;k++)
			{
				if((i|1<<k)==i)
				{
					if(b[j]%a[k]==0){bk=true;break;}
				}
			}
			if(bk==false){bbk=false;break;}
		}
		if(bbk==true)
		{
			long long s=1;
			for(int j=0;j<15;j++)
			{
				if((i|1<<j)==i)s=s*a[j];
			}
			if(s<ss)ss=s;
		}
	}
	printf("%lld\n",ss);
	return 0;
}