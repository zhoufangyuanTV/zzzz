#include<cstdio>
#include<cstring>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void write(long long x)
{
	long long y=10;
	while(y<=x)y=y*10;
	while(y!=1){y=y/10;putchar(x/y+'0');x=x%y;}
	putchar('\n');
}
int a[1010000],b[1010000];
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("horsehunter.in","r",stdin);
	freopen("horsehunter.out","w",stdout);
	int n,m;read(n);read(m);
	for(int i=1;i<=n;i++)read(a[i]);a[n+1]=0;
	long long ss=0;
	for(int i=1;i<=n;i+=2)
	{
		ss=ss+1ll*mymin(a[i],a[i+1])*(i^i+1);
		b[i]=a[i]-mymin(a[i],a[i+1]);
		b[i+1]=a[i+1]-mymin(a[i],a[i+1]);
	}
	b[n+1]=b[n+2]=0;
	for(int i=2;i<=n;i+=2)ss=ss+mymin(b[i],b[i+1]);
	write(ss);
	for(int i=1;i<=m;i++)
	{
		int x;read(x);
		int y=x&1?x+1:x-1;
		ss=ss-1ll*mymin(a[x],a[y])*(x^y);
		read(a[x]);
		ss=ss+1ll*mymin(a[x],a[y])*(x^y);
		int xx=x&1?x-1:x+1;
		int yy=y&1?y-1:y+1;
		ss=ss-mymin(b[x],b[xx])-mymin(b[y],b[yy]);
		b[x]=a[x]-mymin(a[x],a[y]);
		b[y]=a[y]-mymin(a[x],a[y]);
		ss=ss+mymin(b[x],b[xx])+mymin(b[y],b[yy]);
		write(ss);
	}
	return 0;
}