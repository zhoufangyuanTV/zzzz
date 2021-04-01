#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int a[2010000],b[2010000],g[2010000],h[2010000];
bool c[2010000],d[2010000],e[2010000],f[2010000];
inline bool cmp1(int x,int y){return a[x]<a[y];}
inline bool cmp2(int x,int y){return b[x]<b[y];}
int main()
{
	freopen("delidish.in","r",stdin);
	freopen("delidish.out","w",stdout);
	int T;read(T);
	while(T--)
	{
		int n,m;read(n);read(m);
		for(int i=1;i<=n;i++)read(a[i]);
		for(int i=1;i<=m;i++)read(b[i]);
		for(int i=1;i<=n;i++)c[i]=false,e[i]=true,g[i]=i;
		for(int i=1;i<=m;i++)d[i]=false,f[i]=true,h[i]=i;
		sort(g+1,g+n+1,cmp1);
		sort(h+1,h+m+1,cmp2);
		int i=1,j=1,k=1,l=1;
		for(int t=1;t<=n;t++)
		{
			while(k<=m&&b[h[k]]<t)
			{
				f[h[k]]=false;
				k++;
			}
			for(;j<=a[t];j++)
			{
				if(f[j]==false)continue;
				d[j]=true;
				while(l<=n&&a[g[l]]<j)
				{
					e[g[l]]=false;
					l++;
				}
				if(i<=t)i=t+1;
				for(;i<=b[j];i++)if(e[i])c[i]=true;
			}
		}
		int ss=0;
		for(int i=1;i<=n;i++)ss+=c[i]==false;
		for(int i=1;i<=m;i++)ss+=d[i]==false;
		printf("%d\n",ss);
	}
	return 0;
}