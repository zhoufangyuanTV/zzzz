#include<cstdio>
#include<algorithm>
#include<cassert>
#define fo(x,a,b) for(int x=(a),e_=(b);x<=e_;x++)
#define fd(x,a,b) for(int x=(a),e_=(b);x>=e_;x--)
#define ww printf

using namespace std;
typedef long long ll;
const int N=300005;
int in[N],out[N],T[N],bg[N],sz[N],D[N],hd[N],go[N],nx[N],len[N],fa[N];
int n,m,cnt,tl,L,R,s[N];
ll w[N],ans;

void In(int& a){
	a=0;char c=getchar();for(;c<48||c>57;c=getchar());
	for(;c>47&&c<58;c=getchar()) a=(a<<1)+(a<<3)+c-48;
}
#define Go(i) for(int i=hd[x]; i; i=nx[i]) if(go[i]!=fa)


namespace G{
#define ade(x,y,z) (go[++tl]=y, nx[tl]=hd[x], hd[x]=tl, len[tl]=z)
	int q[N],L[N],R[N],lg[N],f[20][N],inx;
	void dfs(int x,int fa){
		L[x]=++inx, q[inx]=x, sz[x]=1, D[x]=D[fa]+1;
		::fa[x]=fa;
		Go(i) {
			w[go[i]]=len[i];
			dfs(go[i], x), q[++inx]=x;
			if(sz[go[i]]>sz[bg[x]]) bg[x]=go[i];
			sz[x]+=sz[go[i]];
		}
		R[x]=++inx, q[inx]=x;
	}
	void init(){
		int x,y,z;
		In(n), In(m);
		fo(i,1,n-1) In(x), In(y), In(z), ade(x,y,z), ade(y,x,z);
		dfs(1,0);
		lg[0]=-1; fo(i,1,inx) lg[i]=lg[i>>1]+1;
		fo(i,1,inx) f[0][i]=L[q[i]];
		fo(j,1,19) {
			fo(i,1,inx) if(i+(1<<j)-1>inx) break;
			else f[j][i]=min(f[j-1][i], f[j-1][i+(1<<(j-1))]);
		}
	}
	inline int Q(int x,int y){
		int l=min(L[x],L[y]), r=max(R[x],R[y]), v=lg[r-l+1];
		return q[min(f[v][l], f[v][r-(1<<v)+1])];
	}
} using G::Q;

void opt(int x,int y,ll& v,int o,int L,int R){
	int g=Q(x,y);
	ll ans=0, js=0;
	for(; x!=g; x=fa[x]) {
		if(o==1) ans+=w[x], ++js;
		else w[x]+=v;
	}
	for(; y!=g; y=fa[y]) {
		if(o==1) ans+=w[y], ++js;
		else w[y]+=v;
	}
	if(o==1 && L<=js && js<=R) v+=ans;
}

int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.ans","w",stdout);
	int o,k;
	ll vk;
	G::init();

	fo(ti,1,m) {
		In(o), In(L), In(R), In(k);
		vk=k;
		if(o==1) {
			opt(L,R,vk,0,0,0);
			continue;
		} 
		s[0]=k; fo(i,1,k) In(s[i]);
		ans=0;
		fo(i,1,k) 
			fo(j,i+1,k) opt(s[i],s[j],ans,1,L,R);
		printf("%lld\n",ans);
	}
	return 0;
}
