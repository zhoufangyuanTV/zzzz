#include<cstdio>
#include<cstring>
using namespace std;
long long ha[20010000];
inline bool add(long long h)
{
	int x=h%19491001;
	while(ha[x]!=-1)
	{
		if(ha[x]==h)return false;
		x=(x+1)%19491001;
	}
	ha[x]=h;
	return true;
}
char s[3100],t[3100];
int main()
{
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	int n;scanf("%d%s%s",&n,s+1,t+1);
	int ss=0;
	memset(ha,-1,sizeof(ha));
	for(int i=1;i<=n;i++)
	{
		long long h=0;
		int k=0;
		for(int j=i;j<=n;j++)
		{
			h=(h*29+t[j]-'a'+1)%1000000009;
			k++;
			while(k<=n&&s[k]!=t[j])k++;
			if(k==n+1)break;
			ss+=add(h);
		}
	}
	printf("%d\n",ss);
	return 0;
}