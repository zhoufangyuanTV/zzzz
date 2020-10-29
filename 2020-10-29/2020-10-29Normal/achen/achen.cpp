#include<cstdio>
#include<cstring>
using namespace std;
int f[1010000];
int main()
{
	freopen("achen.in","r",stdin);
	freopen("achen.out","w",stdout);
	f[0]=1;f[1]=1;f[2]=1;
	for(int i=3;i<=1000000;i++)f[i]=(f[i-1]+f[i-3])%998244353;
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,A,B;scanf("%d%d%d",&n,&A,&B);
		if(A>B)A^=B^=A^=B;
		if(A>1)A++;if(B<n)B--;
		if(A>B)printf("0\n");
		else printf("%d\n",f[B-A]);
	}
	return 0;
}