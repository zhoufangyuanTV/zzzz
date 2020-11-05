#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
double ppt,st,ed,A;
double f[110000],power[110000],point[110000];
inline double mymax(double x,double y){return x>y?x:y;}
inline double sig(double x){return x<0?-1:x>0?1:0;}
inline double PPT(double power1,double point1,double power2,double point2)
{
	return 2*sig(power1-power2)*(sqrt(abs(power1-power2)+1)-1)-A*sig(point1-point2)*(sqrt(abs(point1-point2)+1)-1);
}
void dfs(int x,int fa)
{
	f[x]=-100000;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			f[x]=mymax(f[x],f[y]);
		}
	}
	if(f[x]==-100000)f[x]=mymax(f[x],st);
	f[x]=f[x]+PPT(ppt,f[x],power[x],point[x]);
}
double ss;
int plen,p[310000];
double fg[310000],fh[310000];
void dfs(int x,int fa,double ff)
{
	f[x]=mymax(f[x],ff+PPT(ppt,ff,power[x],point[x]));
	int pl=plen;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)p[++plen]=y;
	}
	int pr=plen;
	if(pr==pl||pr==pl+1&&fa==0)ss=mymax(ss,f[x]);
	fg[pl]=ff;
	for(int i=pl+1;i<=pr;i++)fg[i]=mymax(fg[i-1],f[p[i]]);
	fh[pr+1]=ff;
	plen+=2;
	for(int i=pr;i>=pl+1;i--)fh[i]=mymax(fh[i+1],f[p[i]]);
	for(int i=pl+1;i<=pr;i++)
	{
		double g=mymax(fg[i-1],fh[i+1]);
		dfs(p[i],x,g+PPT(ppt,g,power[x],point[x]));
	}
}
int main()
{
	freopen("pigeatyy.in","r",stdin);
	freopen("pigeatyy.out","w",stdout);
	int n;scanf("%*d%d%lf%lf%lf",&n,&st,&ed,&A);
	len=0;memset(last,0,sizeof(last));
	int ppp=0;
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
		if(x==1)ppp++;
		if(y==1)ppp++;
	}
	for(int i=1;i<=n;i++)scanf("%lf%lf",&power[i],&point[i]);
	double l=-10000,r=1000000;
	while(r-l>3e-7)
	{
		double mid=(l+r)/2;
		ppt=mid;
		dfs(1,0);
		ss=-100000;
		plen=0;
		double ff=-100000;
		if(ppp==1)ff=st;
		dfs(1,0,ff);
		if(ss>=ed)r=mid;
		else l=mid;
	}
	printf("%lf\n",r);
	return 0;
}