#include<cstdio>
#include<cstring>
using namespace std;
int popcount[1<<10];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	popcount[0]=0;
	for(int i=1;i<1<<mymax(n,m);i++)popcount[i]=popcount[i>>1]+(i&1);
	for(int i=1;i<1<<n;i++)
	{
		for(int j=1;j<1<<m;j++)
		{
			putchar((popcount[i&j]&1)^(popcount[(i-1)&j]&1)^(popcount[i&(j-1)]&1)^(popcount[(i-1)&(j-1)]&1)?'1':'0');
		}
		putchar('\n');
	}
	return 0;
}