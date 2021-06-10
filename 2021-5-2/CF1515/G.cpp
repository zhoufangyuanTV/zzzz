#include<cstdio>
#include<cstring>
using namespace std;
inline int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
struct node
{
	int x,y,c,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	return 0;
}