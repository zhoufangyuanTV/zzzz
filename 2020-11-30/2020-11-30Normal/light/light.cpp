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
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
inline long long mymin(long long x,long long y){return x<y?x:y;}
long long f[510000][3][2];
char str[510000];
int tot[510000];
void dfs(int x,int fa)
{
	tot[x]=str[x]=='0';
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			tot[x]+=tot[y];
		}
	}
}
long long ff[3][2],ss;
void treedp(int x,int fa)
{
	int c=str[x]-'0';
	f[x][0][c^1]=f[x][1][c^1]=f[x][2][c^1]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&tot[y]>0)
		{
			treedp(y,x);
			ff[0][0]=f[x][0][0];ff[1][1]=f[x][1][1];ff[2][0]=f[x][2][0];ff[0][1]=f[x][0][1];ff[1][0]=f[x][1][0];ff[2][1]=f[x][2][1];
			f[x][0][0]=mymin(ff[0][1]+f[y][0][1]+1,ff[0][0]+f[y][0][0]+3);
			f[x][0][1]=mymin(ff[0][0]+f[y][0][1]+1,ff[0][1]+f[y][0][0]+3);
			f[x][1][0]=mymin(mymin(ff[1][1]+f[y][0][1]+1,ff[1][0]+f[y][0][0]+3),mymin(ff[0][0]+f[y][1][1],ff[0][1]+f[y][1][0]+2));
			f[x][1][1]=mymin(mymin(ff[1][0]+f[y][0][1]+1,ff[1][1]+f[y][0][0]+3),mymin(ff[0][1]+f[y][1][1],ff[0][0]+f[y][1][0]+2));
			f[x][2][0]=mymin(mymin(ff[2][1]+f[y][0][1]+1,ff[2][0]+f[y][0][0]+3),mymin(ff[1][0]+f[y][1][1],ff[1][1]+f[y][1][0]+2));
			f[x][2][0]=mymin(f[x][2][0],mymin(ff[0][0]+f[y][2][0]+1,ff[0][1]+f[y][2][1]+3));
			f[x][2][1]=mymin(mymin(ff[2][0]+f[y][0][1]+1,ff[2][1]+f[y][0][0]+3),mymin(ff[1][1]+f[y][1][1],ff[1][0]+f[y][1][0]+2));
			f[x][2][1]=mymin(f[x][2][1],mymin(ff[0][1]+f[y][2][0]+1,ff[0][0]+f[y][2][1]+3));
		}
	}
	if(tot[1]==tot[x])ss=mymin(ss,f[x][2][1]);
}
int main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	int n;read(n);scanf("%s",str+1);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	dfs(1,0);
	memset(f,63,sizeof(f));
	ss=0x3f3f3f3f3f3f3f3fll;
	treedp(1,0);
	printf("%lld\n",ss);
	return 0;
}