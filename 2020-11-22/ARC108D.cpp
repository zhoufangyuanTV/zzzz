#include<cstdio>
#include<cstring>
using namespace std;
int f[1100];
int main()
{
	int n;char a,b,c,d;scanf("%d\n%c\n%c\n%c\n%c",&n,&a,&b,&c,&d);
	if(b=='A')
	{
		if(a=='A')printf("1\n");
		else
		{
			if(c=='B')
			{
				int ss=1;
				for(int i=1;i<=n-3;i++)ss=ss*2%1000000007;
				printf("%d\n",ss);
			}
			else
			{
				f[1]=0;f[2]=1;
				for(int i=3;i<=n;i++)f[i]=(f[i-2]+f[i-1])%1000000007;
				printf("%d\n",f[n]);
			}
		}
	}
	else
	{
		if(d=='B')printf("1\n");
		else
		{
			if(c=='A')
			{
				int ss=1;
				for(int i=1;i<=n-3;i++)ss=ss*2%1000000007;
				printf("%d\n",ss);
			}
			else
			{
				f[1]=0;f[2]=1;
				for(int i=3;i<=n;i++)f[i]=(f[i-2]+f[i-1])%1000000007;
				printf("%d\n",f[n]);
			}
		}
	}
	return 0;
}