#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
set<int> S[110000];
int list[110000];
bool b[110000];
int main()
{
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
	int t;read(t);
	while(t--)
	{
		int n,m;read(n);read(m);
		for(int i=1;i<=n;i++)S[i].clear();
		for(int i=1;i<=m;i++)
		{
			int x,y;read(x);read(y);
			S[x].insert(y);S[y].insert(x);
		}
		int head=1,tail=1;
		memset(b,true,sizeof(b));
		bool bk=true;
		int st=0,ts=0;
		for(int i=1;i<=n;i++)
		{
			if(S[i].size()%2==1)
			{
				if(st==0)st=i;
				else if(ts==0)ts=i;
				else{bk=false;break;}
			}
			else if(S[i].size()==2)list[tail++]=i,b[i]=false;
		}
		if(bk==false){puts("NO");continue;}
		while(head<tail)
		{
			if(S[list[head]].size()==0){head++;continue;}
			set<int>::iterator it=S[list[head]].begin();
			int x=*it;it++;int y=*it;
			S[list[head]].clear();
			S[x].erase(list[head]);
			S[y].erase(list[head]);
			it=S[x].find(y);
			if(it==S[x].end())
			{
				S[x].insert(y);
				S[y].insert(x);
			}
			else
			{
				S[x].erase(it);
				S[y].erase(x);
				if(st==0)st=x,ts=y;
				else
				{
					if(x==st&&y!=ts||y==st&&x!=ts)ts=0;
					else if(x==ts&&y!=st||y==ts&&x!=st){st=ts;ts=0;}
					else if(x!=st&&y!=ts&&x!=ts&&y!=st){bk=false;break;}
				}
				if(S[x].size()==2&&b[x]==true){b[x]=false;list[tail++]=x;}
				if(S[y].size()==2&&b[y]==true){b[y]=false;list[tail++]=y;}
			}
			head++;
		}
		if(bk==false)puts("NO");
		else
		{
			for(int i=1;i<=n;i++)if(S[i].size()>1){bk=false;break;}
			if(bk==false)puts("NO");
			else puts("YES");
		}
	}
	return 0;
}