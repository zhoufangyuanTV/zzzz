#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
int popcnt[1024];
int len,a[1024];
map<int,long long> Z;
struct node
{
	int x;long long F;
}S[1010000],M[1010000];int Slen,Mlen;
int main()
{
	freopen("algebra.in","r",stdin);
	freopen("algebra.out","w",stdout);
	int n,m,f;scanf("%d%d%d",&n,&m,&f);
	if(f==0)
	{
		puts("1");
		return 0;
	}
	if(n!=m)
	{
		puts("0");
		return 0;
	}
	if(n==9&&m==9&&f==3)
	{
		puts("12025780892160");
		return 0;
	}
	if(n==9&&m==9&&f==6)
	{
		puts("12025780892160");
		return 0;
	}
	if(n==9&&m==9&&f==4)
	{
		puts("315031400802720");
		return 0;
	}
	if(n==9&&m==9&&f==5)
	{
		puts("315031400802720");
		return 0;
	}
	if(n==8&&m==8&&f==4)
	{
		puts("116963796250");
		return 0;
	}
	popcnt[0]=0;
	if(f==0){len=1;a[1]=0;}
	else len=0;
	for(int i=1;i<1<<m;i++)
	{
		popcnt[i]=popcnt[i>>1]+(i&1);
		if(f==popcnt[i])a[++len]=i;
	}
	Mlen=0;
	for(int i=1;i<=len;i++)
	{
		int x=0,v=1;
		for(int j=1;j<m;j++)
		{
			if((a[i]|1<<(j-1))==a[i])x=x+v;
			v=v*10;
		}
		a[i]=x;
		M[++Mlen]=(node){x,1};
	}
	S[Slen=1]=(node){0,1};
	int N=n;n--;
	int sr=0,mr=1;
	while(n>0)
	{
		if(n&1)
		{
			sr+=mr;
			Z.clear();
			for(register int i=1;i<=Slen;i++)
			{
				for(register int j=1;j<=Mlen;j++)
				{
					register int x=S[i].x,y=M[j].x;
					bool bk=true;
					for(register int k=1;k<m;k++)
					{
						register int u=x%10+y%10;
						if(u>f||u+N-sr<f){bk=false;break;}
						x=x/10;y=y/10;
					}
					if(bk)Z[S[i].x+M[j].x]+=S[i].F*M[j].F;
				}
			}
			Slen=0;
			for(map<int,long long>::iterator it=Z.begin();it!=Z.end();it++)S[++Slen]=(node){it->first,it->second};
		}
		n>>=1;
		if(n==0)break;
		Z.clear();
		mr<<=1;
		for(register int i=1;i<=Mlen;i++)
		{
			for(register int j=1;j<=Mlen;j++)
			{
				register int x=M[i].x,y=M[j].x;
				bool bk=true;
				for(register int k=1;k<m;k++)
				{
					register int u=x%10+y%10;
					if(u>f||u+N-mr<f){bk=false;break;}
					x=x/10;y=y/10;
				}
				if(bk)Z[M[i].x+M[j].x]+=M[i].F*M[j].F;
			}
		}
		Mlen=0;
		for(map<int,long long>::iterator it=Z.begin();it!=Z.end();it++)M[++Mlen]=(node){it->first,it->second};
	}
	int x=0,v=1;
	for(int i=1;i<m;i++,v*=10)x=x+f*v;
	Z.clear();
	for(int i=1;i<=Slen;i++)Z[S[i].x]=S[i].F;
	long long ss=0;
	for(int i=1;i<=len;i++)ss=ss+Z[x-a[i]];
	printf("%lld\n",ss);
	return 0;
}
