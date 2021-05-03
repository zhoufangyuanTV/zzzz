#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct point
{
	long double x,y;
	int p;
}p[4100];
inline long double multi(point &p0,point &p1,point &p2)
{
	long double x1=p1.x-p0.x,y1=p1.y-p0.y;
	long double x2=p2.x-p0.x,y2=p2.y-p0.y;
	return x1*y2-x2*y1;
}
inline bool sgn(long double x){return x>0;}
long double ss=0,s;
int n,a[4100],c[4100];
void dfs(int k)
{
	if(k==n*2+1)
	{
		/*
		if(ss<s)
		{
			ss=s;
			for(int i=1;i<=n*2;i++)c[p[i].p]=p[a[i]].p;
		}
		*/
		if(10000000000<s)
		{
			for(int i=1;i<=n*2;i++)c[p[i].p]=p[a[i]].p;
			for(int i=1;i<n*2;i++)printf("%d ",c[i]);
			printf("%d\n",c[n*2]);
			exit(0);
		}
	}
	else if(a[k]!=-1)dfs(k+1);
	else
	{
		for(int i=k+1;i<=n*2;i++)
		{
			if(a[i]==-1)
			{
				bool bk=true;
				for(int j=1;j<k;j++)
				{
					if(j<a[j])
					{
						if(sgn(multi(p[i],p[k],p[j]))!=sgn(multi(p[i],p[k],p[a[j]]))&&sgn(multi(p[j],p[a[j]],p[i]))!=sgn(multi(p[j],p[a[j]],p[k]))){bk=false;break;}
					}
				}
				if(bk)
				{
					long double dis=sqrt((p[i].x-p[k].x)*(p[i].x-p[k].x)+(p[i].y-p[k].y)*(p[i].y-p[k].y));
					s+=dis;
					a[i]=k;
					a[k]=i;
					dfs(k+1);
					a[i]=-1;
					a[k]=-1;
					s-=dis;
				}
			}
		}
	}
}
int main(int argc,char* argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++)
	{
		scanf("%Lf%Lf",&p[i].x,&p[i].y);
		p[i].p=i;
	}
	random_shuffle(p+1,p+n*2+1);
	memset(a,-1,sizeof(a));
	s=0;dfs(1);
	for(int i=1;i<n*2;i++)printf("%d ",c[i]);
	printf("%d\n",c[n*2]);
	return 0;
}
