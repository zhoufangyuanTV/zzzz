#include<cstdio>
#include<cstring>
using namespace std;
char s[110000];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s);
		int n=strlen(s);
		bool bk=false;
		for(int i=0;i<n;i++)
		{
			if(s[i]!=s[i&1])
			{
				bk=true;
				break;
			}
		}
		if(n>=2&&s[0]==s[1])bk=true;
		if(bk==false)
		{
			printf("-1\n");
			continue;
		}
		for(int i=0;i<n;i++)
		{
			if(i+1<n&&s[i]==s[i+1])
			{
				printf("%c%c\n",s[i],s[i+1]);
				break;
			}
			if(i+2<n&&s[i]!=s[i+1]&&s[i+1]!=s[i+2]&&s[i]!=s[i+2])
			{
				printf("%c%c%c\n",s[i],s[i+1],s[i+2]);
				break;
			}
		}
	}
	return 0;
}