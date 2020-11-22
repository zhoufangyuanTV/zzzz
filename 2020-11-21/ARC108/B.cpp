#include<cstdio>
#include<cstring>
using namespace std;
char s[210000];
int f[210000];
int main()
{
	int n;scanf("%d",&n);
	scanf("%s",s+1);
	f[0]=0;int ss=0;
	for(int i=1,j=1;i<=n;i++,j++)
	{
		if(s[i]=='f')f[j]=1;
		else if(s[i]=='o'&&f[j-1]==1)f[j]=2;
		else if(s[i]=='x'&&f[j-1]==2)
		{
			ss++;
			j-=3;
		}
		else f[j]=0;
	}
	printf("%d\n",n-ss*3);
	return 0;
}