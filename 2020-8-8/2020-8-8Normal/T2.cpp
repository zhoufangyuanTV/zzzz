#include<cstdio>
#include<cstring>
using namespace std;
int fa[110000],dep[110000];
int w[110000][10][26],next[10];
char s[110000];
int m[110000];
int main()
{
	int n,gg;scanf("%d%d",&n,&gg);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);m[i]=strlen(s+1);
		next[0]=0;
		w[i][0][s[1]-'a']=1;
		for(int j=1;j<m[i];j++)
		{
			if(j>1)next[j]=w[i][next[j-1]][s[j]-'a'];else next[j]=0;
			for(int c=0;c<26;c++)w[i][j][c]='a'+c==s[j+1]?j+1:w[i][next[j]][c];
		}
	}
	fa[1]=0;dep[1]=1;
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa[i]);
		dep[i]=dep[fa[i]]+1;
	}
	int q;scanf("%d",&q);int last=0;
	while(q--)
	{
		int x,y;scanf("%d%d%s",&x,&y,s+1);
		if(gg==1)x^=last,y^=last;last=0;
		int mm=strlen(s+1);
		if(dep[x]<dep[y])x^=y^=x^=y;
		while(dep[x]>dep[y])
		{
			int j=0;
			for(int i=1;i<=mm;i++)
			{
				j=w[x][j][s[i]-'a'];
				if(j==m[x])
				{
					if(j>last)last=j;
					break;
				}
			}
			x=fa[x];
		}
		while(x!=y)
		{
			int j=0;
			for(int i=1;i<=mm;i++)
			{
				j=w[x][j][s[i]-'a'];
				if(j==m[x])
				{
					if(j>last)last=j;
					break;
				}
			}
			j=0;
			for(int i=1;i<=mm;i++)
			{
				j=w[y][j][s[i]-'a'];
				if(j==m[y])
				{
					if(j>last)last=j;
					break;
				}
			}
			x=fa[x];
			y=fa[y];
		}
		int j=0;
		for(int i=1;i<=mm;i++)
		{
			j=w[x][j][s[i]-'a'];
			if(j==m[x])
			{
				if(j>last)last=j;
				break;
			}
		}
		printf("%d\n",last);
	}
	return 0;
}