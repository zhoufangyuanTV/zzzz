#include<cstdio>
#include<cstring>
using namespace std;
int f[5100][5100];
char a[5100];
inline int mymin(int x,int y){return x<y?x:y;}
char sta[5100];int top;
int main()
{
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	scanf("%s",a+1);
	int n=strlen(a+1);
	bool bk=true;
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='C'){bk=false;break;}
	}
	if(bk)
	{
		top=0;
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			if(top==0||sta[top]!=a[i])
			{
				if(top==2)top--;
				else
				{
					sta[++top]=a[i];
					ss++;
				}
			}
		}
		printf("%d\n",n+ss*2);
		return 0;
	}
	memset(f,63,sizeof(f));
	for(int i=1;i<=n;i++)f[i][i]=1;
	for(int j=2;j<=n;j++)
	{
		for(int i=j-1;i>=1;i--)
		{
			if(a[j-1]==a[j])f[i][j]=f[i][j-1];
			else
			{
				f[i][j]=f[i][j-1]+1;
				for(int k=i;k<j;k++)
				{
					if(a[k]==a[j])f[i][j]=mymin(f[i][j],f[i][k]+f[k+1][j-1]);
				}
			}
		}
	}
	printf("%d\n",n+f[1][n]*2);
	return 0;
}