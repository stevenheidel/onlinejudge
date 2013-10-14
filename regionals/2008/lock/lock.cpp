#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
 
#define Each(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef map<string, int> msi;

#define DEBUG true

#if DEBUG
#define D(x) cout << #x " is " << x << endl
#define DA(x,n) cout << #x ":\n";For(i,0,n){cout<<x[i]<<" "};cout<<endl
#define DAA(x,m,n) cout << #x ":\n";For(i,0,m){For(j,0,n){cout<<x[i][j]<<" "};cout<<endl}
#else
#define D(x)
#define DA(x,n)
#define DAA(x,m,n)
#endif

int N, T1, T2, T3;

int clockwise(int s, int t) {
	return (N+(s-t))%N;
}

int counter(int s, int t) {
	return (N+(t-s))%N;
}

int ticks(int init) {
	return 3*N+clockwise(init, T1)+counter(T1,T2)+clockwise(T2,T3);
}

bool solve(int T) {
	cin >> N >> T1 >> T2 >> T3;
	if (N==0&&T1==0&&T2==0&&T3==0)
		return false;

	double accum=0;
	For(i,0,N)
		accum += (double) ticks(i);

	cout << fixed << setprecision(3) << accum/N << endl;

	return true;
}
 
int main() {
	int N = 1;
	while (solve(N++)) {}
	
	return 0;
}
