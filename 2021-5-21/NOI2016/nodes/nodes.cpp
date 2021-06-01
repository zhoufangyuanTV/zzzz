#include<cstdio>
#include<cstring>
using namespace std;
int a[110],b[110],c[110];
int main()
{
	freopen("nodes6.out","w",stdout);
	int len=0;
	len++;puts("I");
	int lst=1;
	for(unsigned i=31;i>=1;i--)
	{
		len++;printf("C %d -%u.5\n",lst,(1u<<i)-1);
		len++;printf("< %d 1500\n",len-1);
		len++;printf("S %d\n",len-1);
		len++;printf("O %d\n",len-1);
	    len++;printf("< %d %u\n",len-1,i);
		len++;printf("- %d\n",len-1);
		len++;printf("+ %d %d\n",lst,len-1);
		lst=len;
	}
	printf("O %d\n",lst);
	return 0;
}
