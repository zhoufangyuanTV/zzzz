#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
double f;
int fx[5100],fy[5100];
#define PI 3.14159265358979323846
int Ans,x[5100],y[5100];
struct point{double x,y;}a[11000];
double z[11000];
bool b[11000];
int p[11000];
inline bool cmp(int x,int y){return z[x]<z[y];}
int cnt[11000];
void solve(int l,int r)
{
	if(l>r)return ;
	for(int i=l;i<=r;i++)z[p[i]]=a[p[i]].x;
	sort(p+l,p+r+1,cmp);
	for(int i=l+1;i<=r;i++)z[p[i]]=atan2(a[p[i]].y-a[p[l]].y,a[p[i]].x-a[p[l]].x);
	sort(p+l+1,p+r+1,cmp);
	cnt[l]=0;
	for(int i=l+1;i<=r;i++)cnt[i]=cnt[i-1]+b[p[i]];
	for(int k=0;k<=(r-l)/2;k++)
	{
		int i=(l+r+1)/2+k;
		if(b[p[l]]!=b[p[i]]&&(i-l&1)&&cnt[i-1]==(i-l)/2)
		{
			Ans++;
			x[Ans]=p[l];y[Ans]=p[i];
			solve(l+1,i-1);solve(i+1,r);
			return ;
		}
		i=(l+r+1)/2-k;
		if(b[p[l]]!=b[p[i]]&&(i-l&1)&&cnt[i-1]==(i-l)/2)
		{
			Ans++;
			x[Ans]=p[l];y[Ans]=p[i];
			solve(l+1,i-1);solve(i+1,r);
			return ;
		}
	}
}
int c[11000];
int main(int argc,char* argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	srand(time(0));
	int n;scanf("%d",&n);n*=2;
	for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
	f=0;int tt=2000;
	while(tt--)
	{
		double t=PI*rand()/RAND_MAX-PI/2;
		double tx=cos(t),ty=sin(t);
		for(int i=1;i<=n;i++)z[i]=a[i].x*tx+a[i].y*ty;
		for(int i=1;i<=n;i++)p[i]=i;
		sort(p+1,p+n+1,cmp);
		for(int i=1;i<=n/2;i++)b[p[i]]=false;
		for(int i=n/2+1;i<=n;i++)b[p[i]]=true;
		Ans=0;
		solve(1,n);
		double dis=0;
		for(int i=1;i<=Ans;i++)dis+=sqrt((a[x[i]].x-a[y[i]].x)*(a[x[i]].x-a[y[i]].x)+(a[x[i]].y-a[y[i]].y)*(a[x[i]].y-a[y[i]].y));
		if(f<dis)
		{
			f=dis;
			for(int i=1;i<=Ans;i++)fx[i]=x[i],fy[i]=y[i];
		}
	}
	for(int i=1;i<=n;i++)
	{
		c[fx[i]]=fy[i];
		c[fy[i]]=fx[i];
	}
	for(int i=1;i<n;i++)printf("%d ",c[i]);
	printf("%d\n",c[n]);
	return 0;
}
