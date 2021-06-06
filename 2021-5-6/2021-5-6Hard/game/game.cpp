#include<cstdio>
#include<cstring>
using namespace std;
int threshold=10000000;
unsigned long long k1,k2;
unsigned long long xorShift128Plus()
{
	unsigned long long k3=k1,k4=k2;
	k1=k4;
	k3^=k3<<23;
	k2=k3^k4^(k3>>17)^(k4>>26);
	return k2+k4;
}
int n,k,a[5010000],b[5010000];
void gen()
{
	scanf("%d%d%llu%llu",&n,&k,&k1,&k2);
	for(int i=1;i<=n;i++)
	{
		a[i]=xorShift128Plus()%threshold+1;
		b[i]=xorShift128Plus()%threshold+1;
	}
}
int cnt[4883],d[5010000];
void RadixSort(int c[],int n)
{
	memset(cnt,0,16384);
	for(int i=1;i<=n;i++)cnt[c[i]&4095]++;
	for(int i=1;i<4096;i++)cnt[i]+=cnt[i-1];
	for(int i=1;i<=n;i++)d[cnt[c[i]&4095]--]=c[i];
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)cnt[d[i]>>12]++;
	for(int i=4881;i>=0;i--)cnt[i]+=cnt[i+1];
	for(int i=1;i<=n;i++)c[cnt[d[i]>>12]--]=d[i];
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	gen();
	for(int i=1;i<=n;i++)b[i]+=a[i];
	RadixSort(a,n);
	RadixSort(b,n);
	int i=0,j=0;
	unsigned long long ss=0,s=0;
	while(k--)
	{
		if(i<n)
		{
			s+=a[++i];
			if(i>1&&j<n&&a[i]+a[i-1]<b[j+1])
			{
				s-=a[i--];
				s-=a[i--];
				s+=b[++j];
			}
		}
		else
		{
			s-=a[i--];
			s+=b[++j];
		}
		ss^=s;
	}
	printf("%llu\n",ss);
	return 0;
}
