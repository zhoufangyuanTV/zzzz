#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll P=1000000007;
 
int n,m,t;
ll p;
ll ine[100010],jc[100010],jcc[100010],p1[100010],p2[100010];
ll fr[2][1510],fl[2][1510],sr[2][1510],sl[2][1510],gl[2][1510],gr[2][1510],sc[1510],c[1510];
inline ll pm(ll x,ll y)
{
    ll z=1;
    while(y)
    {
        if(y&1) z=z*x%P;
        x=x*x%P,y>>=1;
    }
    return z;
}
inline ll C(int a,int b)
{
    if(a<b)  return 0;
    return jc[a]*jcc[b]%P*jcc[a-b]%P;
}
inline ll calc(int a)
{
    return C(t,a)*p1[a]%P*p2[t-a]%P;
}
 
int main()
{
    ll a,b;
    int i,j,d=0;
    scanf("%d%d%lld%lld%d",&n,&m,&a,&b,&t),p=a*pm(b,P-2)%P;
    ine[0]=ine[1]=jc[0]=jc[1]=jcc[0]=jcc[1]=1;
    for(i=2;i<=t;i++)    ine[i]=P-(P/i)*ine[P%i]%P,jc[i]=jc[i-1]*i%P,jcc[i]=jcc[i-1]*ine[i]%P;
    for(p1[0]=p2[0]=i=1;i<=t;i++)    p1[i]=p1[i-1]*p%P,p2[i]=p2[i-1]*(1-p)%P;
    for(i=0;i<=m;i++)    c[i]=calc(i);
    for(i=1;i<=m;i++)
        for(j=1;j<=i;j++)    a=c[j-1]*c[m-i]%P,fr[0][i]=(fr[0][i]+a)%P,fl[0][j]=(fl[0][j]+a)%P;
    for(i=1;i<=m;i++)    sr[0][i]=(sr[0][i-1]+fr[0][i])%P;
    for(i=m;i>=1;i--)    sl[0][i]=(sl[0][i+1]+fl[0][i])%P;
    for(i=1;i<=m;i++)    gr[0][i]=(gr[0][i-1]+sr[0][i]*c[i])%P;
    for(i=m;i>=1;i--)    gl[0][i]=(gl[0][i+1]+sl[0][i]*c[m-i+1])%P;
    for(i=0;i<=m;i++)    sc[i]=(sc[i-1]+c[i])%P;
    for(i=2;i<=n;i++)
    {
        d^=1;
        memset(fl[d],0,sizeof(fl[d])),memset(fr[d],0,sizeof(fr[d]));
        memset(sl[d],0,sizeof(sl[d])),memset(sr[d],0,sizeof(sr[d]));
        for(j=1;j<=m;j++)
        {
            fr[d][j]=c[m-j]*((sr[d^1][m]-sl[d^1][j+1])*sc[j-1]%P-gr[d^1][j-1])%P;
            fl[d][j]=c[j-1]*((sr[d^1][m]-sr[d^1][j-1])*sc[m-j]%P-gl[d^1][j+1])%P;
        }
        for(j=1;j<=m;j++)    sr[d][j]=(sr[d][j-1]+fr[d][j])%P;
        for(j=m;j>=1;j--)    sl[d][j]=(sl[d][j+1]+fl[d][j])%P;
        for(j=1;j<=m;j++)    gr[d][j]=(gr[d][j-1]+sr[d][j]*c[j])%P;
        for(j=m;j>=1;j--)    gl[d][j]=(gl[d][j+1]+sl[d][j]*c[m-j+1])%P;
    }
    printf("%lld",(sr[d][m]+P)%P);
    return 0;
}