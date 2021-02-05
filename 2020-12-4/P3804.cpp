#include <cstdio>
#include <cstring>
using namespace std;
struct node {
	int son[26], len, fail, cnt;
} tr[2010000];
int trlen;
char a[1010000];
int p[2010000];
int list[2010000];
int main()
{
	scanf("%s", a+1);
	int n=strlen(a+1);
	memset(tr, 0, sizeof(tr) );
	tr[0].fail=-1;
	int last=0;
	trlen=0;
	for(int i=1; i<=n; i++) {
		int c = a[i]-'a';
		tr[last].son[c]=++trlen;
		tr[trlen].len = tr[last].len+1;
		int k=tr[last].fail;
		last=trlen;
		while(k!=-1 && tr[k].son[c]==0) {
			tr[k].son[c]=last;
			k=tr[k].fail;
		}
		if(k==-1) tr[last].fail=0;
		else {
			int p=tr[k].son[c];
			if(tr[k].len+1 < tr[p].len) {
				tr[++trlen]=tr[p];
				tr[trlen].len = tr[k].len+1;
				tr[trlen].cnt=0;
				tr[last].fail=tr[p].fail=trlen;
				while(k!=-1 && tr[k].son[c]==p) {
					tr[k].son[c]=trlen;
					k=tr[k].fail;
				}
			} else tr[last].fail=p;
		}
		tr[last].cnt++;
	}
	memset(p, 0, sizeof(p) );
	for(int i=1; i<=trlen; i++) p[tr[i].fail]++;
	int head=1, tail=1;
	for(int i=1; i<=trlen; i++) {
		if(p[i]==0) list[tail++]=i;
	}
	while(head<tail) {
		int x=list[head];
		if(x==0) break;
		tr[tr[x].fail].cnt+=tr[x].cnt;
		p[tr[x].fail]--;
		if(p[tr[x].fail]==0) list[tail++]=tr[x].fail;
		head++;
	}
	long long ss=0;
	for(int i=1; i<=trlen; i++)
	{
		if(tr[i].cnt>1 && ss < (long long)tr[i].cnt*tr[i].len) ss=(long long)tr[i].cnt*tr[i].len;
	}
	printf("%lld\n", ss);
	return 0;
}