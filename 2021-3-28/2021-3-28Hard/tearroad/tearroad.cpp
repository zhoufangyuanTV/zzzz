#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
char str[11];
struct node
{
	int x,y,next;
}a[4010000];int len,last[2010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int V[110];
void dfs(int x,int v)
{
	if(x<v)return ;
	if((V[x]|1<<v-1)==V[x])return ;
	V[x]|=1<<v-1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		dfs(y,v);
	}
}
inline long long ksm(long long x,long long k)
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
int cnt[32768];
int main()
{
	freopen("tearroad.in","r",stdin);
	freopen("tearroad.out","w",stdout);
	scanf("%s",str+1);
	int n,m,k;read(n);read(m);read(k);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	memset(V,0,sizeof(V));
	for(int i=1;i<=n;i++)dfs(i,i);
	for(int i=0;i<1<<n;i++)
	{
		cnt[i]=0;
		for(int j=1;j<=n;j++)if((i|1<<j-1)==i)cnt[i]++;
	}
	long long s1=0,s2=0,s3=0;
	for(int i=1;i<1<<n;i++)
	{
		int x=(1<<n)-1,y=0,z=0;
		for(int j=1;j<=n;j++)
		{
			if((i|1<<j-1)==i)
			{
				x&=V[j];
				y|=V[j];
				z^=V[j];
			}
		}
		s1=(s1+ksm(cnt[x],k))%998244353;
		s2=(s2+ksm(k,cnt[y]))%998244353;
		s3=(s3+(cnt[z]+k-1)/k)%998244353;
	}
	bool bk=false;
	if(str[1]=='1')
	{
		if(bk==false)bk=true;
		else putchar(' ');
		printf("%lld",s1);
	}
	if(str[2]=='1')
	{
		if(bk==false)bk=true;
		else putchar(' ');
		printf("%lld",s2);
	}
	if(str[3]=='1')
	{
		if(bk==false)bk=true;
		else putchar(' ');
		printf("%lld",s3);
	}
	putchar('\n');
	return 0;
}