#include<cstdio>
#include<cstring>
using namespace std;
const int dx[8][3]={{0,-1,-1},{-1,-1,0},{0,1,1},{1,1,0},{0,0,0},{-1,-1,-1},{0,0,0},{1,1,1}};
const int dy[8][3]={{1,1,0},{0,-1,-1},{-1,-1,0},{0,1,1},{1,1,1},{0,0,0},{-1,-1,-1},{0,0,0}};
int f[32][32][32][32];
char mmp[31][32];
int n,m;
int main()
{
	freopen("makina.in","r",stdin);
	freopen("makina.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",mmp[i]+1);
	int if1[8]={1,1,n,n,1,1,n,n};
	int if2[8]={m,1,1,m,m,1,1,m};
	int if3[8]={n+1,n+1,0,0,n+1,n+1,0,0};
	int if4[8]={1,1,-1,-1,1,1,-1,-1};
	int if5[8]={0,m+1,m+1,0,0,m+1,m+1,0};
	int if6[8]={-1,1,1,-1,-1,1,1,-1};
	int ss=0,s=0,sss=0;
	for(int d1=0;d1<8;d1++)
	{
		for(int d2=0;d2<8;d2++)
		{
			memset(f,0,sizeof(f));
			for(int i1=if1[d1];i1!=if3[d1];i1+=if4[d1])
			{
				for(int j1=if2[d1];j1!=if5[d1];j1+=if6[d1])
				{
					for(int i2=if1[d2];i2!=if3[d2];i2+=if4[d2])
					{
						for(int j2=if2[d2];j2!=if5[d2];j2+=if6[d2])
						{
							if(mmp[i1][j1]==mmp[i2][j2])
							{
								f[i1][j1][i2][j2]=mmp[i1][j1]==mmp[i2][j2];
								for(int dd1=0;dd1<(d1<4?3:1);dd1++)
								{
									for(int dd2=0;dd2<(d2<4?3:1);dd2++)
									{
										int di1=i1+dx[d1][dd1],dj1=j1+dy[d1][dd1];
										int di2=i2+dx[d2][dd2],dj2=j2+dy[d2][dd2];
										f[i1][j1][i2][j2]=(f[i1][j1][i2][j2]+f[di1][dj1][di2][dj2])%1000000009;
									}
								}
								if(d1<4&&d2<4)ss=(ss+(f[i1][j1][i2][j2]+1000000008)%1000000009)%1000000009;
								else if(d1>3&&d2>3)sss=(sss+(f[i1][j1][i2][j2]+1000000008)%1000000009)%1000000009;
								else s=(s+(f[i1][j1][i2][j2]+1000000008)%1000000009)%1000000009;
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n",((ss+sss)%1000000009-s+1000000009)%1000000009);
	return 0;
}