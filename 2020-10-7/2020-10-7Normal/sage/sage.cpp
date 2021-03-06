//C++
#include<cstdio>
#include<cstring>
using namespace std;

namespace IO{
	int c;
	unsigned int seed;
	unsigned int randnum(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}

	inline int read(int &x){scanf("%d",&x);return x;}
	inline void init_case(int &m,int &a,int &b,int &d,int p[]){
		scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
		for(int i=1;i<=m;i++){
			if(randnum()%c==0)p[i]=-1;
			else p[i]=randnum()%b;
		}
	}

	inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
		const static unsigned int mod=998244353;
		ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
	}
}
using IO::read;
using IO::init_case;
using IO::update_ans;
/*
一开始请调用read(T)读入数据组数T
接下来每组数据开始时请调用init_case(m,a,b,d,p)读入m,a,b,d,p[]
每组数据开始时请用一个初始化为0的32位无符号整形变量ans_sum存储答案，然后对于每个i，
用32位无符号整形变量cur_ans存储第i次答案，并调用update_ans(ans_sum,cur_ans,i)更新。最后输出ans_sum即可。
*/

//示例代码：

bool bk[2010000],v[2010000];
int q[1010000],h,t;
int list[1010000];
inline int mymin(int x,int y){return x<y?x:y;}
int main(){
	freopen("sage.in","r",stdin);
	freopen("sage.out","w",stdout);
	static int p[2000005];
	int T;read(T);
	int m,a,b,d;
	while(T--){
		unsigned int ans_sum=0,cur_ans=0;
		init_case(m,a,b,d,p);
		memset(bk,false,sizeof(bk));
		memset(v,false,sizeof(v));
		for(int i=0;i<=a;i++)bk[i]=v[i]=true;
		h=1;t=0;
		int head=1,tail=0,lj=a+1;
		for(int i=1;i<=m;i++){
			bool k=false;
			if(p[i]==-1)
			{
				if(h<=t&&d==0)
				{
					k=true;
					int x=q[h++];
					v[x]=true;
					if(head<=tail&&list[head]==x)head++;
				}
			}
			else
			{
				if(!bk[p[i]])
				{
					k=true;
					bk[p[i]]=v[p[i]]=true;
					while(bk[lj])lj++;
				}
				else if(v[p[i]]&&d==0)
				{
					k=true;
					v[p[i]]=false;
					q[++t]=p[i];
					while(head<=tail&&p[i]<list[tail])tail--;
					list[++tail]=p[i];
				}
				else if(h<=t&&d==0)
				{
					k=true;
					int x=q[h++];
					v[x]=true;
					if(head<=tail&&list[head]==x)head++;
				}
			}
			cur_ans=k?mymin(head<=tail?list[head]:lj,lj):0;
			update_ans(ans_sum,cur_ans,i);
		}
		printf("%u\n",ans_sum);
	}
	return 0;
}
