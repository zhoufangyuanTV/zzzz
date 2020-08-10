#include<set>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LD double
#define LL long long
#define ULL unsigned long long
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)
#define fo(i,j,k) for(int i=j;i<=k;i++)
#define fd(i,j,k) for(int i=j;i>=k;i--)
#define fr(i,j) for(int i=begin[j];i;i=next[i])
//using namespace std;
int const mn=4*1e6+9,mm=8*1e6+9,inf=1e9;LL mo=2333333333333333;
int n,gra,tag,ansp,begin[mn],to[mm],len[mm],num[mm],next[mm];
    LL anss,f[mn][4][2],a[mn][3][2],g[mn],h[mn];
void insert(int u,int v ,int w,int p){
    to[++gra]=v;
    len[gra]=w;
    num[gra]=p;
    next[gra]=begin[u];
    begin[u]=gra;
}
void add(int now,int pos,LL far){
    fd(i,3,1){
        if(f[now][i][0]>far)break;
        f[now][i+1][0]=f[now][i][0];
        f[now][i+1][1]=f[now][i][1];
        f[now][i][0]=far;
        f[now][i][1]=pos;
    }
}
void dfs(int now,int pre){
    fr(i,now)if(to[i]!=pre){
        dfs(to[i],now);
        add(now,to[i],f[to[i]][1][0]+len[i]);
        h[now]=max(h[now],h[to[i]]);
    }
    h[now]=max(h[now],f[now][1][0]+f[now][2][0]);
}
LL get(int now,int tag){
    fo(i,1,3)if(f[now][i][1]!=tag)return f[now][i][0];
}
LL get2(int now,int tag){
    if(f[now][1][1]==tag)return f[now][2][0]+f[now][3][0];
    else if(f[now][2][1]==tag)return f[now][1][0]+f[now][3][0];
    else return f[now][1][0]+f[now][2][0];
}
void addh(int now,int pos,LL far){
    fd(i,2,1){
        if(a[now][i][0]>far)break;
        a[now][i+1][0]=a[now][i][0];
        a[now][i+1][1]=a[now][i][1];
        a[now][i][0]=far;
        a[now][i][1]=pos;
    }
}
LL geth(int now,int tag){
    fo(i,1,2)if(a[now][i][1]!=tag)return a[now][i][0];
}
int P[110],Q[110];
void dfs2(int now,int pre,LL tmx){
    fr(i,now)if(to[i]!=pre)
        addh(now,to[i],h[to[i]]);
    fr(i,now)if(to[i]!=pre){
        LL tmp=get(now,to[i]);
        g[to[i]]=max(tmp,g[now])+len[i];
        tmp=h[to[i]];LL tmp2=get2(now,to[i]),tmp3=get(now,to[i])+g[now];
        tmp2=max(tmp2,tmp3);tmp3=geth(now,to[i]);
        tmp2=max(tmp2,tmp3);
        tmp2=max(tmp2,tmx);
        tmp3=max(tmp,tmp2);LL tmp4=min(tmp,tmp2);
        P[to[i]]=tmp;Q[to[i]]=tmp2;
        anss=(anss+tmp3*23333+tmp4*2333+1ll*233*num[i]*num[i]+23*num[i]+2)%mo;
        dfs2(to[i],now,tmp2);
    }
}
int main(){
    freopen("cheese.in","r",stdin);
    freopen("cheese.ans","w",stdout);
    scanf("%d",&n);int u,v,w;
    fo(i,1,n-1){
        scanf("%d%d%d",&u,&v,&w);
        insert(u,v,w,i);insert(v,u,w,i);
    }
    dfs(1,0);
    dfs2(1,0,0);
    printf("%lld",anss);
	for(int i=2;i<=n;i++)
	{
		printf("%lld %lld\n",P[i],Q[i]);
    }
    return 0;
}