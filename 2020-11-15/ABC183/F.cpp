#include<cstdio>
#include<cstring>
#include<map>
#include<utility>
using namespace std;
map<int,int> M[210000];
int f[210000];
inline int find(int x){return f[x]!=x?f[x]=find(f[x]):x;}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int c;scanf("%d",&c);
		M[i][c]++;f[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			int fx=find(x),fy=find(y);
			if(fx!=fy)
			{
				if(M[fx].size()>M[fy].size())
				{
					fx^=fy^=fx^=fy;
				}
				f[fx]=fy;
				for(pair<int,int> i:M[fx])
				{
					M[fy][i.first]+=i.second;
				}
				M[fx].clear();
			}
		}
		else
		{
			int fx=find(x);
			auto it=M[fx].find(y);
			if(it!=M[fx].end())printf("%d\n",it->second);
			else printf("0\n");
		}
	}
	return 0;
}