#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define Pi 3.14159265358979323846
inline int lowbit(int x){return x&-x;}
int nn,cc[2100];
void change(int x,int s)
{
	while(x<=nn)
	{
		cc[x]+=s;
		x+=lowbit(x);
	}
}
int ans(int x)
{
	int s=0;
	while(x>0)
	{
		s+=cc[x];
		x-=lowbit(x);
	}
	return s;
}
struct node
{
	long double x,y,z;int p;
}a[2100];long double b[2100];
inline bool cmp(node x,node y){return x.z<y.z;}
int f[1100][1100],c[1100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);nn=n+m;
	for(int i=1;i<=n;i++)scanf("%Lf%Lf",&a[i].x,&a[i].y);
	for(int i=1;i<=m;i++)scanf("%Lf%Lf%d",&a[n+i].x,&a[n+i].y,&c[i]);
	for(int i=1;i<=n+m;i++)
	{
		a[i].x+=10001;a[i].y+=10001;a[i].p=i;
		a[i].z=atan2(a[i].y,a[i].x);
	}
	sort(a+1,a+n+m+1,cmp);
	for(int i=1;i<=n+m;i++)
	{
		if(a[i].p<=n)
		{
			long double g=a[i].z-Pi;
			for(int j=i+1;j<=n+m;j++)
			{
				b[j]=atan2(a[j].y-a[i].y,a[j].x-a[i].x);
				if(b[j]<0)b[j]=g-b[j];
				else b[j]=g-b[j]+2*Pi;
			}
			sort(b+i+1,b+n+m+1);
			memset(cc,0,sizeof(cc));
			for(int j=i+1;j<=n+m;j++)
			{
				long double bg=atan2(a[j].y-a[i].y,a[j].x-a[i].x);
				if(bg<0)bg=g-bg;
				else bg=g-bg+2*Pi;
				if(a[j].p<=n)
				{
					f[a[i].p][a[j].p]=ans(lower_bound(b+i+1,b+n+m+1,bg)-b-i);
					f[a[j].p][a[i].p]=-f[a[i].p][a[j].p];
				}
				else
				{
					change(lower_bound(b+i+1,b+n+m+1,bg)-b-i,c[a[j].p-n]);
				}
			}
		}
	}
	int q;scanf("%d",&q);
	while(q--)
	{
		int t;scanf("%d",&t);
		int ss=0;int st;
		scanf("%d",&st);
		int ed=st;
		for(int i=2;i<=t;i++)
		{
			int p;scanf("%d",&p);
			ss=ss+f[ed][p];
			ed=p;
		}
		ss=ss+f[ed][st];
		if(ss<0)printf("%d\n",-ss);
		else printf("%d\n",ss);
	}
	return 0;
}