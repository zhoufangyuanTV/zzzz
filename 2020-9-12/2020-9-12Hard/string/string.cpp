#include<cstdio>
#include<cstring>
using namespace std;
char s[110000];
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		if(n==0)
		{
			printf("0\n");
			continue;
		}
		scanf("%s",s+1);
		bool bk=false;
		for(int i=1;i<=n/2;i++)if(s[i]!=s[n-i+1]){bk=true;break;}
		if(bk)printf("1\n");
		else
		{
			for(int i=2;i<=n;i++)if(s[i]!=s[1]){bk=true;break;}
			if(bk)
			{
				if(n%2==0)printf("2\n");
				else
				{
					bk=false;
					for(int i=3;i<=n;i+=2)if(s[i]!=s[1]){bk=true;break;}
					for(int i=2;i<n;i+=2)if(s[i]!=s[2]){bk=true;break;}
					if(bk)
					{
						bk=false;
						for(int i=1;i<=n/2;i++)if(s[i]!=s[1]){bk=true;break;}
						if(bk)printf("2\n");
						else printf("-1\n");
					}
					else printf("-1\n");
				}
			}
			else printf("-1\n");
		}
	}
	return 0;
}