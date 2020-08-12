#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
bool c[110000][20];int w;
long long And[110000],Or[110000],Xor[110000][2];
void dfs(int x,int fa)
{
	if(c[x][w])And[x]=1,Or[x]=0,Xor[x][0]=0,Xor[x][1]=1;
	else And[x]=0,Or[x]=1,Xor[x][0]=1,Xor[x][1]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			if(c[x][w])And[x]+=And[y],Xor[x][0]+=Xor[y][1],Xor[x][1]+=Xor[y][0];
			else Or[x]+=Or[y],Xor[x][0]+=Xor[y][0],Xor[x][1]+=Xor[y][1];
		}
	}
}
long long anD,OR,xOr;
void dfs(int x,int fa,long long aNd,long long oR,long long xOr0,long long xOr1)
{
	if(c[x][w])
	{
		anD+=aNd+And[x];oR=0;
		xOr0^=xOr1^=xOr0^=xOr1;
		xOr+=xOr1+Xor[x][1];
	}
	else
	{
		aNd=0;OR+=oR+Or[x];
		xOr+=xOr1+Xor[x][1];
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs(y,x,aNd+And[x]-(c[x][w]?And[y]:0),oR+Or[x]-(!c[x][w]?Or[y]:0),xOr0+Xor[x][0]-Xor[y][c[x][w]],xOr1+Xor[x][1]-Xor[y][1-c[x][w]]);
	}
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			int x;scanf("%d",&x);
			for(int j=0;j<20;j++)
			{
				c[i][j]=x&1;x>>=1;
			}
		}
		len=0;memset(last,0,sizeof(last));
		for(int i=1;i<n;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			ins(x,y);ins(y,x);
		}
		double ANDS=0,ORS=0,XORS=0;
		for(int i=0;i<20;i++)
		{
			w=i;
			dfs(1,0);
			anD=0;OR=0;xOr=0;
			dfs(1,0,0,0,0,0);
			ANDS+=(1<<i)*((double)anD/n/n);
			ORS+=(1<<i)*(1-(double)OR/n/n);
			XORS+=(1<<i)*((double)xOr/n/n);
		}
		printf("%.3lf %.3lf %.3lf\n",ANDS,ORS,XORS);
	}
	return 0;
}