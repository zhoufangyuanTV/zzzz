#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
bitset<110> f[410][110];
int len,n,m;
char A[110],B[110];
int nxt[110];
void dfs(int l,int r)
{
	int now=++len;
	for(int i=1;i<=m+1;i++)f[now][i].reset();
	while(nxt[l]==r)l++,r--;
	if(l==r)
	{
		for(int i=1;i<=m;i++)if(A[l]==B[i])f[now][i][i]=1;
		return ;
	}
	char c=A[r];int p=r;
	for(int i=l;i<=r;i++)
	{
		if(A[i]=='(')i=nxt[i];
		if(A[i]=='|')
		{
			c='|';p=i;break;
		}
		if(i<r&&c!='&'&&A[i]!='|'&&A[i+1]!='*'&&A[i+1]!='+'&&A[i+1]!='|')
		{
			c='&';p=i;
		}
	}
	if(c=='|')
	{
		int lc=len+1;dfs(l,p-1);
		int rc=len+1;dfs(p+1,r);
		for(int i=1;i<=m+1;i++)f[now][i]=f[lc][i]|f[rc][i];
	}
	else if(c=='&')
	{
		int lc=len+1;dfs(l,p);
		int rc=len+1;dfs(p+1,r);
		for(int i=1;i<=m+1;i++)
		{
			for(int j=i-1;j<=m;j++)if(f[lc][i][j])f[now][i]|=f[rc][j+1];
		}
	}
	else
	{
		int son=len+1;dfs(l,r-1);
		if(c=='*')for(int i=1;i<=m+1;i++)f[now][i][i-1]=1;
		else for(int i=1;i<=m+1;i++)f[now][i]=f[son][i];
		for(int i=1;i<=m+1;i++)
		{
			for(int j=i-1;j<=m;j++)
			{
				if(f[now][i][j])f[now][i]|=f[son][j+1];
			}
		}
	}
}
int sta[110],top;
int main()
{
	while(scanf("%s%s",A+1,B+1)!=EOF)
	{
		n=strlen(A+1);m=strlen(B+1);
		memset(nxt,-1,sizeof(nxt));
		for(int i=1;i<=n;i++)
		{
			if(A[i]=='(')sta[++top]=i;
			if(A[i]==')')nxt[sta[top--]]=i;
		}
		len=0;dfs(1,n);
		if(f[1][1][m])printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}