#include<cstdio>
#include<cstring>
using namespace std;
char s[1100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	int ss=0,sss=0;
	for(int i=1;i<=n;i++)
	{
		int sr=0;
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)sr+=s[j]-'0';
		if(sr&1)sss++;
		else ss++;
	}
	printf("%lld\n",1ll*ss*sss);
	return 0;
}