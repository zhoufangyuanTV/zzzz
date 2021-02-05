#include<cstdio>
#include<cstring>
using namespace std;
inline char win(char x,char y)
{
	if(x==y||x=='R'&&y=='S'||x=='P'&&y=='R'||x=='S'&&y=='P')return x;
	else return y;
}
char a[210];
int main()
{
	int n,k;
	scanf("%d%d%s",&n,&k,a+1);
	while(k>0)
	{
		for(int i=n+1;i<=n*2;i++)a[i]=a[i-n];
		for(int i=1;i<=n;i++)a[i]=win(a[i*2-1],a[i*2]);
		k--;
	}
	putchar(a[1]);
	return 0;
}