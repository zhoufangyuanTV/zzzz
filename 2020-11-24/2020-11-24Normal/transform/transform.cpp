#include<cstdio>
#include<cstring>
using namespace std;
char s[510000],sr[510000];
bool b[510000];
int main()
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	scanf("%s",s);
	for(int i=1;i<=m;i++)
	{
		int x,l,k;scanf("%d%d%d",&x,&l,&k);
		for(int j=0;j<l;j++)s[(x+j)%n]=k+'0';
		for(int j=0;j<n;j++)sr[j]=s[j];
		int t=0;
		bool bk=false;
		for(int i=0;i<n;i++)
		{
			int l=i-1,r=i+1;
			if(i==0)l=n-1;
			if(i==n-1)r=0;
			if(s[l]==s[r]&&s[i]!=s[l])b[i]=bk=true;
			else b[i]=false;
		}
		while(bk&&t<=30000000/n/m)
		{
			t++;
			for(int i=0;i<n;i++)
			{
				if(b[i])s[i]=s[i]=='1'?'0':'1';
			}
			bk=false;
			for(int i=0;i<n;i++)
			{
				int l=i-1,r=i+1;
				if(i==0)l=n-1;
				if(i==n-1)r=0;
				if(s[l]==s[r]&&s[i]!=s[l])b[i]=bk=true;
				else b[i]=false;
			}
		}
		if(t>30000000/n/m)puts("-1");
		else printf("%d\n",t);
		for(int j=0;j<n;j++)s[j]=sr[j];
	}
	return 0;
}