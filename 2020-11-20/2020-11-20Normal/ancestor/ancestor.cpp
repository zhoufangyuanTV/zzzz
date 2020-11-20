#include<cstdio>
#include<cstring>
using namespace std;
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
}a[2220000];int len,last[2220000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int z,in[2220000],out[2220000];
void dfs(int x)
{
	in[x]=++z;
	for(int k=last[x];k>0;k=a[k].next)dfs(a[k].y);
	out[x]=z;
}
int n,c[2220000];
inline int lowbit(int x){return x&-x;}
inline void change(int x,int s)
{
	while(x<=n)
	{
		c[x]+=s;
		x+=lowbit(x);
	}
}
inline int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
int f[2220000];
int main()
{
	freopen("ancestor.in","r",stdin);
	freopen("ancestor.out","w",stdout);
	read(n);
	len=0;memset(last,0,sizeof(last));
	for(int i=2;i<=n;i++)
	{
		int p;read(p);
		ins(p,i);
	}
	dfs(1);
	memset(c,0,sizeof(c));
	f[n]=n;
	change(n,1);
	for(int i=n-1;i>=1;i--)
	{
		int j=i+1;
		while(j<=n&&in[i]<=in[j]&&in[j]<=out[i])j=f[j]+1;
		f[i]=j-1;
		change(i,1);
		change(j,-1);
	}
	for(int i=1;i<=n;i++)printf("%d\n",sum(i));
	return 0;
}