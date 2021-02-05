#include<ctime>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();};
}
struct node
{
	int x,y,next;
}a[2010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int p[1010000];
bool b[1010000],v[1010000];
void dfs(int x)
{
	if(b[x])for(int k=last[x];k>0;k=a[k].next)b[a[k].y]=false;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(v[y]==false)
		{
			v[y]=true;
			dfs(y);
		}
	}
}
int list[1010000];
int ss=0,Ans[1010000];
int xx[1010000],yy[1010000];
int main(int argc,char* argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	srand(time(0));
	int n,m;read(n);read(n);read(m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)p[i]=i;
	random_shuffle(p+1,p+m+1);
	for(int i=1;i<=m;i++){read(xx[i]);read(yy[i]);}
	for(int i=1;i<=m;i++){ins(xx[p[i]],yy[p[i]]);ins(yy[p[i]],xx[p[i]]);}
	int t,A,B;sscanf(argv[3],"%d",&t);sscanf(argv[4],"%d",&A);sscanf(argv[5],"%d",&B);
	while(t--)
	{
		memset(b,true,n+1);
		memset(v,false,n+1);
		for(int i=1;i<=n;i++)p[i]=i;
		random_shuffle(p+1,p+n+1);
		for(int i=1;i<=n;i++)
		{
			if(v[p[i]]==true)continue;
			v[p[i]]=true;
			if(rand()%2==0)dfs(p[i]);
			else
			{
				int head=1,tail=2;list[1]=p[i];
				while(head<tail)
				{
					int x=list[head];
					for(int k=last[x];k>0;k=a[k].next)
					{
						int y=a[k].y;
						if(b[x])b[y]=false;
						if(v[y]==false)v[y]=true,list[tail++]=y;
					}
					head++;
				}
			}
		}
		int s=0;
		for(int i=1;i<=n;i++)s=s+b[i];
		if(s>ss)
		{
			ss=0;
			for(int i=1;i<=n;i++)if(b[i])Ans[++ss]=i;
		}
		if(B<=ss)break;
	}
	printf("%d\n",ss);
	for(int i=1;i<=ss;i++)printf("%d\n",Ans[i]);
	return 0;
}