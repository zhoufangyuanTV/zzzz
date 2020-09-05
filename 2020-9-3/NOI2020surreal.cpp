#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int rt[2010000],l[2010000],r[2010000];
vector<int> b[4];
bool dfs(int ll,int rr)
{
	if(ll>rr)
	{
		return false;
	}
	b[0].clear();b[1].clear();b[2].clear();b[3].clear();
	bool bk=false;
	for(int i=ll;i<=rr;i++)
	{
		if(l[rt[i]]==0&&r[rt[i]]==0)return true;
		if(l[rt[i]]==0)b[0].push_back(r[rt[i]]);
		else if(r[rt[i]]==0)b[1].push_back(l[rt[i]]);
		else if(l[l[rt[i]]]==0&&r[l[rt[i]]]==0&&l[r[rt[i]]]==0&&r[r[rt[i]]]==0)bk=true;
		else if(l[l[rt[i]]]==0&&r[l[rt[i]]]==0)b[2].push_back(r[rt[i]]);
		else b[3].push_back(l[rt[i]]);
	}
	int l0=ll,r0=l0+b[0].size()-1;
	int l1=r0+1,r1=l1+b[1].size()-1;
	for(int i=l0;i<=r0;i++)rt[i]=b[0][i-l0];
	for(int i=l1;i<=r1;i++)rt[i]=b[1][i-l1];
	if(bk)return dfs(l0,r0)&&dfs(l1,r1);
	int l2=r1+1,r2=l2+b[2].size()-1;
	int l3=r2+1,r3=l3+b[3].size()-1;
	for(int i=l2;i<=r2;i++)rt[i]=b[2][i-l2];
	for(int i=l3;i<=r3;i++)rt[i]=b[3][i-l3];
	return dfs(l0,r0)&&dfs(l1,r1)&&dfs(l2,r2)&&dfs(l3,r3);
}
int main()
{
	freopen("surreal.in","r",stdin);
	freopen("surreal.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)
	{
		int n;scanf("%d",&n);
		int len=0,ilen=0;
		while(n--)
		{
			int size;scanf("%d",&size);
			for(int j=len+1;j<=len+size;j++)
			{
				scanf("%d%d",&l[j],&r[j]);
				if(l[j]!=0)l[j]+=len;
				if(r[j]!=0)r[j]+=len;
			}
			int x=len+1;
			bool bk=true;
			while(x!=0&&(l[x]!=0||r[x]!=0))
			{
				if(l[x]==0||l[l[x]]==0&&r[l[x]]==0)x=r[x];
				else if(r[x]==0||l[r[x]]==0&&r[r[x]]==0)x=l[x];
				else
				{
					bk=false;break;
				}
			}
			if(bk)rt[++ilen]=len+1,len+=size;
		}
		printf("%s\n",dfs(1,ilen)?"Almost Complete":"No");
	}
	return 0;
}