#include<cstdio>
#include<cstring>
using namespace std;
char a[11000],b[11000],c[11000],d[11000];
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s%s%s%s",a+1,b+1,c+1,d+1);
		int an=strlen(a+1),bn=strlen(b+1),cn=strlen(c+1),dn=strlen(d+1);
		int as=a[an]-'0',bs=0,cs=c[cn]-'0',ds=0;
		for(int i=1;i<=bn;i++)bs=bs+b[i]-'0';
		for(int i=1;i<=dn;i++)ds=ds+d[i]-'0';
		printf("%d\n",(as+cs)%2!=(bs+ds)%3);
	}
	return 0;
}