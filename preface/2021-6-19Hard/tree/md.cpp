#include<bits\stdc++.h>
#define fo(x,a,b) for(int x=(a),e_=(b);x<=e_;x++)
#define fd(x,a,b) for(int x=(a),e_=(b);x>=e_;x--)
#define ww printf

using namespace std;
typedef long long ll;
const int N=4;

int ran(int n){
	return rand()%n+1;
}	
int main(){
	freopen("tree.in","w",stdout);
	srand(time(NULL));
	int n=N;
	printf("%d %d\n",n,2*N);
	fo(i,2,N) printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%10);
	fo(i,1,2*N){
		if(rand()&1) {
			int x,y;
			do{
				x=ran(n), y=ran(n);
			}while(x==y);
			printf("1 %d %d %d\n",x,y,ran(10));
		} else {
			int L=ran(n), R=ran(n);
			if(L>R) swap(L,R);
			int k=ran(n);
			static int a[N+10];
			fo(j,1,n) a[j]=j;
			random_shuffle(a+1,a+n+1);
			printf("2 %d %d %d ",L,R,k);
			fo(j,1,k) printf("%d ",a[j]);puts("");
		}
	}
	return 0;
}