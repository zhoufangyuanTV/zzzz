#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct point{double x,y,z;int c;}p[251000];
inline bool cmp1(point x,point y){return x.x<y.x;}
inline bool cmp2(point x,point y){return x.z<y.z;}
inline bool cmp3(point x,point y){return x.c<y.c;}
inline point operator-(point x,point y){return (point){x.x-y.x,x.y-y.y,0,0};}
inline double multi(point x,point y){return x.x*y.y-x.y*y.x;}
int list[251000],head,tail;
void tubao(int l,int r)
{
	sort(p+l,p+r+1,cmp1);
	for(int i=l+1;i<=r;i++)p[i].z=atan2(p[i].y-p[l].y,p[i].x-p[l].x);
	sort(p+l+1,p+r+1,cmp2);
	head=1;tail=2;list[1]=l;list[2]=l+1;
	for(int i=l+2;i<=r;i++)
	{
		while(head<tail&&multi(p[i]-p[list[tail-1]],p[list[tail]]-p[list[tail-1]])>=0)tail--;
	}
}
long long ss=0;
int l[251000],r[251000];
bool xzqq(int lc,int rc)
{
	if(l[lc]>r[rc])return false;
	if(l[lc]==l[rc])return true;
	int mid=(lc+rc)/2;
	int lk=xzqq(lc,mid),rk=xzqq(mid+1,rc);
	if(lk&&rk)
	{
	}
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf%d",&p[i].x,&p[i].y,&p[i].c);
	sort(p+1,p+n+1,cmp3);
	int j=1;
	for(int i=1;i<=n;i++)
	{
		while(p[j].c<i)j++;
		l[i]=j;
	}
	r[n]=n;
	for(int i=1;i<n;i++)r[i]=l[i+1]-1;
	return 0;
}