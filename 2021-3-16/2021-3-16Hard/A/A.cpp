#include<cstdio>
#include<cstring>
#include<deque>
#include<vector>
using namespace std;
vector<int> a;
struct node{int l,r;};
deque<node> b;
int Ans[3010000];
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int n,t;scanf("%d%d",&n,&t);
	a.push_back(0);
	for(int i=1;i<=n;i++)
	{
		char c=getchar();
		while(c!='0'&&c!='1')c=getchar();
		if(c=='0')a.push_back(0);
		else (*a.rbegin())++;
	}
	memset(Ans,0,sizeof(Ans));
	for(int i=a.size()-1;i>=0;i--)
	{
		node x;x.l=i-t;x.r=i-t+a[i]-1;
		while(!b.empty()&&b.front().l<=x.r)
		{
			x.r+=b.front().r-b.front().l+1;
			b.pop_front();
		}
		if(x.l<=x.r)b.push_front(x);
		if(!b.empty()&&b.back().r>=i)
		{
			Ans[i]=b.back().r-i+1;
			b.back().r=i-1;
			if(b.back().l>b.back().r)b.pop_back();
		}
	}
	while(!b.empty()){Ans[0]+=b.back().r-b.back().l+1;b.pop_back();}
	for(int i=0;i<a.size();i++)
	{
		if(i>0)printf("0 ");
		while(Ans[i]--)printf("1 ");
	}
	return 0;
}