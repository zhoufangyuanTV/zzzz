#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
char s[1010000];
int rk[2][1010000];
vector<int> sa[2][1010000];
int f,ff,i;
inline bool cmp(int x,int y){return rk[f][x+i]<rk[f][y+i];}
int height[1010000];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	if(n==1)
	{
		puts("1");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		rk[0][i]=s[i];
		sa[0][s[i]].push_back(i);
	}
	int m=127;
	for(i=1,f=0,ff=1;i<n;i<<=1,f^=1,ff^=1)
	{
		int ms=0;
		for(int j=1;j<=m;j++)
		{
			sort(sa[f][j].begin(),sa[f][j].end(),cmp);
			for(int k=0;k<sa[f][j].size();k++)
			{
				if(k==0||rk[f][sa[f][j][k-1]+i]<rk[f][sa[f][j][k]+i])ms++;
				rk[ff][sa[f][j][k]]=ms;
				sa[ff][ms].push_back(sa[f][j][k]);
			}
			sa[f][j].clear();
		}
		m=ms;
	}
	for(int i=1;i<n;i++)printf("%d ",sa[f][i][0]);
	printf("%d\n",sa[f][n][0]);
	for(int i=1;i<=n;i++)
	{
		if(i>1)height[rk[f][i]]=height[rk[f][i-1]]-1;
		else height[rk[f][i]]=0;
		while(s[i+height[rk[f][i]]]==s[sa[f][rk[f][i]-1][0]+height[rk[f][i]]])height[rk[f][i]]++;
	}
	for(int i=2;i<=n;i++)printf("%d\n",height[i]);
	return 0;
}