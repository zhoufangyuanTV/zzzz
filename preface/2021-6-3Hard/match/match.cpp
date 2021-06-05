#include<cstdio>
#include<cstring>
using namespace std;
int bitcnt[262144];
int f[262144][19];
char A[310][310],B[310][310];
int main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%s",A[i]+1);
	for(int i=1;i<=n;i++)scanf("%s",B[i]+1);
	bitcnt[0]=0;
	for(int i=1;i<1<<n;i++)bitcnt[i]=bitcnt[i>>1]+(i&1);
	memset(f,0,sizeof(f));f[0][0]=1;
	for(int i=1;i<1<<n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i>>j-1&1)
			{
				if(A[bitcnt[i]][j]=='1')
				{
					for(int k=1;k<=bitcnt[i];k++)f[i][k]^=f[i^1<<j-1][k-1];
				}
				if(B[bitcnt[i]][j]=='1')
				{
					for(int k=0;k<bitcnt[i];k++)f[i][k]^=f[i^1<<j-1][k];
				}
			}
		}
	}
	int q;scanf("%d",&q);
	while(q--)
	{
		int i;scanf("%d",&i);
		printf("%d\n",f[(1<<n)-1][i]);
	}
	return 0;
}
