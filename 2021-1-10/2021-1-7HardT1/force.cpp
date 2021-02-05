#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(long long &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
char ouf[110];
inline void write(unsigned long long x)
{
	int len=0;
	while(x>0)ouf[++len]=x%10+'0',x=x/10;
	while(len>0)putchar(ouf[len--]);
	putchar('\n');
}
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
unsigned long long a[5100][5100];
int main()
{
	freopen("qiu.in","r",stdin);
	freopen("qiu.ans","w",stdout);
	int x0=2500,y0=2500;
	int x=x0,y=y0,d=0,cnt=0;
	memset(a,0,sizeof(a));
	while(cnt<24990001)
	{
		a[x][y]=++cnt;
		int r=(d+1)%4;
		if(a[x+dx[r]][y+dy[r]]==0)d=r;
		x=x+dx[d];y=y+dy[d];
	}
	long long t;read(t);
	while(t--)
	{
		long long x1,x2,y1,y2;read(x1);read(x2);read(y1);read(y2);
		x1=x1+x0;x2=x2+x0;y1=y1+y0;y2=y2+y0;
		unsigned long long ss=0;
		for(x=x1;x<=x2;x++)
		{
			for(y=y1;y<=y2;y++)
			{
				ss=ss+a[x][y];
			}
		}
		write(ss%(9223372036854775808ull));
	}
	return 0;
}