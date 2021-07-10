#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
char a[210000],b[210000];
bool f[210000];
int s[210000];
bitset<200000> A,B;
int k;
void g(int n,int m,char c)
{
	s[0]=a[0]==c;
	for(int i=1;i<n;i++)s[i]=s[i-1]+(a[i]==c);
	for(int i=0;i<n;i++)
	{
		int l=i-k,r=i+k;
		int sl,sr;
		if(l<=0)sl=0;
		else sl=s[l-1];
		if(r>=n)sr=s[n-1];
		else sr=s[r];
		if(sl<sr)A[i]=0;
		else A[i]=1;
	}
	B.reset();
	for(int i=0;i<m;i++)B[i]=b[i]==c;
	int j=0;
	for(int i=0;i<=n-m;i++)
	{
		if(f[i])
		{
			if(j<i)
			{
				B<<=i-j;
				j=i;
			}
			if((A&B).any())f[i]=false;
		}
	}
}
int main()
{
	freopen("base.in","r",stdin);
	freopen("base.out","w",stdout);
	scanf("%d%s%s",&k,a,b);
	int n=strlen(a),m=strlen(b);
	memset(f,true,sizeof(f));
	g(n,m,'Z');g(n,m,'P');g(n,m,'S');g(n,m,'B');
	int ss=0;
	for(int i=0;i<=n-m;i++)ss+=f[i];
	printf("%d\n",ss);
	return 0;
}
