#include<cstdio>
#include<cstring>
using namespace std;
char a[1110000];
int cnt[510];
int f[1110000],ff[1110000];
long long haxi1[1110000],haxi2[1110000];
long long base1[1110000],base2[1110000];
long long p=1000000007,pp=1000000009;
inline long long jianp(long long x,long long y){return x-y<0?x-y+p:x-y;}
inline long long jianpp(long long x,long long y){return x-y<0?x-y+pp:x-y;}
inline bool pand(int l,int r,int ll,int rr)
{
	long long h1=jianp(haxi1[r],haxi1[l-1]*base1[r-l+1]%p);
	long long hh1=jianp(haxi1[rr],haxi1[ll-1]*base1[rr-ll+1]%p);
	if(h1!=hh1)return false;
	long long h2=jianpp(haxi2[r],haxi2[l-1]*base2[r-l+1]%pp);
	long long hh2=jianpp(haxi2[rr],haxi2[ll-1]*base2[rr-ll+1]%pp);
	return h2==hh2;
}
long long g[1110000][31];
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	base1[0]=1;
	for(int i=1;i<=1100000;i++)base1[i]=base1[i-1]*31%p;
	base2[0]=1;
	for(int i=1;i<=1100000;i++)base2[i]=base2[i-1]*131%pp;
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s",a+1);
		int n=strlen(a+1);
		haxi1[0]=0;haxi2[0]=0;
		for(int i=1;i<=n;i++)
		{
			int c=a[i]-'a';
			haxi1[i]=(haxi1[i-1]*31+c)%p;
			haxi2[i]=(haxi2[i-1]*131+c)%pp;
		}
		memset(cnt,0,sizeof(cnt));int s=0;
		for(int i=1;i<=n;i++)
		{
			int c=a[i]-'a';
			cnt[c]++;
			if(cnt[c]%2==0)s--;
			else s++;
			f[i]=s;
		}
		memset(cnt,0,sizeof(cnt));s=0;
		for(int i=n;i>=1;i--)
		{
			int c=a[i]-'a';
			cnt[c]++;
			if(cnt[c]%2==0)s--;
			else s++;
			ff[i]=s;
		}
		for(int i=2;i<n;i++)
		{
			for(int j=0;j<=26;j++)g[i][j]=0;
			for(int j=i;j<n;j+=i)
			{
				if(pand(1,i,j-i+1,j)==false)break;
				g[i][ff[j+1]]++;
			}
		}
		for(int i=n-2;i>=2;i--)
		{
			for(int j=0;j<=26;j++)g[i][j]=g[i][j]+g[i+1][j];
		}
		long long ss=0;
		for(int i=2;i<n;i++)
		{
			for(int j=f[i-1];j<=26;j++)ss=ss+g[i][j];
		}
		printf("%lld\n",ss);
	}
	return 0;
}
