#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
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

//typedef long long ll;
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

bool solve(int T) {
	int cal, F, C, P;
	cin >> cal >> F >> C >> P;
	if (cal==0&&F==0&&C==0&&P==0)
		return false;

	int diff = (cal - 9*F - 4*C - 4*P);
	bool yes = true;

	if (diff >= 0)
		yes = diff < 8.5;
	else {
		if (F != 0)
			F = 9;
		if (C != 0)
			C = 4;
		if (P != 0)
			P = 4;

		yes = abs(diff) < (F+C+P)/2.0;
	}

	if (yes)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	return true;
}
 
int main() {
	int N = 1;
	while (solve(N++)) {}
	
	return EXIT_SUCCESS;
}
