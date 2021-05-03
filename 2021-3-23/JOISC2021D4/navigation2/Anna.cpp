#include"Anna.h"
#include<vector>
#include<bitset>
using namespace std;
void Anna(int N,int K,vector<int> R,vector<int> C)
{
	vector<vector<int>> flag;
	bitset<10> b;b.reset();
	const int w[3][3]={{1,2,3},{4,5,6},{7,0,-1}};
	flag.resize(N);
	for(int i=0;i<N;i++)flag[i].resize(N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)flag[i][j]=w[i%3][j%3];
	}
	for(int i=0;i<K;i++)
	{
		if(flag[R[i]-1][C[i]-1]==i+1)b.set(1);
		else if(flag[R[i]-1][C[i]]==i+1)b.set(2);
		else if(flag[R[i]-1][C[i]+1]==i+1)b.set(3);
		else if(flag[R[i]][C[i]-1]==i+1)b.set(4);
		else if(flag[R[i]][C[i]]==i+1)b.set(5);
		else if(flag[R[i]][C[i]+1]==i+1)b.set(6);
		else if(flag[R[i]+1][C[i]-1]==i+1)b.set(7);
		else if(flag[R[i]+1][C[i]]==i+1)b.set(8);
		else b.set(9);
	}
	int vv,wx,wy;
	for(vv=1;vv<=9;vv++)if(b[vv]==false)break;
	if(vv==1)wx=2,wy=2;
	else if(vv==2)wx=2,wy=0;
	else if(vv==3)wx=2,wy=1;
	else if(vv==4)wx=0,wy=2;
	else if(vv==5)wx=0,wy=0;
	else if(vv==6)wx=0,wy=1;
	else if(vv==7)wx=1,wy=2;
	else if(vv==8)wx=1,wy=0;
	else wx=1,wy=1;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)flag[i][j]=w[(i+wx)%3][(j+wy)%3];
	}
	b.reset();
	for(int i=0;i<K;i++)
	{
		if(flag[R[i]-1][C[i]-1]==i+1)b.set(1);
		else if(flag[R[i]-1][C[i]]==i+1)b.set(2);
		else if(flag[R[i]-1][C[i]+1]==i+1)b.set(3);
		else if(flag[R[i]][C[i]-1]==i+1)b.set(4);
		else if(flag[R[i]][C[i]]==i+1)b.set(5);
		else if(flag[R[i]][C[i]+1]==i+1)b.set(6);
		else if(flag[R[i]+1][C[i]-1]==i+1)b.set(7);
		else if(flag[R[i]+1][C[i]]==i+1)b.set(8);
		else b.set(9);
	}
	for(vv=1;vv<=9;vv++)if(vv!=5&&b[vv]==false)break;
	if(vv<5)vv=vv+3;
	else vv=vv+2;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(flag[i][j]==-1)SetFlag(i,j,12);
			else if(flag[i][j]==0)SetFlag(i,j,vv);
			else
			{
				int d=flag[i][j]-1;
				if(i<R[d]-1)SetFlag(i,j,1);
				else if(i>R[d]+1)SetFlag(i,j,4);
				else if(j<C[d]-1)SetFlag(i,j,2);
				else if(j>C[d]+1)SetFlag(i,j,3);
				else
				{
					int gg;
					if(i==R[d]-1&&j==C[d]-1)gg=5;
					else if(i==R[d]-1&&j==C[d])gg=6;
					else if(i==R[d]-1&&j==C[d]+1)gg=7;
					else if(i==R[d]&&j==C[d]-1)gg=8;
					else if(i==R[d]&&j==C[d]+1)gg=9;
					else if(i==R[d]+1&&j==C[d]-1)gg=10;
					else if(i==R[d]+1&&j==C[d])gg=11;
					else gg=12;
					if(gg>vv)gg--;
					SetFlag(i,j,gg);
				}
			}
		}
	}
}