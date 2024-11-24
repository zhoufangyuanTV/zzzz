#include<cstdio>
using namespace std;
int main()
{
    int t;scanf("%d",&t);
    while(t--)
    {
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++)printf("%d%c",i*2-1,i==n?'\n':' ');
    }
    return 0;
}