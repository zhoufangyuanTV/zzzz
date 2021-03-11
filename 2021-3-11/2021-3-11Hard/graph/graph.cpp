#include<cstdio>
#include<cstring>
#include<algorithm>
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
}a[1010000];int len,last[1100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int p[1100],c[1100];
int X,Y,Z;
bool dfs(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=Z)
		{
			if(c[y]==-1)
			{
				c[y]=c[x]^1;
				bool re=dfs(y);
				if(re==false)return re;
			}
			else if(c[x]==c[y])return false;
		}
	}
	return true;
}
int Al,A[1100],Bl,B[1100];
inline bool cmp0(int x,int y){return p[x]>p[y];}
inline bool cmp1(int x,int y){return p[x]<p[y];}
bool bo[1100];
int Ans[1100];
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int t;read(t);
	while(t--)
	{
		int n,m;read(n);read(m);
		len=0;memset(last,0,sizeof(last));
		memset(p,0,sizeof(p));
		for(int i=1;i<=m;i++)
		{
			int x,y;read(x);read(y);
			ins(x,y);ins(y,x);
			p[x]++;p[y]++;
		}
		X=-1;Y=-1;Z=-1;
		for(int i=1;i<=n;i++)
		{
			if(p[i]==2)
			{
				int x=a[last[i]].y,y=a[a[last[i]].next].y;
				for(int k=last[x];k>0;k=a[k].next)
				{
					if(y==a[k].y)
					{
						X=x;Y=y;Z=i;
						p[X]--;p[Y]--;
						break;
					}
				}
				if(Z!=-1)break;
			}
		}
		memset(c,-1,sizeof(c));
		bool bk=true;
		for(int i=1;i<=n;i++)
		{
			if(i!=Z&&c[i]==-1)
			{
				c[i]=1;
				if(dfs(i)==false){bk=false;break;}
			}
		}
		if(bk==false){puts("No");continue;}
		Al=0;Bl=0;
		for(int i=1;i<=n;i++)
		{
			if(c[i]==0)A[++Al]=i;
			else if(c[i]==1)B[++Bl]=i;
		}
		if(Al>0)sort(A+1,A+Al+1,cmp0);
		if(Bl>0)sort(B+1,B+Bl+1,cmp1);
		int R=1000000000;
		if(Z==-1)
		{
			int j=1;
			for(int i=1;i<=Al;i++)
			{
				memset(bo,false,sizeof(bo));
				for(int k=last[A[i]];k>0;k=a[k].next)bo[a[k].y]=true;
				int k;
				for(k=Bl;k>=1;k--)if(bo[B[k]]==false)break;
				if(Bl-k<p[A[i]]){bk=false;break;}
				if(j<=k)
				{
					if(i>1)Ans[B[j]]=Ans[A[i-1]]+R;
					else Ans[B[j]]=0;
					for(j++;j<=k;j++)Ans[B[j]]=Ans[B[j-1]]+1;
				}
				if(i==1)Ans[A[i]]=-R;
				else Ans[A[i]]=Ans[A[i-1]]+1;
				if(j>1&&Ans[A[i]]<Ans[B[j-1]]-R+1)Ans[A[i]]=Ans[B[j-1]]-R+1;
			}
			if(bk&&j<=Bl)
			{
				if(Al>0)Ans[B[j]]=Ans[A[Al]]+R;
				else Ans[B[j]]=0;
				for(j++;j<=Bl;j++)Ans[B[j]]=Ans[B[j-1]]+1;
			}
			if(bk==false)puts("No");
			else
			{
				puts("Yes");
				printf("2000000000 ");
				for(int i=1;i<n;i++)printf("%d ",Ans[i]);
				printf("%d\n",Ans[n]);
			}
		}
		else
		{
			if(c[X]==1)X^=Y^=X^=Y;
			if(Al==p[Y]&&Bl==p[X])
			{
				for(int i=2;i<=Al;i++)
				{
					if(X==A[i])
					{
						A[1]^=A[i]^=A[1]^=A[i];
						break;
					}
				}
				for(int i=1;i<Bl;i++)
				{
					if(Y==B[i])
					{
						B[Bl]^=B[i]^=B[Bl]^=B[i];
						break;
					}
				}
				Ans[X]=-R;Ans[Z]=0;Ans[Y]=R;
				int j=1;
				for(int i=2;i<=Al;i++)
				{
					memset(bo,false,sizeof(bo));
					for(int k=last[A[i]];k>0;k=a[k].next)bo[a[k].y]=true;
					int k;
					for(k=Bl;k>=1;k--)if(bo[B[k]]==false)break;
					if(Bl-k<p[A[i]]){bk=false;break;}
					if(j<=k)
					{
						if(i>2)Ans[B[j]]=Ans[A[i-1]]+R;
						else Ans[B[j]]=1;
						for(j++;j<=k;j++)Ans[B[j]]=Ans[B[j-1]]+1;
					}
					Ans[A[i]]=Ans[A[i-1]]+1;
					if(j>1&&Ans[A[i]]<Ans[B[j-1]]-R+1)Ans[A[i]]=Ans[B[j-1]]-R+1;
				}
				if(bk&&j<Bl)
				{
					if(Al>1)Ans[B[j]]=Ans[A[Al]]+R;
					else Ans[B[j]]=1;
					for(j++;j<Bl;j++)Ans[B[j]]=Ans[B[j-1]]+1;
				}
				if(bk==false)puts("No");
				else
				{
					puts("Yes");
					printf("2000000000 ");
					for(int i=1;i<n;i++)printf("%d ",Ans[i]);
					printf("%d\n",Ans[n]);
				}
			}
			else puts("No");
		}
	}
	return 0;
}