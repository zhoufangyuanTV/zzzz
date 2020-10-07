#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[1100];int len,last[110];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int p[110],c[110];
bool mp[110][110];
int cc[110];
int list[110];
int f[11000][110];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
	int n,m,C,T;scanf("%d%d%d%d",&n,&m,&C,&T);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i],&c[i]);
		if(c[i]>C)c[i]=C;
	}
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);
	}
	memset(mp,false,sizeof(mp));
	for(int i=1;i<=n;i++)
	{
		int head=1,tail=2;
		list[head]=i;cc[i]=c[i];
		while(head<tail)
		{
			int x=list[head];
			mp[i][x]=true;
			if(cc[x]>0)
			{
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(mp[i][y]==false)
					{
						cc[y]=cc[x]-1;
						list[tail++]=y;
					}
				}
			}
			head++;
		}
	}
	while(T--)
	{
		int s,q,d;scanf("%d%d%d",&s,&q,&d);
		memset(f,0,sizeof(f));f[0][s]=0;
		int ss=-1;
		for(int i=0;i<=q;i++)
		{
			for(int x=1;x<=n;x++)
			{
				if(f[i][x]>=d)
				{
					ss=i;break;
				}
				for(int y=1;y<=n;y++)
				{
					if(i+p[x]<=q&&mp[x][y])f[i+p[x]][y]=mymax(f[i+p[x]][y],f[i][x]+1);
				}
			}
			if(ss!=-1)break;
		}
		printf("%d\n",ss);
	}
	return 0;
}