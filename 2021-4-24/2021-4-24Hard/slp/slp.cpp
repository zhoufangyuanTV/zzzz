#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
long long a[1010000][6];
int p[1010000],c[1010000];
long long ss=0x3f3f3f3f3f3f3f3fll;
unsigned short seed=114;
inline unsigned short myrand()
{
	seed^=seed<<6;
	seed^=seed>>3;
	seed^=seed<<13;
	return seed;
}
inline long long myabs(long long x){return x<0?-x:x;}
int main()
{
	freopen("slp.in","r",stdin);
	freopen("slp.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int w,x,y,z;scanf("%d%d%d%d",&w,&x,&y,&z);
		a[i][0]=w+x-y-z;
		a[i][1]=w-x+y-z;
		a[i][2]=w-x-y+z;
		a[i][3]=-w+x+y-z;
		a[i][4]=-w+x-y+z;
		a[i][5]=-w-x+y+z;
	}
	int t=20;
	while(t--)
	{
		long long s=0;
		for(int i=1;i<=n;i++)
		{
			p[i]=myrand()%6;
			s+=a[i][p[i]];
		}
		double T=1000000,delta=0.98;
		while(T>1)
		{
			int x=myrand()%n+1,y=myrand()%5;
			if(p[x]<=y)y++;
			long long ns=s-a[x][p[x]]+a[x][y];
			long long ds=myabs(ns)-myabs(s);
			if(ds<0)
			{
				s=ns;
				p[x]=y;
			}
			else if(1.0/65536.0*myrand()<exp(-ds/T)){s=ns;p[x]=y;}
			T=T*delta;
		}
		if(s<ss)
		{
			ss=s;
			for(int i=1;i<=n;i++)c[i]=p[i];
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(c[i]==0)printf("1 1 0 0 ");
		else if(c[i]==1)printf("1 0 1 0 ");
		else if(c[i]==2)printf("1 0 0 1 ");
		else if(c[i]==3)printf("0 1 1 0 ");
		else if(c[i]==4)printf("0 1 0 1 ");
		else printf("0 0 1 1 ");
	}
	return 0;
}