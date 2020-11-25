#include<cstdio>
#include<cstring>
using namespace std;
inline long long mymax(long long x,long long y){return x>y?x:y;}
int f[71][71][72][72],p[72],q[72],r[72],s[72];
inline int c(int z,int a,int b,int d){return (p[z]-q[a])*(p[z]-q[a])+(p[a]-r[b])*(p[a]-r[b])+(p[b]-s[d])*(p[b]-s[d]);}
int F(int l,int r,int rr,int pp)
{
	if(l>r)return 0;
	if(f[l][r][rr][pp]!=-1)return f[l][r][rr][pp];
	for(int i=pp>r?l:pp;i<=r;i++)
	{
		for(int j=i+1;j<=r+1;j++)
		{
			f[l][r][rr][pp]=mymax(f[l][r][rr][pp],F(l,i-1,j,pp)+F(i+1,r,rr,j)+c(l-1,i,r+1,rr));
		}
	}
	return f[l][r][rr][pp];
}
int main()
{
	freopen("landmine.in","r",stdin);
	freopen("landmine.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)scanf("%d",&q[i]);
	for(int i=1;i<=n;i++)scanf("%d",&r[i]);
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	memset(f,-1,sizeof(f));
	printf("%d\n",F(1,n,n+1,n+1));
	return 0;
}