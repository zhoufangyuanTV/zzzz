#include"greedy.h"
#include"grader.cpp"
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
int sz,askv[3100];
int type,Ans[3100];
void solve(int rt,vector<int> N)
{
	if(N.size()==1)return ;
	if(N.size()==3)
	{
		for(int i=0;i<N.size();i++)
		{
			if(N[i]!=rt)Ans[N[i]-1]=rt;
		}
		return ;
	}
	int x=rand()%(N.size()-1)+1;
	for(int i=0;i<N.size();i++)
	{
		if(N[i]!=rt)
		{
			x--;
			if(x==0){x=N[i];break;}
		}
	}
	sz=1;askv[0]=x;
	for(int i=0;i<N.size();i++)
	{
		if(N[i]!=x)askv[sz++]=N[i];
	}
	int ss=ask(sz,askv);
	vector<int> A,B;
	A.push_back(x);A.push_back(rt);
	B.push_back(x);
	for(int i=0;i<N.size();i++)
	{
		if(N[i]!=rt&&N[i]!=x)
		{
			sz=2;
			askv[0]=x;askv[1]=N[i];
			if(ask(sz,askv)==2)
			{
				A.push_back(N[i]);
			}
			else
			{
				sz=1;
				askv[0]=N[i];
				for(int j=0;j<N.size();j++)
				{
					if(N[i]!=N[j])askv[sz++]=N[j];
				}
				int s=ask(sz,askv);
				if(s<ss)A.push_back(N[i]);
				else B.push_back(N[i]);
			}
		}
	}
	solve(rt,A);
	solve(x,B);
}
void solve(int n,int ty)
{
	type=ty;
	int rt;
	for(int i=1;i<=n;i++)
	{
		sz=1;askv[0]=i;
		for(int j=1;j<=n;j++)
		{
			if(i!=j)askv[sz++]=j;
		}
		if(ask(sz,askv)==1){rt=i;break;}
	}
	vector<int> N;
	for(int i=1;i<=n;i++)N.push_back(i);
	Ans[rt-1]=0;
	solve(rt,N);
	answer(Ans);
}
int main () {
	Gmain();
	return 0;
}


