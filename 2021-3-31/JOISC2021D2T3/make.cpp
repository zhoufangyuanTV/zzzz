#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int p[1010000];
inline int ra(){return rand()<<15|rand();}
int main()
{
	freopen("sample.txt","w",stdout);
	int n=1000000;
	/*for(int i=1;i<=1000000;i++)p[i]=1000001-i;*/
	for(int i=1;i<=500000;i++)p[i]=i*2;
	for(int i=500001;i<=1000000;i++)p[i]=(1000000-i)*2+1;
	srand(time(0));
	int l=ra()%n,r=ra()%n;
	if(l>r)swap(l,r);
	int t=300000;
	while(t--)
	{
		int tl=l+rand()%(r-l+1)+1,tr=l+rand()%(r-l+1)+1;
		if(tl!=tr)swap(p[tl],p[tr]);
	}
	printf("%d %d %d\n",n,l,r);
	for(int i=1;i<n;i++)printf("%d ",p[i]);
	printf("%d\n",p[n]);
	return 0;
}