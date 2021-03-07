#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct point{long long x,y;double z;int p;}a[510];
inline long long mul(point p0,point p1,point p2)
{
	long long x1=p1.x-p0.x,y1=p1.y-p0.y;
	long long x2=p2.x-p0.x,y2=p2.y-p0.y;
	return x1*y2-x2*y1;
}
inline bool cmp1(point x,point y){return x.x==y.x?x.y<y.y:x.x<y.x;}
inline bool cmp2(point x,point y){return x.z<y.z;}
inline bool cmp3(point x,point y){return x.p<y.p;}
int p[510],plen;
bool b[510];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld%lld",&a[i].x,&a[i].y);
			a[i].p=i;
		}
		if(n==2){printf("1 2\n");continue;}
		sort(a+1,a+n+1,cmp1);
		for(int i=2;i<=n;i++)a[i].z=atan2(a[i].y-a[1].y,a[i].x-a[1].x);
		sort(a+2,a+n+1,cmp2);
		plen=1;p[1]=1;
		for(int i=2;i<=n;i++)
		{
			while(plen>1&&mul(a[p[plen-1]],a[i],a[p[plen]])>0)plen--;
			p[++plen]=i;
		}
		if(plen==n)
		{
			int i;
			for(i=1;i<=n;i++)if(a[i].p==1)break;
			for(int j=i;a[j].p!=n;j=(j+n-2)%n+1)printf("%d ",a[j].p);
			for(int j=i%n+1;a[j].p!=n;j=j%n+1)printf("%d ",a[j].p);
			printf("%d\n",n);
		}
		else
		{
			memset(b,false,sizeof(b));
			for(int i=1;i<=plen;i++)b[a[p[i]].p]=true;
			sort(a+1,a+n+1,cmp3);
			int i;
			for(i=1;i<=n;i++)if(b[i]==false)break;
			point tt=a[i];a[i]=a[1];a[1]=tt;
			for(i=2;i<=n;i++)a[i].z=atan2(a[i].y-a[1].y,a[i].x-a[1].x);
			sort(a+2,a+n+1,cmp2);
			if(a[1].p==1)
			{
				for(i=2;i<=n;i++)if(a[i].p==n)break;
				printf("1 ");
				for(i=i==n?2:i+1;a[i].p!=n;i=i==n?2:i+1)printf("%d ",a[i].p);
				printf("%d\n",n);
			}
			else if(a[1].p==n)
			{
				for(i=2;i<=n;i++)if(a[i].p==1)break;
				printf("1 ");
				for(i=i==n?2:i+1;a[i].p!=1;i=i==n?2:i+1)printf("%d ",a[i].p);
				printf("%d\n",n);
			}
			else
			{
				for(i=2;i<=n;i++)if(a[i].p==1)break;
				for(int j=i;a[j].p!=n;j=j==n?2:j+1)printf("%d ",a[j].p);
				printf("%d ",a[1].p);
				for(int j=i==2?n:i-1;a[j].p!=n;j=j==2?n:j-1)printf("%d ",a[j].p);
				printf("%d\n",n);
			}
		}
	}
	return 0;
}