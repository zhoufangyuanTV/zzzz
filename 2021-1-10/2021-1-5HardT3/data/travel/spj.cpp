#include "testlib_for_lemons.h"
#include <bits/stdc++.h>

using namespace std;

/*
 * inf - input file
 * ouf - output file
 * ans - standard answer
 */

int main(int argc, char **argv) {
    registerLemonChecker(argc, argv);

    string test1 = ouf.readString(),test2=ans.readString();
	
	if(test1!=test2){quitf(_wa,"Wrong answer!");return 0;}
	
	int n=inf.readInt(),limA=inf.readInt(),limB=inf.readInt(),tp=inf.readInt();
	int cntA=ouf.readInt(),cntB=ouf.readInt();
	
	if(tp==1){
//		quitf(_ok,"Accept!");
		quitf(_ok,"Accept! Your answer is %d and %d.\n",cntA,cntB);
		return 0;
	}
    if(tp==2){
		double a=30,b;
		if(cntA<=16000) a=30;
		else{
			double c=max(0.0,(cntA-16000)*1.0/2800)+1;
			b=1+log(c)*1.0/log(2);
			a=30.0/b;
		}
		if(cntA<=16000) quitf(_ok,"Accept! Your answer is %d and %d.\n",cntA,cntB);
		else quitp(a,"Your answer is %d and %d.\n",cntA,cntB);
		return 0;
	}
	if(tp==3){
		double a=1;
		if(cntA<=9300) a=1;
		else if(cntA<=14000) a=1.9-cntA*1.0/10000;
		else a=1-cntA*1.0/28000;
		if(cntA<=9300) quitf(_ok,"Accept! Your answer is %d and %d.\n",cntA,cntB);
		else quitp(40.0*a,"Your answer is %d and %d.\n",cntA,cntB);
		return 0;
	}
	return 0;
}
