#include<cstdio>
#include<cstring>
using namespace std;
int bitcnt[65536];
char a[26],opt[11],s[26],t[26];
int f[65536],ff[65536],g[8192][25];
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("quarantine.in","r",stdin);
	freopen("quarantine.out","w",stdout);
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	bitcnt[0]=0;
	for(int i=1;i<1<<m;i++)bitcnt[i]=bitcnt[i>>1]+(i&1);
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%s",a+1);
			g[i][j]=0;
			for(int k=1;k<=m;k++)g[i][j]|=a[k]-'0'<<k-1;
		}
	}
	while(q--)
	{
		scanf("%s",opt+1);
		if(opt[1]=='T')
		{
			int i,x,y;scanf("%d%d%d",&i,&x,&y);
			g[i][x]^=1<<y-1;
		}
		else
		{
			int l,r;scanf("%d%d%s%s",&l,&r,s+1,t+1);
			int S=0,T=0;
			for(int i=1;i<=m;i++)S|=s[i]-'0'<<i-1,T|=t[i]-'0'<<i-1;
			memset(f,63,4<<m);f[S]=0;
			for(int i=l;i<r;i++)
			{
				for(int j=(1<<m)-1;j>=0;j--)
				{
					ff[j]=f[j];
					for(int k=1;k<=m;k++)ff[j]=mymin(ff[j],ff[j|1<<k-1]+1);
				}
				memset(f,63,4<<m);
				for(int j=0;j<1<<m;j++)
				{
					int k=0;
					for(int l=1;l<=m;l++)if(j==(j|1<<l-1))k|=g[i][l];
					f[k]=mymin(f[k],ff[j]);
				}
			}
			int ss=0x3f3f3f3f;
			for(int i=0;i<1<<m;i++)ss=mymin(ss,f[i]+bitcnt[i&T]);
			printf("%d\n",ss);
		}
	}
	return 0;
}