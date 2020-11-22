#include<cstdio>
#include<cstring>
using namespace std;
long long f[4][1100];
int g[4];
char s[110];
int main()
{
    int n;scanf("%d",&n);
    scanf("%s",s+1);
    g[0]=s[1]-'A';
    scanf("%s",s+1);
    g[1]=s[1]-'A';
    scanf("%s",s+1);
    g[2]=s[1]-'A';
    scanf("%s",s+1);
    g[3]=s[1]-'A';
    f[0][0]=f[1][0]=f[2][0]=f[3][0]=1;
    f[0][1]=f[1][1]=f[2][1]=f[3][1]=1;
    for(int i=2;i<=n;i++)
    {
        int x=g[0],y=g[0]<<1;
        f[0][i]=0;
        for(int j=0;j<i;j++)
        {
            f[0][i]=(f[0][i]+f[x][j]*f[y][i-j-1])%1000000007;
        }
        x=g[1],y=g[1]<<1|1;
        f[1][i]=0;
        for(int j=0;j<i;j++)
        {
            f[1][i]=(f[1][i]+f[x][j]*f[y][i-j-1])%1000000007;
        }
        x=2|g[2],y=g[2]<<1;
        f[2][i]=0;
        for(int j=0;j<i;j++)
        {
            f[2][i]=(f[2][i]+f[x][j]*f[y][i-j-1])%1000000007;
        }
        x=2|g[3],y=g[3]<<1|1;
        f[3][i]=0;
        for(int j=0;j<i;j++)
        {
            f[3][i]=(f[3][i]+f[x][j]*f[y][i-j-1])%1000000007;
        }
    }
    printf("%lld\n",f[1][n-2]);
    return 0;
}