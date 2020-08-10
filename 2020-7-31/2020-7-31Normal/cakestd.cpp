#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#define ll long long
using namespace std;
const ll maxn=4e6;
ll bz[maxn+5],p[maxn+5],d[maxn],p1[maxn+5],p2[maxn+5],c[maxn+5];
ll n,m,i,t,j,k,l,x,y,z,ans,mo;
map<ll,ll>h,h1,h2;
ll make(ll n){
    ll t=n+1,k=2*n+1;
    if (n%2) t/=2;
    else n/=2;
    if (n%3==0) n/=3;
    else if (t%3==0) t/=3;
    else if (k%3==0) k/=3;
    return n*t%mo*k%mo;
}
ll sqr(ll x){
    return x*x%mo;
}
ll dg(ll n){
    if (n<=maxn) return p[n];
    if (h[n]) return h[n];
    ll y=n*(n+1)/2%mo,i=2,t;
    while (i<=n){
        t=n/(n/i);
        y-=(t-i+1)*dg(n/i)%mo;i=t+1;
    }
    y%=mo;y=(y+mo)%mo;h[n]=y;
    return y;
}
ll dg1(ll n){
    if (n<=maxn) return p1[n];
    if (h1[n]) return h1[n];
    ll y=make(n),i=2,t;
    while (i<=n){
        t=n/(n/i);
        y-=(t+i)*(t-i+1)/2%mo*dg1(n/i)%mo;i=t+1;
    }
    y%=mo;y=(y+mo)%mo;h1[n]=y;
    return y;
}
ll dg2(ll n){
    if (n<=maxn) return p2[n];
    if (h2[n]) return h2[n];
    ll y=sqr(n*(n+1)/2%mo),i=2,t;
    while (i<=n){
        t=n/(n/i);
        y-=(make(t)-make(i-1)+mo)%mo*dg2(n/i)%mo;i=t+1;
    }
    y%=mo;y=(y+mo)%mo;h2[n]=y;
    return y;
}
int main(){
    freopen("cake.in","r",stdin);freopen("cake.out","w",stdout);
    scanf("%lld%lld",&n,&mo);p[1]=1;
    for (i=2;i<=maxn;i++){
        if (!bz[i]) d[++d[0]]=i,p[i]=i-1;
        for (j=1;j<=d[0];j++){
            if (i*d[j]>maxn) break;
            bz[i*d[j]]=1;
            if (i%d[j]==0){
                p[i*d[j]]=p[i]*d[j];break;
            }else p[i*d[j]]=p[i]*p[d[j]];
        }
    }
    for (i=1;i<=maxn;i++)
        p1[i]=i*p[i]%mo,p2[i]=p1[i]*i%mo,p[i]=(p[i]+p[i-1])%mo,p1[i]=(p1[i]+p1[i-1])%mo,
        p2[i]=(p2[i]+p2[i-1])%mo;
    long long s=dg(n),ss=dg1(n),sss=dg2(n);
    ans=n*n%mo*4%mo*s%mo;
    t=6*n%mo*ss%mo;
    k=2*sss%mo;
    ans=(ans+k-t+mo)%mo;
    printf("%lld\n%lld\n%lld\n%lld\n",s,ss,sss,ans);
}