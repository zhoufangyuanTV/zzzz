#include"Bruno.h"
#include<vector>
using namespace std;
vector<int> Bruno(int K,vector<int> value)
{
	int X;
	for(X=0;X<9;X++)if(value[X]==12)break;
	vector<int> p;
	int vv;
	if(X==0)p={-1,7,0,3,1,2,6,4,5},vv=value[2];
	else if(X==1)p={0,-1,7,2,3,1,5,6,4},vv=value[0];
	else if(X==2)p={7,0,-1,1,2,3,4,5,6},vv=value[1];
	else if(X==3)p={6,4,5,-1,7,0,3,1,2},vv=value[5];
	else if(X==4)p={5,6,4,0,-1,7,2,3,1},vv=value[3];
	else if(X==5)p={4,5,6,7,0,-1,1,2,3},vv=value[4];
	else if(X==6)p={3,1,2,6,4,5,-1,7,0},vv=value[8];
	else if(X==7)p={2,3,1,5,6,4,0,-1,7},vv=value[6];
	else p={1,2,3,4,5,6,7,0,-1},vv=value[7];
	vector<int> Ans;Ans.resize(K);
	if(p[0]>0)
	{
		int pp=p[0]-1,v=value[0];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==8||v==9||v==10||v==11||v==12)Ans[pp]=3;
			else if(v==6||v==7)Ans[pp]=1;
			else Ans[pp]=4;
		}
	}
	if(p[1]>0)
	{
		int pp=p[1]-1,v=value[1];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==5||v==8||v==10)Ans[pp]=0;
			else if(v==7||v==9||v==12)Ans[pp]=1;
			else if(v==11)Ans[pp]=3;
			else Ans[pp]=4;
		}
	}
	if(p[2]>0)
	{
		int pp=p[2]-1,v=value[2];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==8||v==9||v==10||v==11||v==12)Ans[pp]=3;
			else if(v==5||v==6)Ans[pp]=0;
			else Ans[pp]=4;
		}
	}
	if(p[3]>0)
	{
		int pp=p[3]-1,v=value[3];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==6||v==7||v==9||v==11||v==12)Ans[pp]=1;
			else if(v==5)Ans[pp]=2;
			else if(v==10)Ans[pp]=3;
			else Ans[pp]=4;
		}
	}
	if(p[4]>0)
	{
		int pp=p[4]-1,v=value[4];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==5||v==6||v==7)Ans[pp]=2;
			else if(v==10||v==11||v==12)Ans[pp]=3;
			else if(v==8)Ans[pp]=0;
			else if(v==9)Ans[pp]=1;
		}
	}
	if(p[5]>0)
	{
		int pp=p[5]-1,v=value[5];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==5||v==6||v==8||v==10||v==11)Ans[pp]=0;
			else if(v==7)Ans[pp]=2;
			else if(v==12)Ans[pp]=3;
			else Ans[pp]=4;
		}
	}
	if(p[6]>0)
	{
		int pp=p[6]-1,v=value[6];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==5||v==6||v==7||v==8||v==9)Ans[pp]=2;
			else if(v==11||v==12)Ans[pp]=1;
			else Ans[pp]=4;
		}
	}
	if(p[7]>0)
	{
		int pp=p[7]-1,v=value[7];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==5||v==6||v==7||v==8||v==9)Ans[pp]=2;
			else if(v==10)Ans[pp]=0;
			else if(v==12)Ans[pp]=1;
			else Ans[pp]=4;
		}
	}
	if(p[8]>0)
	{
		int pp=p[8]-1,v=value[8];
		if(v>vv)v++;
		if(v==1)Ans[pp]=2;
		else if(v==2)Ans[pp]=0;
		else if(v==3)Ans[pp]=1;
		else if(v==4)Ans[pp]=3;
		else
		{
			if(v==5||v==6||v==7||v==8||v==9)Ans[pp]=2;
			else if(v==10||v==11)Ans[pp]=0;
			else Ans[pp]=4;
		}
	}
	return Ans;
}