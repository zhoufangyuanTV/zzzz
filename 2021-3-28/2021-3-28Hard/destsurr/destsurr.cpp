#include<cstdio>
#include<cstring>
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
int a[2010000];
int root;
struct node
{
	int l,r,size;
}tr[2010000];
int sta[2010000],top;
long long f[2010000];
void dfs(int x)
{
	if(x==0)return ;
	int lc=tr[x].l,rc=tr[x].r;
	dfs(lc);dfs(rc);
	tr[x].size=tr[lc].size+tr[rc].size+1;
	f[x]=f[lc]*f[rc]*2%998244353;
	f[x]=(f[x]+tr[lc].size*(f[rc]+998244352)+tr[rc].size*(f[lc]+998244352))%998244353;
}
int main()
{
	freopen("destsurr.in","r",stdin);
	freopen("destsurr.out","w",stdout);
	int t;read(t);
	while(t--)
	{
		int n;read(n);
		top=0;
		for(int i=1;i<=n;i++)
		{
			read(a[i]);
			int last=0;
			while(top>0&&a[i]<a[sta[top]])last=sta[top--];
			if(top>0)tr[sta[top]].r=i;
			sta[++top]=i;
			tr[i].l=last;
			tr[i].r=0;
		}
		root=sta[1];
		tr[0].size=0;
		f[0]=1;
		dfs(root);
		printf("%lld\n",(f[root]+n)%998244353);
	}
	return 0;
}