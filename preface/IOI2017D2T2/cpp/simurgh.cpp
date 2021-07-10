#include"simurgh.h"
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y,c,next;
}a[310000];int len,last[510];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
bool b[510];
int list[510];
int fa[510];
int findfa(int x){return fa[x]!=x?fa[x]=findfa(fa[x]):x;}
vector<int> e,E;
int f[510],fy[510],dep[510],ty[210000];
int S[510];
vector<int> find_roads(int n,vector<int> u,vector<int> v)
{
	int m=u.size();
	len=0;memset(last,0,sizeof(last));
	for(int i=0;i<m;i++)
	{
		ins(u[i],v[i],i);
		ins(v[i],u[i],i);
	}
	memset(b,false,sizeof(b));
	int st=rand()%n;b[st]=true;
	int head=1,tail=2;list[1]=st;f[st]=fy[st]=-1;dep[st]=1;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(!b[y])
			{
				b[y]=true;
				list[tail++]=y;
				f[y]=a[k].c;
				fy[y]=x;
				dep[y]=dep[x]+1;
				e.push_back(a[k].c);
			}
		}
		head++;
	}
	int UT=count_common_roads(e);
	memset(ty,-1,sizeof(ty));
	for(int i=0;i<n;i++)fa[i]=i;
	for(int i=0;i<m;i++)
	{
		vector<int>::iterator it=find(e.begin(),e.end(),i);
		if(it==e.end())
		{
			int Fax=findfa(u[i]),Fay=findfa(v[i]);
			if(Fax==Fay){ty[i]=0;continue;}
			E.clear();
			int x=u[i],y=v[i];
			while(x!=y)
			{
				if(dep[x]<dep[y])
				{
					E.push_back(f[y]);
					y=fy[y];
				}
				else
				{
					E.push_back(f[x]);
					x=fy[x];
				}
			}
			int p=-1;
			for(it=E.begin();it!=E.end();it++)
			{
				if(ty[*it]==-1)
				{
					Fax=findfa(u[*it]);Fay=findfa(v[*it]);
					if(Fax==Fay)ty[*it]=0;
				}
				if(ty[*it]!=-1){p=*it;break;}
			}
			if(p==-1)
			{
				int MM=-999;
				for(int j=0;j<E.size();j++)
				{
					vector<int> As=e;
					As.erase(find(As.begin(),As.end(),E[j]));
					As.push_back(i);
					S[j]=count_common_roads(As)-UT;
					if(S[j]>MM)MM=S[j];
				}
				if(MM==-1)
				{
					ty[i]=0;
					for(int j=0;j<E.size();j++)
					{
						ty[E[j]]=1;
						Fax=findfa(u[E[j]]);Fay=findfa(v[E[j]]);
						fa[Fax]=Fay;
					}
				}
				else if(MM==0)
				{
					ty[i]=0;
					for(int j=0;j<E.size();j++)
					{
						if(S[j]==-1)
						{
							ty[E[j]]=1;
							Fax=findfa(u[E[j]]);Fay=findfa(v[E[j]]);
							fa[Fax]=Fay;
						}
						else ty[E[j]]=0;
					}
				}
				else if(MM==1)
				{
					ty[i]=1;
					Fax=findfa(u[i]);Fay=findfa(v[i]);
					fa[Fax]=Fay;
					for(int j=0;j<E.size();j++)
					{
						if(S[j]==0)
						{
							ty[E[j]]=1;
							Fax=findfa(u[E[j]]);Fay=findfa(v[E[j]]);
							fa[Fax]=Fay;
						}
						else ty[E[j]]=0;
					}
				}
			}
			else
			{
				vector<int> re=e;
				re.erase(find(re.begin(),re.end(),p));
				re.push_back(i);
				int SS=count_common_roads(re)-UT;
				ty[i]=SS+ty[p];
				if(ty[i]==1)
				{
					Fax=findfa(u[i]);Fay=findfa(v[i]);
					fa[Fax]=Fay;
				}
				for(int j=0;j<E.size();j++)
				{
					if(ty[E[j]]==-1)
					{
						Fax=findfa(u[E[j]]);Fay=findfa(v[E[j]]);
						if(Fax==Fay)ty[E[j]]=0;
					}
					if(ty[E[j]]==-1)
					{
						re=e;
						re.erase(find(re.begin(),re.end(),E[j]));
						re.push_back(i);
						int SSS=count_common_roads(re)-UT;
						ty[E[j]]=ty[i]-SSS;
						if(ty[E[j]]==1)
						{
							Fax=findfa(u[E[j]]);Fay=findfa(v[E[j]]);
							fa[Fax]=Fay;
						}
					}
				}
			}
		}
	}
	e.clear();
	for(int i=0;i<m;i++)
	{
		if(ty[i]!=0)e.push_back(i);
	}
	return e;
}