#include<cstdio>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;
deque<int> a;
int Ans[110000];
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=0;i<=n;i++)
	{
		int x;scanf("%d",&x);
		a.push_back(x);
	}
	bool bk;
	do
	{
		bk=false;
		int s=0,ss=0,i=0;
		for(deque<int>::iterator it=a.begin();it!=a.end();it++,i++)
		{
			if(i&1)
			{
				if(*it<ss)
				{
					ss-=*it;
					bk=true;
				}
				else
				{
					s=*it-ss;
					*it=ss;
					ss=0;
				}
			}
			else
			{
				ss+=*it;
				*it+=s;
				s=0;
			}
		}
		a.push_back(ss);
		a.pop_front();
	}while(bk);
	int ss=a.size()/2+1;
	for(int i=0;i<a.size();i+=2)Ans[i/2+1]=a[i];
	sort(Ans+1,Ans+ss+1);
	for(int i=1;i<ss;i++)printf("%d ",Ans[i]);
	printf("%d\n",Ans[ss]);
	return 0;
}