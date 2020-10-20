#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("lol.in","r",stdin);
	freopen("lol.out","w",stdout);
	int x;scanf("%d",&x);
	int t=100000000,j=x,ss=0;
	for(int i=1;i<=t;i++)
	{
		if(rand()%100<j)ss++,j=x;
		else j+=x;
	}
	printf("%.9lf\n",1.0*ss/t);
	return 0;
}