#include<cstdio>
#include<cstring>
using namespace std;
struct node{int n,a[110000];}p,q,A,r,ss;
node operator*(node x,node y)
{
	node z;z.n=x.n;
	for(int i=1;i<=z.n;i++)z.a[i]=y.a[x.a[i]];
	return z;
}
node operator-(node x)
{
	node y;y.n=x.n;
	for(int i=1;i<=y.n;i++)y.a[x.a[i]]=i;
}
node operator^(node x,int k)
{
	node y;y.n=x.n;
	memset(y.a,-1,sizeof(y.a));
	for(int i=1;i<=y.n;i++)
	{
		if(y.a[i]==-1)
		{
			int j=x.a[i],ring=1;
			while(j!=i)j=x.a[j],ring++;
			int t=k%ring;
			y.a[i]=i;
			while(t--)y.a[i]=x.a[y.a[i]];
			while(x.a[j]!=i)y.a[x.a[j]]=x.a[y.a[j]],j=x.a[j];
		}
	}
}
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	p.n=q.n=n;
	for(int i=1;i<=n;i++)scanf("%d",&p.a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&q.a[i]);
	A=-q;A=A*p;A=A*q;A=A*-p;
	A=A^k/6;
	if(k%6==0)r=p*-q;
	else if(k%6==1)r=p;
	else if(k%6==2)r=q;
	else if(k%6==3)r=-p*q;
	else if(k%6==4)r=-q*-p*q;
	else if(k%6==5)r=-q*p*-q*-p*q;
	ss=A*r*-A;
	for(int i=1;i<n;i++)printf("%d ",ss.a[i]);
	printf("%d\n",ss.a[n]);
	return 0;
}