#include "hexagon.h"
#include <vector>
namespace {
	using namespace std;
	inline long long S1(long long n)
	{
		return n*(n+1)%1000000007*500000004%1000000007;
	}
	inline long long S2(long long n)
	{
		return (2*n*n%1000000007*n%1000000007 + 3*n*n%1000000007 + n)*166666668%1000000007;
	}
}
int draw_territory(int N, int A, int B, vector<int> D, vector<int> L)
{
	return (A*S1(L[0]+1) + B*(S2(L[0])+S1(L[0]) ) )%1000000007;
}
