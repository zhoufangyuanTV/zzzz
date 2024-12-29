#include<cstdio>
#include<cstring>
using namespace std;
int s[410000],g[410000],l[210000],r[210000];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		for(int i=0;i<=2*n;i++)s[i]=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&l[i],&r[i]);
			if(l[i]==r[i])s[l[i]]++;
		}
		g[0]=0;
		for(int i=1;i<=2*n;i++)
		{
			if(s[i]>0)g[i]=g[i-1]+1;
			else g[i]=g[i-1];
		}
		for(int i=1;i<=n;i++)
		{
			if(l[i]==r[i])
			{
				if(s[l[i]]>1)putchar('0');
				else putchar('1');
			}
			else
			{
				if(r[i]-l[i]+1==g[r[i]]-g[l[i]-1])putchar('0');
				else putchar('1');
			}
		}
		putchar('\n');
	}
	return 0;
}