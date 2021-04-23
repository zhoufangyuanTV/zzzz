#include<cstdio>
#include<cstring>
#include<vector>
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
int z,dfn[110000],low[110000];
int belong[110000],cnt;vector<int> c[110000];
int sta[110000],top;bool v[110000];
inline int mymin(int x,int y){return x<y?x:y;}
void dfs(int x)
{
	dfn[x]=low[x]=++z;sta[++top]=x;v[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(dfn[y]==-1)
		{
			dfs(y);
			low[x]=mymin(low[x],low[y]);
		}
		else if(v[y]==true)low[x]=mymin(low[x],dfn[y]);
	}
	if(dfn[x]==low[x])
	{
		cnt++;
		c[cnt].clear();
		int i;
		do
		{
			i=sta[top--];
			belong[i]=cnt;
			c[cnt].push_back(i);
			v[i]=false;
		}while(i!=x);
	}
}
vector<int> e[110000];
int p[110000],pos[110];
int f[110000];
char S[51000],h[110];
struct tiao
{
	int x,y;
	char hi,hj;
}t[110000];
int list[110000];
char Ans[51000];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n,d,m;scanf("%d%d%s%d",&n,&d,S+1,&m);
	int s=0;
	for(int i=1;i<=n;i++)
	{
		if(S[i]=='x')pos[++s]=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&t[i].x);
		scanf("%s",h+1);
		t[i].hi=h[1];
		scanf("%d",&t[i].y);
		scanf("%s",h+1);
		t[i].hj=h[1];
	}
	for(int zt=0;zt<1<<d;zt++)
	{
		for(int i=1;i<=d;i++)
		{
			if(zt>>i-1&1)S[pos[i]]='C';
			else S[pos[i]]='c';
		}
		len=0;memset(last,0,sizeof(last));
		int T=n*2+1,F=n*2+2;
		for(int i=1;i<=m;i++)
		{
			int X=t[i].x,Y=t[i].y;
			int x,nx,y,ny;
			if(t[i].hi==S[X])x=T,nx=F;
			else if(S[X]=='C'||t[i].hi+32==S[X])x=F,nx=T;
			else
			{
				char an=230-S[X]-t[i].hi;
				if(t[i].hi<an)x=X*2-1,nx=X*2;
				else x=X*2,nx=X*2-1;
			}
			if(t[i].hj==S[Y])y=T,ny=F;
			else if(S[Y]=='C'||t[i].hj+32==S[Y])y=F,ny=T;
			else
			{
				char an=230-S[Y]-t[i].hj;
				if(t[i].hj<an)y=Y*2-1,ny=Y*2;
				else y=Y*2,ny=Y*2-1;
			}
			ins(x,y);
			ins(ny,nx);
		}
		memset(dfn,-1,sizeof(dfn));
		memset(v,false,sizeof(v));
		z=cnt=top=0;
		dfs(T);
		if(dfn[F]==-1)dfs(F);
		for(int i=1;i<=n;i++)
		{
			if(S[i]=='C')continue;
			if(dfn[i*2-1]==-1)dfs(i*2-1);
			if(dfn[i*2]==-1)dfs(i*2);
		}
		memset(f,-1,sizeof(f));
		bool bk=true;
		for(int i=1;i<=cnt;i++)
		{
			for(int j=0;j<c[i].size();j++)
			{
				f[(c[i][j]+1)/2]++;
				if(f[(c[i][j]+1)/2]==1){bk=false;break;}
			}
			if(bk==false)break;
			for(int j=0;j<c[i].size();j++)f[(c[i][j]+1)/2]=-1;
		}
		if(bk==false)continue;
		for(int i=1;i<=cnt;i++)e[i].clear(),p[i]=0;
		for(int i=1;i<=len;i++)
		{
			if(belong[a[i].x]==belong[a[i].y])continue;
			e[belong[a[i].y]].push_back(belong[a[i].x]);
			p[belong[a[i].x]]++;
		}
		int head=1,tail=1;
		for(int i=1;i<=cnt;i++)if(p[i]==0)list[tail++]=i;
		f[belong[F]]=0;
		while(head<tail)
		{
			int x=list[head];
			if(f[x]==-1)f[x]=1;
			if(f[x]==1)
			{
				for(int i=0;i<c[x].size();i++)
				{
					if(c[x][i]&1)f[belong[c[x][i]+1]]=0;
					else f[belong[c[x][i]-1]]=0;
				}
				for(int i=0;i<e[x].size();i++)
				{
					int y=e[x][i];
					p[y]--;
					if(p[y]==0)list[tail++]=y;
				}
			}
			else
			{
				for(int i=0;i<e[x].size();i++)
				{
					int y=e[x][i];
					f[y]=0;
					p[y]--;
					if(p[y]==0)list[tail++]=y;
				}
			}
			head++;
		}
		for(int i=1;i<=n;i++)
		{
			if(f[belong[i*2-1]]==0&&f[belong[i*2]]==0){bk=false;break;}
		}
		if(bk==false||f[belong[T]]==0)continue;
		for(int i=1;i<=n;i++)
		{
			if(S[i]=='C'){Ans[i]='C';continue;}
			if(f[belong[i*2-1]]==1)
			{
				if(S[i]=='a')Ans[i]='B';
				else Ans[i]='A';
			}
			else
			{
				if(S[i]=='c')Ans[i]='B';
				else Ans[i]='C';
			}
		}
		Ans[n+1]='\0';
		puts(Ans+1);
		return 0;
	}
	puts("-1");
	return 0;
}