#include<cstdio>
#include<cstring>
using namespace std;
int sta[110][1100],top[110];
struct node{int x,y;}Ans[1010000];int ss;
inline void moe(int x,int y,int g)
{
	while(top[x]>g)
	{
		sta[y][++top[y]]=sta[x][top[x]];
		top[x]--;
		Ans[++ss]=(node){x,y};
	}
}
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		top[i]=m;
		for(int j=1;j<=m;j++)scanf("%d",&sta[i][j]);
	}
	top[n+1]=0;ss=0;
	for(int i=1;i<=n;i++)
	{
		int k=i+1,t=top[i+1];
		for(int j=m;j>=1;j--)
		{
			if(sta[i][j]==i)continue;
			while(sta[k][t]!=i)
			{
				t--;
				if(t==0)
				{
					moe(n+1,k,0);t=top[++k];
				}
				/*else
				{
					sta[n+1][++top[n+1]]=sta[k][top[k]];
					top[k]--;Ans[++ss]=(node){k,n+1};
				}*/
			}
			moe(k,n+1,t);
			if(top[i]-j+1<=m-top[n+1])
			{
				moe(i,n+1,j-1);
				//moe(k,i,t-1);
				sta[i][++top[i]]=sta[k][top[k]];
				Ans[++ss]=(node){k,i};
				//moe(n+1,k,top[n+1]-1);
				sta[k][top[k]]=sta[n+1][top[n+1]--];
				Ans[++ss]=(node){n+1,k};
				moe(n+1,i,top[n+1]-m+top[i]);
			}
			else
			{
				//moe(k,n+1,t-1);
				sta[n+1][++top[n+1]]=sta[k][top[k]];
				top[k]--;Ans[++ss]=(node){k,n+1};
				if(top[i]-j+1<=m-top[k])
				{
					moe(i,k,j-1);
					//moe(n+1,i,top[n+1]-1);
					sta[i][++top[i]]=sta[n+1][top[n+1]];
					Ans[++ss]=(node){n+1,i};
					//moe(k,n+1,top[k]-1);
					sta[n+1][top[n+1]]=sta[k][top[k]--];
					Ans[++ss]=(node){k,n+1};
					moe(k,i,top[k]-m+top[i]);
					t--;
					if(t==0)
					{
						moe(n+1,k,0);t=top[++k];
					}
				}
				else
				{
					moe(i,k,top[i]-((m-1)-top[k]));
					//moe(n+1,k,top[n+1]-1);
					sta[k][++top[k]]=sta[n+1][top[n+1]];
					top[n+1]--;Ans[++ss]=(node){n+1,k};
					moe(i,n+1,j-1);
					//moe(k,i,top[k]-1);
					moe(k,i,t-1);
					//moe(n+1,k,top[n+1]-1);
					sta[k][++top[k]]=sta[n+1][top[n+1]];
					top[n+1]--;Ans[++ss]=(node){n+1,k};
					moe(n+1,i,top[n+1]-m+top[i]);
				}
			}
		}
		moe(n+1,k,0);
	}
	printf("%d\n",ss);
	for(int i=1;i<=ss;i++)printf("%d %d\n",Ans[i].x,Ans[i].y);
	return 0;
}
