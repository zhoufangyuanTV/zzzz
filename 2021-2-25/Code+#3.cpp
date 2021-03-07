#include<cstdio>
#include<cstring>
using namespace std;
long long f[17][17][131072],g[131072],G[131072];
int a[17][17],Ans[17][17];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&a[i][j]);
	f[0][0][(1<<m)-2+a[0][0]]=1;
	for(int i=0;i<n;i++)
	{
		if(i>0)
		{
			for(int j=0;j<1<<m;j+=2)f[i][0][j+a[i][0]]=(f[i-1][m-1][j]+f[i-1][m-1][j+1])%1000000007;
			if(a[i][0]==0)
			{
				for(int j=0;j<1<<m;j+=2)f[i][0][j+1]=(f[i][0][j+1]+f[i-1][m-1][j])%1000000007;
			}
		}
		for(int j=1;j<m;j++)
		{
			for(int k=0;k<1<<j;k++)
			{
				for(int l=0;l<1<<m;l+=1<<j+1)f[i][j][k+(a[i][j]<<j)+l]=(f[i][j-1][k+l]+f[i][j-1][k+(1<<j)+l])%1000000007;
			}
			if(a[i][j]==0)
			{
				for(int k=0;k<1<<j-1;k++)
				{
					for(int l=0;l<1<<m;l+=1<<j+1)f[i][j][k+(1<<j-1)+(1<<j)+l]=(f[i][j][k+(1<<j-1)+(1<<j)+l]+f[i][j-1][k+l]+f[i][j-1][k+(1<<j)+l])%1000000007;
				}
				for(int k=0;k<1<<j;k++)
				{
					for(int l=0;l<1<<m;l+=1<<j+1)f[i][j][k+(1<<j)+l]=(f[i][j][k+(1<<j)+l]+f[i][j-1][k+l])%1000000007;
				}
			}
		}
	}
	for(int i=0;i<1<<m;i++)g[i]=1;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=m-1;j>=0;j--)
		{
			if(a[i][j]==0)
			{
				memset(f[i][j],0,1048576);
				if(i==0&&j==0)f[0][0][(1<<m)-1]=1;
				else if(i>0&&j==0)
				{
					for(int k=0;k<1<<m;k+=2)f[i][0][k+1]=(f[i-1][m-1][k]+f[i-1][m-1][k+1])%1000000007;
				}
				else
				{
					for(int k=0;k<1<<j;k++)
					{
						for(int l=0;l<1<<m;l+=1<<j+1)f[i][j][k+(1<<j)+l]=(f[i][j-1][k+l]+f[i][j-1][k+(1<<j)+l])%1000000007;
					}
				}
				for(int k=0;k<1<<m;k++)Ans[i][j]=(Ans[i][j]+f[i][j][k]*g[k])%1000000007;
			}
			memset(G,0,sizeof(G));
			if(j==0)
			{
				for(int k=0;k<1<<m;k+=2)G[k]=G[k+1]=g[k+a[i][j]];
				if(a[i][j]==0)
				{
					for(int k=0;k<1<<m;k+=2)G[k]=(G[k]+g[k+1])%1000000007;
				}
			}
			else
			{
				for(int k=0;k<1<<j;k++)
				{
					for(int l=0;l<1<<m;l+=1<<j+1)G[k+l]=G[k+(1<<j)+l]=g[k+(a[i][j]<<j)+l];
				}
				if(a[i][j]==0)
				{
					for(int k=0;k<1<<j-1;k++)
					{
						for(int l=0;l<1<<m;l+=1<<j+1)
						{
							G[k+l]=(G[k+l]+g[k+(1<<j-1)+(1<<j)+l])%1000000007;
							G[k+(1<<j)+l]=(G[k+(1<<j)+l]+g[k+(1<<j-1)+(1<<j)+l])%1000000007;
						}
					}
					for(int k=0;k<1<<j;k++)
					{
						for(int l=0;l<1<<m;l+=1<<j+1)G[k+l]=(G[k+l]+g[k+(1<<j)+l])%1000000007;
					}
				}
			}
			for(int k=0;k<1<<m;k++)g[k]=G[k];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=m-2;j++)printf("%d ",Ans[i][j]);
		printf("%d\n",Ans[i][m-1]);
	}
	return 0;
}