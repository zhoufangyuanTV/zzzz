#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct Query{int x,y,p;}Q[1010000];
int Ans[1010000];
inline bool cmp(Query x,Query y){return x.x==y.x?x.y<y.y:x.x<y.x;}
vector<int> a[610000],son[610000][26],fail[610000];
int len[610000];
char s[610000];
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		len[i]=strlen(s+1);
		a[i].resize(len[i]+1);
		for(int j=0;j<26;j++)son[i][j].resize(len[i]+1);
		fail[i].resize(len[i]+1);
		for(int j=1;j<=len[i];j++)
		{
			int c=s[j]-'a';
			a[i][j]=c;
			son[i][c][j-1]=j;
		}
		fail[i][0]=0;
		for(int j=1;j<=len[i];j++)
		{
			if(j>1)fail[i][j]=son[i][a[i][j]][fail[i][j-1]];
			else fail[i][1]=0;
			for(int k=0;k<26;k++)
			{
				if(son[i][k][j]==0)son[i][k][j]=son[i][k][fail[i][j]];
			}
		}
	}
	for(int i=1;i<=m;i++)scanf("%d%d",&Q[i].x,&Q[i].y),Q[i].p=i;
	sort(Q+1,Q+m+1,cmp);
	int lastans=0;
	for(int i=1;i<=m;i++)
	{
		if(Q[i].x==Q[i-1].x&&Q[i].y==Q[i-1].y)Ans[Q[i].p]=lastans;
		else
		{
			int x=Q[i].x,y=Q[i].y;
			int j=0;
			if(len[x]<len[y])
			{
				for(int k=1;k<=len[x];k++)j=son[y][a[x][k]][j];
			}
			else
			{
				for(int k=len[x]-len[y]+1;k<=len[x];k++)j=son[y][a[x][k]][j];
			}
			lastans=Ans[Q[i].p]=j;
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}