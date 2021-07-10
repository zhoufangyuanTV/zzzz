#include<cstdio>
#include<cstring>
#include<list>
using namespace std;
list<int> L1,L2;
list<int>::iterator p[11000];
int Ans[11000],T[11000];
int main()
{
	freopen("help.in","r",stdin);
	freopen("help.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		L2.clear();
		memset(T,0,sizeof(T));
		for(int i=1;i<=n;i++)
		{
			int x;scanf("%d",&x);
			L2.insert(L2.begin(),x);
		}
		int tt=0;
		while(!L2.empty())
		{
			for(int i=1;i<=n;i++)
			{
				if(T[i]==tt)p[i]=L1.insert(L1.end(),i);
			}
			tt++;
			for(list<int>::iterator it=L2.begin();it!=L2.end();)
			{
				if(T[*it]<tt)
				{
					Ans[*it]=tt;
					if(p[*it]!=L1.begin())
					{
						list<int>::iterator pt=p[*it];
						pt--;
						T[*pt]=tt;
					}
					list<int>::iterator pt=p[*it];
					pt++;
					if(pt!=L1.end())T[*pt]=tt;
					L1.erase(p[*it]);
					it=L2.erase(it);
				}
				else
				{
					L1.erase(p[*it]);
					it++;
				}
			}
		}
		for(int i=1;i<n;i++)printf("%d ",Ans[i]);
		printf("%d\n",Ans[n]);
	}
	return 0;
}