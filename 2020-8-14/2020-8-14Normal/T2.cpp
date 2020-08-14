#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define PI 3.14159265358979323846
int nm,c[2100];
inline int lowbit(int x){return x&-x;}
void change(int x,int s)
{
	while(x<=nm)
	{
		c[x]+=s;
		x+=lowbit(x);
	}
}
int ans(int x)
{
	int s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
inline long double mo(long double x){return x>PI?x-2*PI:x;}
inline long double left(long double x,long double y)
{
	if(y<0)return y<x&&x<y+PI;
	else return y<x||x<mo(y+PI);
}
long double f[1100][1100],pp[1100],xx[1100],yy[1100];
struct point{long double x,y,z;int p,pz;}a[2100];
long double zz[2100];
inline bool cmp(point x,point y){return x.z<y.z;}
int main()
{
	int n,m;scanf("%d%d",&n,&m);nm=n+m;
	for(int i=1;i<=n;i++)
	{
		scanf("%Lf%Lf",&a[i].x,&a[i].y);
		a[i].z=atan2(a[i].y,a[i].x);
		zz[i]=a[i].z;a[i].p=-i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%Lf%Lf%Lf",&xx[i],&yy[i],&pp[i]);
		a[i+n].x=xx[i];a[i+n].y=yy[i];
		a[i+n].z=atan2(yy[i],xx[i]);
		zz[i+n]=a[i+n].z;a[i+n].p=i;
	}
	sort(zz+1,zz+n+m+1);
	for(int i=1;i<=n+m;i++)a[i].pz=lower_bound(zz+1,zz+n+m+1,a[i].z)-zz;
	for(int i=1;i<=m;i++)
	{
		for(int j=n+1;j<=n+m;j++)
		{
			if(i!=a[j].p)a[j].z=atan2(a[j].y-yy[i],a[j].x-xx[i]);
		}
		sort(a+n+1,a+n+m+1,cmp);
		int k=n+1;
		while(k<=n+m&&a[k].z<0)k++;
		long double ppp=pp[i];
		if(k==n+m+1)k=n+1;
		for(int l=k;l<=n+m;l++)
		{
			if(i!=a[l].p)ppp*=1-pp[a[l].p];
		}
		for(int j=n+1;j<=n+m;j++)
		{
			while(k!=j&&left(a[k].z,a[j].z))
			{
				if(i!=a[k].p)ppp/=(1-pp[a[k].p]);
				k++;if(k==n+m+1)k=n+1;
			}
			if(k==j)ppp=pp[i];
			if(i!=a[j].p)
			{
				f[i][a[j].p]=ppp*pp[a[j].p];
				ppp*=1-pp[a[j].p];
			}
		}
	}
	long double ss=0;
	for(int i=1;i<=m;i++)
	{
		long double iz=-atan2(-yy[i],-xx[i]);
		for(int j=1;j<=n+m;j++)
		{
			if(i!=a[j].p)
			{
				a[j].z=-atan2(a[j].y-yy[i],a[j].x-xx[i]);
				if(a[j].z>iz)a[j].z-=2*PI;
			}
		}
		sort(a+1,a+n+m+1,cmp);
		memset(c,0,sizeof(c));
		for(int j=1;j<=n+m;j++)
		{
			if(a[j].z+PI>iz)break;
			if(a[j].p<0)
			{
				change(a[j].pz,1);
			}
			else
			{
				if(i!=a[j].p)
				{
					int s=ans(a[j].pz);
					ss+=f[i][a[j].p]*s;
					ss-=f[a[j].p][i]*s;
				}
			}
		}
	}
	printf("%.9Lf\n",ss);
	return 0;
}