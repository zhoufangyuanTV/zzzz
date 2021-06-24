#include<cstdio>
using namespace std;
char s[16777217];
bool b[16777217];
int g[110];
int main()
{
	freopen("majiang.in","r",stdin);
	freopen("majiang.out","w",stdout);
	int n=fread(s+1,1,1<<24,stdin);
	unsigned f=0;
	for(int i=1;i<=n;i++)
	{
		f=f<<1|s[i]-'0';
		if(24<=i)b[f&16777215]=true;
		else g[i]=f;
	}
	int p;
	for(int i=0;i<16777216;i++)if(!b[i])p=i;
	for(int t=23;t>=1;t--)
	{
		int pp=-1;
		if(t<=n)b[g[t]]=true;
		for(int i=(1<<t)-1;i>=0;i--)
		{
			b[i]|=b[i|1<<t];
			if(!b[i])pp=i;
		}
		if(pp==-1)
		{
			for(int i=t;i>=0;i--)putchar((p>>i&1)+'0');
			return 0;
		}
		else p=pp;
	}
	putchar(p+'0');
	return 0;
}