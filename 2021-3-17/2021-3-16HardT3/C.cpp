#include"C.hpp"
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int,int> > Ans;
int X;
vector<int> TA,TB;
bool search(vector<int> V,bool empty)
{
	if(empty)
	{
		V.push_back(1);
		bool empty=!ask(V,X);
		V.pop_back();
		if(empty)
		{
			TB.insert(TB.end(),V.begin(),V.end());
			return false;
		}
	}
	if(V.size()==1)
	{
		TA.push_back(V[0]);
		return true;
	}
	bool R=search(vector<int>(V.begin(),V.begin()+V.size()/2),true);
	search(vector<int>(V.begin()+V.size()/2,V.end()),R);
	return true;
}
vector<int> fS(vector<int> S,bool empty)
{
	if(S.empty())return vector<int>();
	if(empty)
	{
		S.push_back(1);
		bool empty=!ask(S,X);
		S.pop_back();
		if(empty)return S;
	}
	if(S.size()==1)
	{
		Ans.push_back(make_pair(X,S[0]));
		return vector<int>();
	}
	vector<int> R=fS(vector<int>(S.begin(),S.begin()+S.size()/2),true);
	vector<int> E=fS(vector<int>(S.begin()+S.size()/2,S.end()),R.size()<S.size()/2);
	R.insert(R.end(),E.begin(),E.end());
	return R;
}
vector<int> solve(vector<int> N,vector<int> S,vector<int> I)
{
	if(N.size()==1)
	{
		for(int i=0;i<S.size();i++)Ans.push_back(make_pair(N[0],S[i]));
		X=N[0];
		return fS(I,true);
	}
	if(N.size()==2)
	{
		Ans.push_back(make_pair(N[0],N[1]));
		X=N[1];
		S=fS(S,true);
		for(int i=0;i<S.size();i++)Ans.push_back(make_pair(N[0],S[i]));
		I=fS(I,true);
		X=N[0];
		return fS(I,true);
	}
	int x=X=N[1];
	TA.clear();TB.clear();
	TA.push_back(x);TB.push_back(N[0]);
	search(vector<int>(N.begin()+2,N.end()),true);
	vector<int> A(TA),B(TB);
	vector<int> G(S);
	G.insert(G.end(),I.begin(),I.end());
	G=solve(A,vector<int>(),G);
	vector<int> Q(1,x),W;
	for(int i=0;i<S.size();i++)
	{
		if(find(G.begin(),G.end(),S[i])!=G.end())Q.push_back(S[i]);
	}
	for(int i=0;i<I.size();i++)
	{
		if(find(G.begin(),G.end(),I[i])!=G.end())W.push_back(I[i]);
	}
	return solve(B,Q,W);
}
vector<pair<int,int> > work(int n)
{
	vector<int> N;
	for(int i=1;i<=n;i++)N.push_back(i);
	solve(N,vector<int>(),vector<int>());
	return Ans;
}