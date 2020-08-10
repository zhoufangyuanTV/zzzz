#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next,other;
}a[21000];int len,last[5100];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[len-1].other=len;
	a[len].other=len-1;
}
int st,ed;
int dep[5100];
int list[5100];
bool pand()
{
	memset(dep,-1,sizeof(dep));dep[st]=1;
	int head=1,tail=2;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(dep[y]==-1&&a[k].c>0)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed]!=-1;
}
bool b[5100];
int cur[5100];
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==ed)return f;
	if(b[x]==false)return 0;
	int used=0;
	for(int &k=cur[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(a[k].c>0&&dep[y]==dep[x]+1&&used<f)
		{
			int tt=find(y,mymin(a[k].c,f-used));
			used+=tt;
			a[k].c-=tt;
			a[a[k].other].c+=tt;
			if(used==f)break;
		}
	}
	if(used==0)b[x]=false;
	return used;
}
int map[110][110];
int main()
{
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	st=n*m*2+1;ed=n*m*2+2;
	len=0;memset(last,0,sizeof(last));
	int sr=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			ins((i-1)*m+j,n*m+(i-1)*m+j,0x3f3f3f3f);
			if(map[i][j]<0)
			{
				if(map[i][j]==-3||map[i][j]==-4)ins(st,(i-1)*m+j,0x3f3f3f3f);
				if(map[i][j]==-1||map[i][j]==-2)ins(n*m+(i-1)*m+j,ed,0x3f3f3f3f);
				int s=0;
				switch(map[i][j])
				{
					case -3:map[i][j]=0;for(int k=j-1;k>=1;k--)if(s<map[i][k])s=map[i][k];
					for(int k=j-1;k>=1;k--)ins((i-1)*m+k+1,(i-1)*m+k,s-map[i][k+1]);break;
					case -4:map[i][j]=0;for(int k=j+1;k<=m;k++)if(s<map[i][k])s=map[i][k];
					for(int k=j+1;k<=m;k++)ins((i-1)*m+k-1,(i-1)*m+k,s-map[i][k-1]);break;
					case -1:map[i][j]=0;for(int k=i-1;k>=1;k--)if(s<map[k][j])s=map[k][j];
					for(int k=i-1;k>=1;k--)ins(n*m+(k-1)*m+j,n*m+k*m+j,s-map[k+1][j]);break;
					case -2:map[i][j]=0;for(int k=i+1;k<=n;k++)if(s<map[k][j])s=map[k][j];
					for(int k=i+1;k<=n;k++)ins(n*m+(k-1)*m+j,n*m+(k-2)*m+j,s-map[k-1][j]);break;
				}
				sr+=s;
			}
		}
	}
	int ss=0;
	while(pand())
	{
		memset(b,true,sizeof(b));
		for(int i=1;i<=ed;i++)cur[i]=last[i];
		ss+=find(st,0x3f3f3f3f);
	}
	printf("%d\n",sr-ss);
	return 0;
}