#include<cstdio>
#include<cstring>
using namespace std;
namespace A
{
	struct node
	{
		int x,y,next;
	}a[210000];int len,last[1100];
	inline void ins(int x,int y)
	{
		len++;a[len].x=x;a[len].y=y;
		a[len].next=last[x];last[x]=len;
	}
}
namespace B
{
	struct node
	{
		int x,y,next;
	}a[210000];int len,last[1100];
	inline void ins(int x,int y)
	{
		len++;a[len].x=x;a[len].y=y;
		a[len].next=last[x];last[x]=len;
	}
}
int Ans[210000];
int d[1100],D1[1100],D2[1100];
int tr[2048],trlen;
inline int cmp(int x,int y){return d[x]>d[y]?x:y;}
inline void change(int x)
{
	x=(trlen+x)>>1;
	while(x>0)
	{
		tr[x]=cmp(tr[x<<1],tr[(x<<1)+1]);
		x>>=1;
	}
}
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	A::len=0;memset(A::last,0,sizeof(A::last));
	B::len=0;memset(B::last,0,sizeof(B::last));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		A::ins(x,y);B::ins(y,x);
	}
	trlen=1;
	while(trlen+1<n)trlen=(trlen<<1)+1;
	for(int i=1;i<=n;i++)tr[trlen+i]=i;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)D1[j]=D2[j]=0;
		{
			using namespace A;
			d[i]=m+1;
			for(int j=i+1;j<=n;j++)d[j]=0;
			for(int j=trlen;j>=1;j--)tr[j]=cmp(tr[j<<1],tr[(j<<1)+1]);
			for(int j=i;j<=n;j++)
			{
				int x=tr[1];
				if(d[x]<1)break;
				D1[x]=d[x];
				d[x]=-1;
				change(x);
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(i<=y)
					{
						if(d[y]!=-1&&d[y]<mymin(D1[x],k))
						{
							d[y]=mymin(D1[x],k);
							change(y);
						}
					}
				}
			}
		}
		{
			using namespace B;
			d[i]=m+1;
			for(int j=i+1;j<=n;j++)d[j]=0;
			for(int j=trlen;j>=1;j--)tr[j]=cmp(tr[j<<1],tr[(j<<1)+1]);
			for(int j=i;j<=n;j++)
			{
				int x=tr[1];
				if(d[x]<1)break;
				D2[x]=d[x];
				d[x]=-1;
				change(x);
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(i<=y)
					{
						if(d[y]!=-1&&d[y]<mymin(D2[x],k))
						{
							d[y]=mymin(D2[x],k);
							change(y);
						}
					}
				}
			}
		}
		for(int j=i;j<=n;j++)
		{
			if(D1[j]>0&&D2[j]>0)Ans[mymin(D1[j],D2[j])-1]++;
		}
	}
	for(int i=m-1;i>=0;i--)Ans[i]+=Ans[i+1];
	for(int i=0;i<m;i++)printf("%d ",Ans[i]);
	printf("%d\n",Ans[m]);
	return 0;
}
