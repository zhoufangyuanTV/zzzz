#include<cstdio>
#include<cstring>
using namespace std;
char s[110000];
int main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d%s",&n,s+1);
		s[n+1]='\0';
		int j=1,ss=0;
		for(int i=1;i<=n;i++)
		{
			while(j<=n&&(j<i||s[j]!=s[j+1]))j++;
			if(j>n)
			{
				while(s[n-1]==s[n])n--;
				s[n--]='\0';
			}
			else j++;
			ss++;
			while(i<=n&&s[i]==s[i+1])i++;
		}
		printf("%d\n",ss);
	}
	return 0;
}
