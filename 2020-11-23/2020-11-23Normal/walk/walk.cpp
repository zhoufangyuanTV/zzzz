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
struct node
{
	int x,y,next;
}a[410000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool b[110000];
int p[110000];
int stx;
bool dfs(int x,int fa)
{
	b[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			if(b[y]==false)
			{
				if(dfs(y,x)==false)return false;
			}
			else if(x!=stx&&y!=stx)return false;
		}
	}
	return true;
}
int main()
{
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
	int t;read(t);
	while(t--)
	{
		int n,m;read(n);read(m);
		memset(p,0,sizeof(p));
		len=0;memset(last,0,sizeof(last));
		for(int i=1;i<=m;i++)
		{
			int x,y;read(x);read(y);
			ins(x,y);ins(y,x);
			p[x]++;p[y]++;
		}
		bool bk=true;
		int st=0,ts=0,S=0;
		for(int i=1;i<=n;i++)
		{
			if(p[i]&1)
			{
				if(st==0)st=i;
				else if(ts==0)ts=i;
				else{bk=false;break;}
			}
			else if(p[S]<p[i])S=i;
		}
		if(st!=0&&ts==0||bk==false){puts("NO");continue;}
		memset(b,false,sizeof(b));
		if(st==0)stx=S,puts(dfs(S,0)?"YES":"NO");
		else
		{
			stx=st;
			if(dfs(st,0))puts("YES");
			else
			{
				memset(b,false,sizeof(b));
				stx=ts;puts(dfs(ts,0)?"YES":"NO");
			}
		}
	}
	return 0;
}