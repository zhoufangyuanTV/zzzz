#include<cstdio>
#include<cstring>
using namespace std;
const int base1=5,base2=31,p=19260817,p1=1000000007,p2=1000000009;
long long ph1[5010000],ph2[5010000];
struct node
{
	int hash1,hash2,cnt;
}hash[19260817];
char s[5010000];
int main()
{
	freopen("dna.in","r",stdin);
	freopen("dna.out","w",stdout);
	int k;scanf("%s%d",s+1,&k);
	int n=strlen(s+1);
	long long b1k=1,b2k=1;
	for(int i=1;i<=k;i++)b1k=b1k*base1%p1,b2k=b2k*base2%p2;
	int ss=0;
	memset(hash,0,sizeof(hash));
	ph1[0]=ph2[0]=0;
	for(int i=1;i<=n;i++)
	{
		int c=s[i]=='A'?0:s[i]=='G'?1:s[i]=='C'?2:3;
		ph1[i]=(ph1[i-1]*base1+c)%p1;
		ph2[i]=(ph2[i-1]*base2+c)%p2;
		if(k<=i)
		{
			int h1=(ph1[i]-ph1[i-k]*b1k%p1+p1)%p1;
			int h2=(ph2[i]-ph2[i-k]*b2k%p2+p2)%p2;
			int j=(h1+h2)%p;
			while(hash[j].cnt>0&&(hash[j].hash1!=h1||hash[j].hash2!=h2))j=(j+1)%p;
			hash[j].hash1=h1;hash[j].hash2=h2;hash[j].cnt++;
			if(ss<hash[j].cnt)ss=hash[j].cnt;
		}
	}
	printf("%d\n",ss);
	return 0;
}