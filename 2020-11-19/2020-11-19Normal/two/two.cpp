#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
priority_queue<int,vector<int>,greater<int> > QQ[110000];
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		int m,k;scanf("%d%d",&m,&k);
		QQ[m].push(k);
	}
	for(int i=1;i<=q;i++)
	{
		int opt,x,t;scanf("%d%d%d",&opt,&x,&t);
		if(opt==1)
		{
			QQ[x].push(t);
			n++;
		}
		else
		{
			for(int i=x;i<=100000;i++)
			{
				if(t<=(i-x)*(i-x))break;
				int tt=t-(i-x)*(i-x);
				while(!QQ[i].empty()&&QQ[i].top()<=tt)QQ[i].pop(),n--;
			}
			for(int i=x-1;i>=1;i--)
			{
				if(t<=(x-i)*(x-i))break;
				int tt=t-(x-i)*(x-i);
				while(!QQ[i].empty()&&QQ[i].top()<=tt)QQ[i].pop(),n--;
			}
		}
		printf("%d\n",n);
	}
	return 0;
}