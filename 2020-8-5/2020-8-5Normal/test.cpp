#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
int main()
{
	set<int> S;int ss=0;
	for(int i=1;i<=5000;i++)S.insert(i);
	for(int i=5000;i<=10000;i++)
	{
		set<int> &SS=S;
		if(SS.size()>=5000)ss++;
	}
	printf("%d\n",ss);
	return 0;
}