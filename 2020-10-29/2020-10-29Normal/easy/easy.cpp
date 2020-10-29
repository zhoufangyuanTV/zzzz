#include<cstdio>
#include<cstring>
#include<set>
#include<utility>
using namespace std;
set<int> S;
int a[110000];
int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int ss=0;
	for(int i=1;i<=n;i++)
	{
		S.clear();int s=0;
		for(int j=1;j<=n;j++)
		{
			pair<set<int>::iterator,bool> R=S.insert(a[j]);
			if(R.second)
			{
				s++;
				set<int>::iterator it=R.first;
				if(it!=S.begin())
				{
					it--;
					if(*it==a[j]-1)s--;
					it++;
				}
				it++;
				if(it!=S.end()&&*it==a[j]+1)s--;
			}
			if(s==1)ss++;
		}
	}
	printf("%d\n",ss);
	return 0;
}