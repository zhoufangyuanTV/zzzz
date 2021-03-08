#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
int f[110][110],a[51000],b[110],h[110];
priority_queue<int> Q;
bool g[110][110];
int Ans[51000],ss;
struct node{int x;};
inline bool operator<(node x,node y){return a[x.x]<a[y.x];}
priority_queue<node> N;
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n,m,X,A;scanf("%d%d%d%d",&n,&m,&X,&A);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d%d",&b[i],&h[i]);
	b[0]=0;
	memset(f,-1,sizeof(f));f[0][0]=A;
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(f[i-1][j]!=-1)
			{
				f[i][j]=f[i-1][j];
				for(int k=b[i-1]+1;k<=b[i];k++)f[i][j]+=a[k];
				g[i][j]=false;
			}
			if(j>0&&f[i-1][j-1]!=-1&&h[i]<=b[i]-b[i-1])
			{
				int B=f[i-1][j-1],C=b[i]-b[i-1]-h[i];
				while(!Q.empty())Q.pop();
				for(int k=b[i-1]+1;k<=b[i];k++)
				{
					Q.push(a[k]);
					B-=X;
					if(B<0)
					{
						if(Q.empty())break;
						B+=X+Q.top();
						Q.pop();
						C--;
					}
				}
				if(B>=0&&C>=0)
				{
					while(C>0&&!Q.empty()){B+=X+Q.top();Q.pop();C--;}
					if(f[i][j]<B)
					{
						f[i][j]=B;
						g[i][j]=true;
					}
				}
			}
		}
	}
	int j;
	for(j=m;j>=1;j--)if(f[m][j]!=-1)break;
	printf("%d\n",j);
	ss=0;
	for(int i=m;i>=1;i--)
	{
		if(g[i][j])
		{
			int B=f[i-1][j-1],C=b[i]-b[i-1]-h[i];
			while(!N.empty())N.pop();
			for(int k=b[i-1]+1;k<=b[i];k++)
			{
				N.push((node){k});
				B-=X;
				if(B<0)
				{
					if(N.empty())break;
					B+=X+a[N.top().x];
					Ans[++ss]=N.top().x;
					N.pop();
					C--;
				}
			}
			while(C>0&&!N.empty())
			{
				Ans[++ss]=N.top().x;
				N.pop();
				C--;
			}
			j--;
		}
		else for(int k=b[i-1]+1;k<=b[i];k++)Ans[++ss]=k;
	}
	printf("%d\n",ss);
	sort(Ans+1,Ans+ss+1);
	for(int i=1;i<ss;i++)printf("%d ",Ans[i]);
	printf("%d\n",Ans[ss]);
	return 0;
}