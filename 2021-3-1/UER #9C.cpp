#include"head.h"
void work(int N,int tp,int &a,int &b,int &c)
{
	int s=query(0,0,0)/2;
	if(s<=N)
	{
		a=N-query(N,0,0)/2;
		b=N-query(a,N,0)/2;
		c=s-a-b;
	}
	else if(s>=2*N)
	{
		c=query(N,N,0)/2;
		b=query(N,0,c)/2;
		a=s-b-c;
	}
	else
	{
		int t=query(N,s-N,0)/2;
		if(t+N<=s)b=s-N+query(N,s-t-N,t)/2-t;
		else b=query(s-t,0,t)/2;
		if(s-b<=N)a=N-t,c=s-a-b;
		else c=t,a=s-b-c;
	}
}