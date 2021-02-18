#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
bool f[51000][1024];
int a[11][51000];
char s[51000];
int sta[51000],top,to[51000];
void dfs(int l,int r)
{
	if(l==r)
	{
		for(int i=0;i<1<<m;i++)f[l][i]=(i|1<<(s[l]-'0'))==i;
		return ;
	}
	dfs(l+1,to[l+1]);
	for(int i=0;i<1<<m;i++)f[l][i]=f[l+1][i];
	for(int i=to[l+1]+1;i<r;i++)
	{
		dfs(i+1,to[i+1]);
		if(s[i]=='<')
		{
			for(int j=0;j<1<<m;j++)f[l][j]&=f[i+1][j];
		}
		else
		{
			for(int j=0;j<1<<m;j++)f[l][j]|=f[i+1][j];
		}
		i=to[i+1];
	}
}
int g[1024],gg[1025];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
inline int lowbit(int x){return x&-x;}
int T;
long long ff[51000][11],FF[11];
void ddfs(int l,int r)
{
	if(l==r){ff[l][s[l]-'0']=1;return ;}
	ddfs(l+1,to[l+1]);
	for(int i=0;i<m;i++)ff[l][i]=ff[l+1][i];
	for(int i=to[l+1]+1;i<r;i++)
	{
		ddfs(i+1,to[i+1]);
		for(int j=0;j<m;j++){FF[j]=ff[l][j];ff[l][j]=0;}
		if(s[i]!='>')
		{
			for(int j=0;j<m;j++)
			{
				for(int k=0;k<m;k++)
				{
					if(a[j][T]<a[k][T])ff[l][j]=(ff[l][j]+FF[j]*ff[i+1][k])%1000000007;
					else ff[l][k]=(ff[l][k]+FF[j]*ff[i+1][k])%1000000007;
				}
			}
		}
		if(s[i]!='<')
		{
			for(int j=0;j<m;j++)
			{
				for(int k=0;k<m;k++)
				{
					if(a[j][T]>a[k][T])ff[l][j]=(ff[l][j]+FF[j]*ff[i+1][k])%1000000007;
					else ff[l][k]=(ff[l][k]+FF[j]*ff[i+1][k])%1000000007;
				}
			}
		}
		i=to[i+1];
	}
}
int main()
{
	freopen("expr.in","r",stdin);
	freopen("expr.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
	}
	s[1]='(';scanf("%s",s+2);
	int len=strlen(s+1)+1;s[len]=')';
	top=0;bool bk=false;
	for(int i=1;i<=len;i++)
	{
		if(s[i]=='(')sta[++top]=i;
		else if(s[i]==')')to[sta[top--]]=i;
		else to[i]=i;
		if(s[i]=='?')bk=true;
	}
	if(bk==true)
	{
		long long ss=0;
		for(T=1;T<=n;T++)
		{
			memset(ff,0,sizeof(ff));
			ddfs(1,len);
			for(int j=0;j<m;j++)ss=(ss+ff[1][j]*a[j][T])%1000000007;
		}
		printf("%lld\n",ss);
		return 0;
	}
	memset(f,false,sizeof(f));
	dfs(1,len);
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		int sss=0;g[0]=0x3f3f3f3f;
		for(int j=0;j<m;j++)gg[1<<j]=a[j][i];
		for(int j=1;j<1<<m;j++)
		{
			g[j]=mymin(g[j-lowbit(j)],gg[lowbit(j)]);
			if(f[1][j])sss=mymax(sss,g[j]);
		}
		ss=(ss+sss)%1000000007;
	}
	printf("%d\n",ss);
	return 0;
}
