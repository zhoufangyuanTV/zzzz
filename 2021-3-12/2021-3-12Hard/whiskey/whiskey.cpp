#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;struct F{int a,b,c;}f[510000];
inline bool cmp(F x,F y){return x.c>y.c;}
struct S{int a,b;}s[510000];
inline int mymax(int x,int y){return x>y?x:y;}
struct T{int a,b;}t[510000];
inline bool Tcmp(T x,T y){return x.a>y.a;}
struct E{int a,b;}e[510000];
inline bool Ecmp(E x,E y){return x.b>y.b;}
int main()
{
	freopen("whiskey.in","r",stdin);
	freopen("whiskey.out","w",stdout);
	int n,x,y,z;scanf("%d%d%d%d",&n,&x,&y,&z);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&f[i].a,&f[i].b,&f[i].c);
	sort(f+1,f+n+1,cmp);
	long long ss=0;
	int a=0,b=0;
	for(int i=z,j=1;i>=1;i--)
	{
		while(j<=n&&i==f[j].c)
		{
			a=mymax(a,f[j].a);
			b=mymax(b,f[j].b);
			j++;
		}
		ss=ss+1ll*a*y+1ll*x*b-1ll*a*b;
		s[i].a=a;s[i].b=b;
	}
	for(int i=1;i<=n;i++)e[i].a=t[i].a=f[i].a,e[i].b=t[i].b=f[i].b;
	sort(t+1,t+n+1,Tcmp);sort(e+1,e+n+1,Ecmp);
	a=x;b=y;int bb=0,aa=0;
	long long sss=0;
	for(int i=1,j=1,k=1;i<=z;i++)
	{
		while(s[i].a<a)
		{
			while(j<=n&&a==t[j].a)
			{
				bb=mymax(bb,t[j].b);
				j++;
			}
			if(b<bb)sss=sss+bb-b;
			a--;
		}
		while(s[i].b<b)
		{
			while(k<=n&&b==e[k].b)
			{
				aa=mymax(aa,e[k].a);
				k++;
			}
			if(a<aa)sss=sss+aa-a;
			b--;
		}
		ss=ss+sss;
	}
	printf("%lld\n",1ll*x*y*z-ss);
	return 0;
}