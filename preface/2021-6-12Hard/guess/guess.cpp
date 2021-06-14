#include"guess.h"
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int X;
int n;
vector<int> e[3100];
int fa[6100],du[3100],tot[6100];
queue<int> Q;
bool b[3100],gg[3100];
int search(const int &rt,const vector<int> &N,const vector<pair<int,int>> &T)
{
	if(N.size()==2)return N[0]+N[1]-rt;
	if(N.size()==3&&T[0].second==rt&&T[1].second==rt)
	{
		vector<int> G=N;
		if(G[1]==rt)swap(G[0],G[1]);
		else if(G[2]==rt)swap(G[0],G[2]);
		if(G[1]>n)swap(G[1],G[2]);
		if(query({G[1],X})==G[0])return G[2];
		else return G[1];
	}
	while(!Q.empty())Q.pop();
	for(int i:N)
	{
		tot[i]=1;
		if(i<=n)
		{
			e[i].clear();
			du[i]=0;
		}
		else Q.push(i);
	}
	for(pair<int,int> i:T)
	{
		fa[i.first]=i.second;
		du[i.second]++;
		if(i.first<=n)e[i.second].push_back(i.first);
	}
	for(int i:N)
	{
		if(i<=n&&du[i]==0)Q.push(i);
	}
	while(!Q.empty())
	{
		int x=Q.front();Q.pop();
		if(x==rt)break;
		tot[fa[x]]+=tot[x];
		du[fa[x]]--;
		if(du[fa[x]]==0)Q.push(fa[x]);
	}
	int ff=0x3f3f3f3f,Al=N.size()-1;
	for(int i:N)
	{
		if(i!=rt&&i<=n)ff=min(ff,max(tot[i]-1,Al-tot[i]+1));
	}
	for(int i:N)
	{
		if(i<=n)
		{
			int s=0,ss=0,sss=0;
			for(int j:e[i])
			{
				s=max(s,tot[j]-1);
				ss+=tot[j];
				sss++;
				if(sss>1)ff=min(ff,max(s,max(Al-ss,sss)));
			}
		}
	}
	for(int i:N)
	{
		if(i!=rt&&i<=n)
		{
			if(ff==max(tot[i]-1,Al-tot[i]+1))
			{
				if(query({i,X})==i)
				{
					vector<int> A;
					vector<pair<int,int>> TA;
					Q.push(i);
					while(!Q.empty())
					{
						int x=Q.front();Q.pop();
						A.push_back(x);
						b[x]=true;
						for(int y:e[x])
						{
							Q.push(y);
							TA.push_back({y,x});
						}
					}
					for(int i:N)
					{
						if(i>n&&b[i-n])
						{
							A.push_back(i);
							TA.push_back({i,i-n});
						}
					}
					for(int i:A)if(i<=n)b[i]=false;
					return search(i,A,TA);
				}
				else
				{
					vector<int> A;
					vector<pair<int,int>> TA;
					Q.push(rt);
					while(!Q.empty())
					{
						int x=Q.front();Q.pop();
						A.push_back(x);
						if(x==i)continue;
						b[x]=true;
						for(int y:e[x])
						{
							Q.push(y);
							TA.push_back({y,x});
						}
					}
					for(int i:N)
					{
						if(i>n&&b[i-n])
						{
							A.push_back(i);
							TA.push_back({i,i-n});
						}
					}
					for(int i:A)if(i<=n)b[i]=false;
					return search(rt,A,TA);
				}
			}
		}
	}
	for(int i:N)
	{
		if(i<=n)
		{
			int s=0,ss=0,sss=0;
			vector<int> S;
			for(int j:e[i])
			{
				s=max(s,tot[j]-1);
				ss+=tot[j];
				sss++;
				S.push_back(j);
				if(sss>1&&ff==max(s,max(Al-ss,sss)))
				{
					S.push_back(X);
					int re=query(S);
					S.pop_back();
					if(re==i)
					{
						for(int i:S)gg[i]=true;
						vector<int> A;
						vector<pair<int,int>> TA;
						Q.push(rt);
						while(!Q.empty())
						{
							int x=Q.front();Q.pop();
							A.push_back(x);
							b[x]=true;
							for(int y:e[x])
							{
								if(gg[y])continue;
								Q.push(y);
								TA.push_back({y,x});
							}
						}
						for(int i:N)
						{
							if(i>n&&b[i-n])
							{
								A.push_back(i);
								TA.push_back({i,i-n});
							}
						}
						for(int i:A)if(i<=n)b[i]=false;
						for(int i:S)gg[i]=false;
						return search(rt,A,TA);
					}
					else if(find(S.begin(),S.end(),re)!=S.end())
					{
						vector<int> A;
						vector<pair<int,int>> TA;
						Q.push(re);
						while(!Q.empty())
						{
							int x=Q.front();Q.pop();
							A.push_back(x);
							b[x]=true;
							for(int y:e[x])
							{
								Q.push(y);
								TA.push_back({y,x});
							}
						}
						for(int i:N)
						{
							if(i>n&&b[i-n])
							{
								A.push_back(i);
								TA.push_back({i,i-n});
							}
						}
						for(int i:A)if(i<=n)b[i]=false;
						return search(re,A,TA);
					}
					else
					{
						vector<int> A;
						vector<pair<int,int>> TA;
						A=S;
						A.push_back(i);
						for(int y:S)TA.push_back({y,i});
						return search(i,A,TA);
					}
				}
			}
		}
	}
}
vector<int> N;
vector<pair<int,int>> T;
bool v[3100];
void solve(int n,int L,int data_type)
{
	::n=n;
	N.clear();
	T.clear();
	fill(v+1,v+n+1,false);
	N.push_back(1);
	N.push_back(n+1);
	T.push_back({n+1,1});
	v[1]=true;
	for(int i=2;i<=n;i++)
	{
		if(v[i]==false)
		{
			X=i;
			int x=search(1,N,T);
			if(x<=n)
			{
				auto it=T.begin();
				for(;it!=T.end();it++)
				{
					if(it->first==x)break;
				}
				int f=it->second;
				int re=query({x,i});
				if(re==i)
				{
					T.erase(it);
					T.push_back({x,i});
					T.push_back({i,f});
					T.push_back({n+i,i});
					N.push_back(i);
					N.push_back(n+i);
					v[i]=true;
				}
				else
				{
					T.erase(it);
					T.push_back({x,re});
					T.push_back({re,f});
					T.push_back({i,re});
					T.push_back({n+re,re});
					T.push_back({n+i,i});
					N.push_back(re);
					N.push_back(n+re);
					N.push_back(i);
					N.push_back(n+i);
					v[i]=v[re]=true;
				}
			}
			else
			{
				T.push_back({i,x-n});
				T.push_back({n+i,i});
				N.push_back(i);
				N.push_back(n+i);
				v[i]=true;
			}
		}
	}
	for(auto i:T)
	{
		if(i.first<=n)report(i.first,i.second);
	}
}
