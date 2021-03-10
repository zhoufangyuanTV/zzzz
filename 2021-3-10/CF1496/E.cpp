#include<cstdio>
#include<cstring>
using namespace std;
char s[1100][1100],ss[1100][1100];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
		for(int i=1;i<=n;i++)ss[i][m+1]='\0';
		for(int i=1;i<=m;i++)ss[1][i]='X';
		for(int i=2;i<=n;i++)
		{
			if(i%2==0)
			{
				bool bk=false;
				for(int j=1;j<=m;j++)
				{
					ss[i][j]=s[i][j];
					if(ss[i][j]=='X')bk=true;
				}
				if(bk==false)ss[i][1]='X';
			}
			else
			{
				int g=0;
				for(int j=1;j<=m;j++)
				{
					if(ss[i-1][j]=='X')
					{
						if(g==0)g=1,ss[i][j]='X';
						else
						{
							if(s[i][j]=='X'||i<=n&&s[i+1][j]=='X')
							{
								ss[i][j]='X';ss[i][j-1]='.';
							}
							else
							{
								g=0;ss[i][j]='.';
							}
						}
					}
					else ss[i][j]='X';
				}
				if(g==0)
				{
					for(int j=m;j>=1;j--)
					{
						if(ss[i-1][j]=='X')
						{
							ss[i][j]='X';
							ss[i][j-1]='.';
							break;
						}
					}
				}
			}
		}
		for(int i=1;i<=n;i++)puts(ss[i]+1);
	}
	return 0;
}