#include<cstdio>
#include<cstring>
using namespace std;
bool kk[110],kkk[110];
int main()
{
	freopen("zoo.in","r",stdin);
	freopen("zoo.out","w",stdout);
	int n,m,c,k;scanf("%d%d%d%d",&n,&m,&c,&k);
	memset(kk,false,sizeof(kk));
	for(int i=1;i<=n;i++)
	{
		unsigned long long x;scanf("%llu",&x);
		for(int j=0;j<k;j++)
		{
			if((x&(1ull<<j))==(1ull<<j))
			{
				kk[j]=true;
			}
		}
	}
	memset(kkk,true,sizeof(kkk));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		kkk[x]=false;
	}
	unsigned long long ss=0;
	for(int i=0;i<k;i++)
	{
		if(kk[i]==true||kkk[i]==true)ss++;
	}
	if(ss==64)
	{
		if(n==0)printf("18446744073709551616\n");
		else printf("%llu\n",((unsigned long long)n^18446744073709551615ull)+1);
	}
	else
	{
		ss=1ull<<ss;
		printf("%llu\n",ss-(unsigned long long)n);
	}
	return 0;
}
