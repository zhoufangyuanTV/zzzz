#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct N
{
	vector<int> x;
	long long suo();
	void ti();
};
char s[310000];
inline int lowbit(int x){return x&-x;}
long long N::suo()
{
	long long ss=0;
	int i;
	for(i=0;i<x.size();i++)
	{
		if(x[i]>0)break;
		ss+=30;
	}
	for(int j=i;j<x.size();j++)x[j-i]=x[j];
	x.resize(x.size()-i);
	int k=lowbit(x[0]);
	if(k==1)return ss;
	int kk=1073741824/k;
	for(int j=0;j<x.size();j++)
	{
		int y=x[j]&(k-1);
		if(j>0)x[j-1]|=y*kk;
		x[j]/=k;
	}
	if(x[x.size()-1]==0)x.resize(x.size()-1);
	while(k>1)
	{
		ss++;k>>=1;
	}
	return ss;
}
void N::ti()
{
	int g=1;
	for(int i=0;i<x.size();i++)
	{
		int gg=x[i]>>29;
		int y=(x[i]-(gg<<29))<<1;
		int z=x[i]+y+g;
		if(z<1073741824)x[i]=z,g=gg;
		else x[i]=z-1073741824,g=gg+1;
	}
	if(g>0)x.push_back(g);
}
int main()
{
	freopen("lxl.in","r",stdin);
	freopen("lxl.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	N A;
	A.x.resize((n+29)/30);
	for(int i=0;i<A.x.size();i++)
	{
		int X=0;
		int st=n-i*30-29;
		if(st<1)st=1;
		for(int j=st;j<=n-i*30;j++)X=X*2+s[j]-'0';
		A.x[i]=X;
	}
	long long ss=A.suo();
	while(A.x.size()>1||A.x[0]!=1)
	{
		ss++;A.ti();ss+=A.suo();
	}
	printf("%lld\n",ss);
	return 0;
}
