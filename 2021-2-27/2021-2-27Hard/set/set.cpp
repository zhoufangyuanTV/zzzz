#include<cstdio>
#include<cstring>
#include<unordered_set>
using namespace std;
unordered_set<int> S;
int s,a[1100],n;
void dfs(int k)
{
	if(k-1>s)
	{
		s=k-1;
		if(s>=1000)
		{
			printf("%d\n",s);
			for(int i=1;i<s;i++)printf("%d ",a[i]);
			printf("%d\n",a[s]);
		}
	}
	for(int i=a[k-1]+1;i<=n;i++)
	{
		bool bk=true;
		for(int j=1;j<k;j++)
		{
			if(S.find(a[j]^i)!=S.end()){bk=false;break;}
		}
		if(bk)
		{
			a[k]=i;
			for(int j=1;j<k;j++)S.insert(a[j]^i);
			dfs(k+1);
			for(int j=1;j<k;j++)S.erase(a[j]^i);
		}
	}
}
int main()
{
	scanf("%d",&n);
	s=a[0]=0;dfs(1);
	return 0;
}