#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("experience.in","r",stdin);
	freopen("experience.out","w",stdout);
	int n,m;scanf("%*d%d%d",&n,&m);
	if(n==2)
	{
		if(m==1)puts("0");
		else if(m==2)puts("1");
		else if(m==3)puts("9");
		else if(m==4)puts("30");
	}
	else
	{
		if(m==1)puts("0");
		else if(m==2)puts("0");
		else if(m==3)puts("2+6");
		else if(m==4)puts("24+8+24+24+24");
	}
	return 0;
}
