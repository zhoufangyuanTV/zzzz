#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Query
{
	bool opt;
	int a,b,c;
}Q[310000];
char s[11];
int a[310000];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	{
		scanf("%d",&Q[i].c);
		Q[i].opt=false;Q[i].a=i;Q[i].b=1;
	}
	int q=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='C')
		{
			q++;
			Q[q].opt=false;
			Q[q].a=i;Q[q].b=a
		}
	}
	return 0;
}
