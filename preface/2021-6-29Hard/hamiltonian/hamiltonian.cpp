#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template<typename T>
inline void read(T &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
struct node
{
	int x,y,next;
}a[2010000];int len,last[2010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool b[1010000];
int cnt,p[1010000];
int sta[1010000],top;
long long c[2010000],siz[2010000];
int dfn[1010000];
long long f[2010000],mid;
void dfs(int x)
{
	f[x]=mid*siz[x]-c[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		dfs(y);
		f[x]+=f[y];
	}
	if(f[x]<0)f[x]=0;
}
int main()
{
	freopen("hamiltonian.in","r",stdin);
	freopen("hamiltonian.out","w",stdout);
	int n,m;read(n);read(m);
	for(int i=1;i<=n;i++)read(p[i]);
	for(int i=1;i<=n;i++)
	{
		read(c[i]);
		siz[i]=1;
	}
	c[0]=siz[0]=0;
	cnt=n;
	memset(b,false,sizeof(b));
	len=0;memset(last,0,sizeof(last));
	memset(dfn,0,sizeof(dfn));
	for(int i=1;i<=n;i++)
	{
		if(b[i]==false)
		{
			int x=i;
			top=0;
			while(x!=-1&&b[x]==false)
			{
				b[x]=true;
				sta[++top]=x;
				x=p[x];
			}
			if(x!=-1&&dfn[x]==0)
			{
				cnt++;
				c[cnt]=siz[cnt]=0;
				int y;
				do
				{
					y=sta[top--];
					dfn[y]=cnt;
					c[cnt]+=c[y];
					siz[cnt]+=siz[y];
				}while(y!=x);
				ins(0,cnt);
				sta[top+1]=cnt;
			}
			else if(x!=-1)sta[top+1]=dfn[x];
			else sta[top+1]=0;
			for(int i=1;i<=top;i++)
			{
				ins(sta[i+1],sta[i]);
				dfn[sta[i]]=sta[i];
			}
		}
	}
	long long l=0,r=1000000000+m/n;
	while(l<r)
	{
		mid=(l+r+1)/2;
		dfs(0);
		if(f[0]<=m)l=mid;
		else r=mid-1;
	}
	printf("%lld\n",l);
	return 0;
}
