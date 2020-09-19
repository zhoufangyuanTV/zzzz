#include<cstdio>
#include<cstring>
using namespace std;
char s[110000];
int p[110000];
int main()
{
	int n,m;scanf("%d%s%d",&n,s+1,&m);
	for(int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		p[l-1]=l-2;
		for(int j=l;j<=r;j++)
		{
			int k=p[j-1];
			while(k!=l-2&&s[k+1]!=s[j])k=p[k];
			p[j]=k+1;
		}
		if((r-l+1)%(r-p[r])==0)printf("%d\n",r-p[r]);
		else printf("%d\n",r-l+1);
	}
	return 0;
}