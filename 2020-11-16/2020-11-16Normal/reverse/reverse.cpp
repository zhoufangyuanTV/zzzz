#include<cstdio>
#include<cstring>
using namespace std;
int f[8388608];
struct node
{
	int x,p;
}list[8388608];
bool b[8388608];
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
long long F[50]={1,313580260,24153594,180832141,623549475,600151703,118555701,138894910,391938921,94713314,46796575,514331555,438425500,979296190,901002909,891313291,525968915,564758681,950038481,238703419,625627616,390400372,327806090,32055438,317190899,141879510,66184294,282970591,322246221,366741457,750348159,128011307,684399504,958870061,71920520,742379541,859365829,31921323,185637776,568973445,934543240,638168352,338314267,374557572,230678080,159960230,897355463,760246454,433927037,137196301};
char a[110];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	long long type,n,m;scanf("%lld%lld%lld",&type,&n,&m);
	if(type==1)scanf("%s",a+1);
	else
	{
		/*n=2*n+1;
		for(int i=1;i<=n;i++)a[i]=i%2+'0';*/
		if(2*m-1>=998244353)
		{
			printf("0\n");
			return 0;
		}
		long long jc=1,fjc=1,FF=F[m/10000000];
		for(long long i=m*2+1;i<=n+m+1;i++)jc=jc*i%998244353;
		for(long long i=1;i<=n-m+1;i++)fjc=fjc*i%998244353;
		fjc=ksm(fjc,998244351);
		for(long long i=m/10000000*10000000+1;i<=m;i++)FF=FF*(2*i-1)%998244353;
		printf("%lld\n",jc*fjc%998244353*FF%998244353);
		return 0;
	}
	memset(b,false,sizeof(b));
	memset(f,0,sizeof(f));
	int g=0;
	for(int i=1;i<=n;i++)g|=a[i]-'0'<<i-1;
	f[g]=1;b[g]=1;
	int head=1,tail=2;
	list[1]=(node){0,g};
	while(head<tail)
	{
		if(list[head].x==m)break;
		int j=list[head].p;
		for(int k=1;k<=n;k++)a[k]=j>>k-1&1;
		for(int l=1;l<=n;l++)
		{
			if(a[l]==1)
			{
				g=1<<l-1;
				if(b[j^g]==false)
				{
					b[j^g]=true;
					list[tail++]=(node){list[head].x+1,j^g};
				}
				f[j^g]=(f[j^g]+f[j])%998244353;
				for(int r=l+2;r<=n;r+=2)
				{
					if(a[r-1]!=0||a[r]!=1)break;
					g|=1<<r-2|1<<r-1;
					if(b[j^g]==false)
					{
						b[j^g]=true;
						list[tail++]=(node){list[head].x+1,j^g};
					}
					f[j^g]=(f[j^g]+f[j])%998244353;
				}
			}
		}
		head++;
	}
	int ss=0;
	for(int i=head;i<tail;i++)ss=(ss+f[list[i].p])%998244353;
	printf("%d\n",ss);
	return 0;
}