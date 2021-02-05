#include<cstdio>
#include<cstring>
using namespace std;
char a[110],b[110],c[110];
int n,m,nm,d[210],cc[110];
long long ss=0;
bool v[210][21];
void dfs(int k)
{
	if(k==n+m+1)
	{
		long long A=0,B=0;
		for(int i=1;i<=n;i++)A=A*10+d[a[i]];
		for(int i=1;i<=m;i++)B=B*10+d[b[i]];
		long long C=A+B;
		for(int i=nm;i>=1;i--)cc[i]=C%10,C=C/10;
		if(C>0)return ;
		if(cc[1]==0)return ;
		for(int i=1;i<=nm;i++)
		{
			if(d[c[i]]!=-1&&d[c[i]]!=cc[i])return ;
			if(v[c[i]][cc[i]]==false)return ;
		}
		ss++;
	}
	else
	{
		if(k<=n)
		{
			if(d[a[k]]!=-1)dfs(k+1);
			else
			{
				for(int i=0;i<10;i++)
				{
					if(k==1&&i==0)continue;
					if(v[a[k]][i]==false)continue;
					d[a[k]]=i;
					dfs(k+1);
					d[a[k]]=-1;
				}
			}
		}
		else
		{
			if(d[b[k-n]]!=-1)
			{
				if(k==n+1&&d[b[k-n]]==0)return ;
				dfs(k+1);
			}
			else
			{
				for(int i=0;i<10;i++)
				{
					if(k==n+1&&i==0)continue;
					if(v[b[k-n]][i]==false)continue;
					d[b[k-n]]=i;
					dfs(k+1);
					d[b[k-n]]=-1;
				}
			}
		}
	}
}
char sg[210];
int main()
{
	scanf("%[^+]%*c%[^=]%*c%[^\n\r]",a+1,b+1,c+1);
	n=strlen(a+1),m=strlen(b+1),nm=strlen(c+1);
	memset(d,-1,sizeof(d));
	int t;scanf("%d",&t);
	memset(v,true,sizeof(v));
	while(t--)
	{
		int x;scanf("%s %d",sg+1,&x);
		v[sg[1]][x]=false;
	}
	dfs(1);
	printf("%lld\n",ss);
	return 0;
}