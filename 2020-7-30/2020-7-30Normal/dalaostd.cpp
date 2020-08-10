#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<map>
#define Rint register int
#define Lint long long int
using namespace std;
const int INF=0x3f3f3f3f;
const int N=6010;
struct node
{
    int d,f;
    bool operator < (const node &a) const
    {
        return f<a.f;
    }
}p[N*220];
int a[N],w[N],c[N],q[N*220],F[N*220],L[N*220];
int n,m,mc,mx,D,cnt;
int f[N][N];
map<int,map<int,int> > d;
void bfs()
{
    int h=0,t=1;
    F[t]=1,L[t]=0,d[1][0]=q[t]=1;//赋初值，F为讽刺能力，L为等级
    while( h<t )
    {
        h++;
        int tmp=d[F[h]][L[h]];
        if( tmp>=D )   continue ;
        int x=F[h],y=L[h];
        if( !d[x][y+1] )
        {
            F[++t]=x,L[t]=y+1;
            d[x][y+1]=q[t]=tmp+1;
        }
        if( (Lint)x*(Lint)y<=1ll*mx && !d[x*y][y] )
        {
            F[++t]=x*y,L[t]=y;
            d[x*y][y]=q[t]=tmp+1;
        }
    }
    printf("%d\n",t);
    p[++cnt]=(node){ 0,0 };
    for(int i=1;i<=t;i++)   p[++cnt]=(node){ q[i],F[i] };
    sort( p+1,p+cnt+1 );
}
bool judge(int x)
{
    int j=1,v=INF;
    for(int i=cnt; i ;i--)
    {
        while( p[i].f+p[j].f<=x && i>j )   v=min( v,p[j].d-p[j].f ),j++;
        if( D-x>=v+p[i].d-p[i].f )   return 1;
    }
    return 0;
}
int main()
{
    /*freopen("dalao.in","r",stdin);
    freopen("dalao.out","w",stdout);*/
    scanf("%d%d%d",&n,&m,&mc);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&w[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&c[i]);
        mx=max( mx,c[i] );
    }
    memset( f,-1,sizeof f );
    f[0][mc]=0;
    for(int i=1,x;i<=n;i++)
        for(int j=a[i];j<=mc;j++)
        {
            f[i][j-a[i]]=max( f[i][j-a[i]],f[i-1][j]+1 );
            x=min( mc,j-a[i]+w[i] );
            f[i][x]=max( f[i][x],f[i-1][j] );
        }
    for(int i=0;i<=n;i++)   for(int j=0;j<=mc;j++)  
            if(f[i][j]==7)
            {
                printf("%d %d\n",i,j);
            }// D=max( D,f[i][j] );
    /*mx=100000000;
    bfs();
    for(int i=1;i<=m;i++)
        if( judge( c[i] ) )   printf("1\n");
        else   printf("0\n");*/
    return 0;
}