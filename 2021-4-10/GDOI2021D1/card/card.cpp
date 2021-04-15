#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int a[1010000],b[1010000];
struct node
{
	int x,p;bool bk;
}g[2010000];
inline bool cmp(node x,node y){return x.x<y.x;}
bool f[1010000],ff[1010000];
int c[1010000];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	int n,m;read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		g[i].x=a[i];g[i].p=i;g[i].bk=false;
	}
	for(int i=1;i<=n;i++)
	{
		read(b[i]);
		g[n+i].x=b[i];g[n+i].p=i;g[n+i].bk=true;
	}
	sort(g+1,g+n*2+1,cmp);
	memset(f,true,sizeof(f));
	memset(ff,true,sizeof(ff));
	int ma=0,s=0;
	memset(c,0,sizeof(c));
	c[0]=0;
	for(int i=n;i>=1;i--)c[n-i+1]=mymax(c[n-i],mymin(a[i],b[i]));
	int ss=0x3f3f3f3f,lst=0;
	for(int i=1;i<=n*2;i++)
	{
		int mm=mymin(m-s,n-lst);
		int MA=mymax(ma,c[mm]);
		if(mm+s<n)MA=mymax(MA,a[n-mm]);
		ss=mymin(ss,MA-g[i].x);
		if(g[i].bk==false)
		{
			f[g[i].p]=false;
			if(ff[g[i].p]==false)break;
			s++;
			if(s>m)break;
			ma=mymax(ma,b[g[i].p]);
		}
		else
		{
			ff[g[i].p]=false;
			if(f[g[i].p]==false)break;
			lst=mymax(lst,g[i].p);
		}
	}
	printf("%d\n",ss);
	return 0;
}
