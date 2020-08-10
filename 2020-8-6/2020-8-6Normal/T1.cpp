#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
map<unsigned,int> M;
unsigned gcd(unsigned x,unsigned y){return y==0?x:gcd(y,x%y);}
int base[8][16];
struct node
{
	unsigned d;int c;
}dabiao[8][32768];int len[8];
int main()
{
	base[1][0]=1;base[1][1]=1;
	base[2][0]=1;base[2][1]=2;
	base[3][0]=2;base[3][1]=3;base[3][2]=4;
	base[4][0]=3;base[4][1]=4;base[4][2]=6;base[4][3]=10;
	base[5][0]=6;base[5][1]=5;base[5][2]=6;base[5][3]=8;base[5][4]=9;base[5][5]=14;base[5][6]=21;
	base[6][0]=6;base[6][1]=6;base[6][2]=8;base[6][3]=10;base[6][4]=14;base[6][5]=44;base[6][6]=52;
	base[7][0]=15;base[7][1]=7;base[7][2]=8;base[7][3]=9;base[7][4]=10;base[7][5]=12;base[7][6]=15;base[7][7]=22;base[7][8]=33;base[7][9]=39;base[7][10]=52;base[7][11]=55;base[7][12]=68;base[7][13]=102;base[7][14]=114;base[7][15]=138;
	for(int i=1;i<=7;i++)
	{
		M.clear();
		for(int j=1;j<1<<base[i][0];j++)
		{
			unsigned lcm=1,sr=0;
			for(int k=1;k<=base[i][0];k++)
			{
				if((j|1<<(k-1))==j)
				{
					sr++;lcm/=gcd(lcm,base[i][k]);
					lcm*=base[i][k];
				}
			}
			if(sr%2==1)M[lcm]++;
			else M[lcm]--;
		}
		len[i]=0;
		for(map<unsigned,int>::iterator it=M.begin();it!=M.end();it++)
		{
			if((*it).second==0)continue;
			len[i]++;
			dabiao[i][len[i]].d=(*it).first;
			dabiao[i][len[i]].c=(*it).second;
		}
	}
	int t;scanf("%d",&t);
	while(t--)
	{
		long long a,b,k;scanf("%lld%lld%lld",&a,&b,&k);a--;
		long long SA=0,SB=0;
		for(int i=1;i<=len[k];i++)
		{
			SA+=a/dabiao[k][i].d*dabiao[k][i].c;
			SB+=b/dabiao[k][i].d*dabiao[k][i].c;
		}
		printf("%lld\n",SB-SA);
	}
	return 0;
}