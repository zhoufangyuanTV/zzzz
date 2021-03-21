#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int p[110000];
int fa[110000],son[110000],h[110000];
void dfs1(int x)
{
	son[x]=0;h[x]=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dfs1(y);
			if(h[son[x]]<h[y])son[x]=y;
			if(h[x]<h[y]+1)h[x]=h[y]+1;
		}
	}
}
int m,f[110000];
bool dfs2(int x)
{
	vector<int> fy;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			if(dfs2(y)==false)return false;
			if(f[y]+1>m)return false;
			fy.push_back(f[y]+1);
		}
	}
	sort(fy.begin(),fy.end());
	if(x==1)
	{
		if(fy.size()&1)fy.pop_back();
		bool bk=true;
		for(int i=0,j=fy.size()-1;i<j;i++,j--)
		{
			if(fy[i]+fy[j]>m){bk=false;break;}
		}
		return bk;
	}
	if(fy.size()&1)
	{
		int i;
		for(i=0;i<fy.size();i++)
		{
			bool bk=true;
			int j=0,k=fy.size()-1;
			if(j==i)j++;
			if(k==i)k--;
			while(j<k)
			{
				if(fy[j]+fy[k]>m){bk=false;break;}
				j++;k--;
				if(j==i)j++;
				if(k==i)k--;
			}
			if(bk){f[x]=fy[i];break;}
		}
		if(i==fy.size())return false;
	}
	else
	{
		bool bk=true;
		for(int i=0,j=fy.size()-1;i<j;i++,j--)
		{
			if(fy[i]+fy[j]>m){bk=false;break;}
		}
		if(bk)f[x]=0;
		else
		{
			fy.pop_back();
			int i;
			for(i=0;i<fy.size();i++)
			{
				bk=true;
				int j=0,k=fy.size()-1;
				if(j==i)j++;
				if(k==i)k--;
				while(j<k)
				{
					if(fy[j]+fy[k]>m){bk=false;break;}
					j++;k--;
					if(j==i)j++;
					if(k==i)k--;
				}
				if(bk){f[x]=fy[i];break;}
			}
			if(i==fy.size())return false;
		}
	}
	return true;
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	int n,type;scanf("%d%d",&n,&type);
	len=0;memset(last,0,sizeof(last));
	memset(p,0,sizeop(p));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		p[x]++;p[y]++;
	}
	int ss=0;
	for(int i=1;i<=n;i++)ss+=p[i]&1;
	printf("%d\n",ss/2);
	if(type==1)return 0;
	fa[1]=0;h[0]=-1;dfs1(1);
	int l=1,r=n;
	while(l<r)
	{
		m=(l+r)/2;
		if(dfs2())r=m;
		else l=m+1;
	}
	printf("%d\n",r);
	if(type==2)return 0;
	return 0;
}