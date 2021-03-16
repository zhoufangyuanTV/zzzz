#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int> a;
int Ans[3010000];
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int n,t;scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)
	{
		char c=getchar();
		while(c!='0'&&c!='1')c=getchar();
		if(c=='1')a.push_back(i);
	}
	bool bk=true;
	for(int i=0;i<=a.size()-2;i++)if(a[i]+1==a[i+1]){bk=false;break;}
	memset(Ans,0,sizeof(Ans));
	if(bk)
	{
		int las=0;
		for(int i=0;i<a.size();i++)
		{
			if(a[i]-t<=las)las++;
			else las=a[i]-t;
			Ans[las]=1;
		}
	}
	else
	{
		while(t--)
		{
			for(int i=a.size()-1;i>=0;i--)
			{
				if(i==0){if(a[i]>1)a[i]--;}
				else if(a[i]>a[i-1]+1)a[i]--;
			}
		}
		for(int i=0;i<a.size();i++)Ans[a[i]]=1;
	}
	for(int i=1;i<n;i++){putchar(Ans[i]+'0');putchar(' ');}
	putchar(Ans[n]+'0');putchar('\n');
	return 0;
}