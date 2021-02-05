#include <cstdio>
#include <cstring>
using namespace std;
struct node {
	int son[26], len, fail, dep;
} tr[510000];
int trlen;
char a[510000];
int main()
{
	memset(tr, 0, sizeof(tr) );
	tr[0].fail=1;
	tr[1].len=-1;
	tr[1].fail=1;
	trlen=1;
	int last=1;
	int lastans=0;
	bool bk=false;
	for(int i=1; (a[i]=getchar() )!=EOF; i++) {
		if(a[i]<'a' || a[i]>'z') break;
		a[i] = (a[i]-97+lastans)%26 + 97;
		while(a[i-tr[last].len-1]!=a[i]) last=tr[last].fail;
		int c = a[i]-'a';
		if(tr[last].son[c]==0) {
			tr[last].son[c]=++trlen;
			tr[trlen].len = tr[last].len+2;
			if(last==1) tr[trlen].fail=0;
			else {
				int k=tr[last].fail;
				while(a[i-tr[k].len-1]!=a[i]) k=tr[k].fail;
				tr[trlen].fail=tr[k].son[c];
			}
			tr[trlen].dep = tr[tr[trlen].fail].dep+1;
		}
		last=tr[last].son[c];
		if(bk) putchar(' ');
		else bk=true;
		printf("%d", lastans=tr[last].dep);
	}
	putchar('\n');
	return 0;
}