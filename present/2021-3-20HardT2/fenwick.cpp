#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
int k,p,t;
int bl[210000];
struct node{int p,c;};
inline bool cmp(node x,node y){return x.p<y.p;}
vector<node> ex[30][210000];
map<int,int> M;
struct Query{int opt,x,c;}Q[210000];
inline int lowbitv(int x)
{
	int b=1;
	while(x/b%k==0)b=b*k;
	return b;
}
inline int lowbit(int x){return x/lowbitv(x)%k;}
inline int lowbit2(int x){return x&-x;}
int main()
{
	freopen("fenwick.in","r",stdin);
	freopen("fenwick.out","w",stdout);
	int n,m;scanf("%d%d%d",&n,&m,&k);
	p=lowbit2(k);t=k/p;
	memset(bl,0,sizeof(bl));
	for(int i=1;i<t;i++)
	{
		if(bl[i]==0)
		{
			int j=i;
			while(bl[j]==0){bl[j]=i;j=j*2%t;}
		}
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&Q[i].opt,&Q[i].x);
		if(Q[i].opt==1)
		{
			scanf("%d",&Q[i].c);
			int x=Q[i].x;
			int low=lowbit(x);
			while(x<=n&&lowbit2(low)<p)
			{
				x+=low*lowbitv(x);
				low=lowbit(x);
			}
			if(x<=n)
			{
				int d=0;
				int xx=x;
				while(x%k==0){d++;x=x/k;}
				ex[d][bl[low/p]].push_back((node){xx,0});
			}
		}
	}
	for(int i=0;i<=29;i++)
	{
		for(int j=1;j<t;j++)sort(ex[i][j].begin(),ex[i][j].end(),cmp);
	}
	for(int i=1;i<=m;i++)
	{
		if(Q[i].opt==1)
		{
			int x=Q[i].x;
			int low=lowbit(x);
			while(x<=n&&lowbit2(low)<p)
			{
				M[x]^=Q[i].c;
				x+=low*lowbitv(x);
				low=lowbit(x);
			}
			if(x<=n)
			{
				int d=0;
				int xx=x;
				while(x%k==0){d++;x=x/k;}
				int pos=lower_bound(ex[d][bl[low/p]].begin(),ex[d][bl[low/p]].end(),(node){xx,0},cmp)-ex[d][bl[low/p]].begin();
				while(pos<ex[d][bl[low/p]].size())
				{
					ex[d][bl[low/p]][pos].c^=Q[i].c;
					pos+=lowbit2(pos+1);
				}
			}
		}
		else
		{
			int ss=0;
			int x=Q[i].x;
			int d=0,pp=1;
			while(x>0)
			{
				while(x/pp%k==0){d++;pp*=k;}
				int low=x/pp%k;
				if(lowbit2(low)<p)ss^=M[x];
				else
				{
					int pos=upper_bound(ex[d][bl[low/p]].begin(),ex[d][bl[low/p]].end(),(node){x,0},cmp)-ex[d][bl[low/p]].begin()-1;
					while(pos>-1)
					{
						ss^=ex[d][bl[low/p]][pos].c;
						pos-=lowbit2(pos+1);
					}
				}
				x-=low*pp;
			}
			printf("%d\n",ss);
		}
	}
	return 0;
}