#include<cstdio>
#include<cstring>
using namespace std;
char s[31000];
long long h1[31000],h2[31000];
long long base1[31000],base2[31000];
bool pand(int l1,int r1,int l2,int r2)
{
	long long hash1=(h1[r1]-h1[l1-1]*base1[r1-l1+1]%1000000007+1000000007)%1000000007;
	long long hash2=(h2[r1]-h2[l1-1]*base2[r1-l1+1]%1000000009+1000000009)%1000000009;
	long long hash3=(h1[r2]-h1[l2-1]*base1[r2-l2+1]%1000000007+1000000007)%1000000007;
	long long hash4=(h2[r2]-h2[l2-1]*base2[r2-l2+1]%1000000009+1000000009)%1000000009;
	return hash1==hash3&&hash2==hash4;
}
int main()
{
	freopen("excellent.in","r",stdin);
	freopen("excellent.out","w",stdout);
	base1[0]=1;
	for(int i=1;i<=30000;i++)base1[i]=base1[i-1]*31%1000000007;
	base2[0]=1;
	for(int i=1;i<=30000;i++)base2[i]=base2[i-1]*37%1000000009;
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s+1);
		int n=strlen(s+1);
		h1[0]=h2[0]=0;
		for(int i=1;i<=n;i++)
		{
			h1[i]=(h1[i-1]*31+s[i]-'a'+1)%1000000007;
			h2[i]=(h2[i-1]*37+s[i]-'a'+1)%1000000009;
		}
		long long ss=0;
		for(int i=2;i<=n-2;i++)
		{
			long long s1=0,s2=0;
			for(int j=1;j*2<=i;j++)
			{
				if(pand(i-2*j+1,i-j,i-j+1,i))s1++;
			}
			for(int j=1;i+j*2<=n;j++)
			{
				if(pand(i+1,i+j,i+j+1,i+j*2))s2++;
			}
			ss+=s1*s2;
		}
		printf("%lld\n",ss);
	}
	return 0;
}
