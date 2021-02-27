#include"head.h"
int query(int x,int y,int z);
void work(int N,int tp,int &a,int &b,int &c)
{
	if(tp==1||tp==2)
	{
		long long s1=query(0,0,0),s2=query(0,0,N),s3=query(N,N,0);
		long long ab=(s2-s3)/2+N;c=s1/2-ab;
		if(ab>=N)
		{
			long long s4=query(N,0,0);
			b=s4/2;
			a=ab-b;
		}
		else
		{
			long long s4=query(N,0,0);
			a=N-s4/2;
			b=ab-a;
		}
	}
}