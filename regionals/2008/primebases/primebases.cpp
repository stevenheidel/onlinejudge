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
#define DA(x,n) cout << #x ":\n";For(i,0,n){cout<<x[i]<<" ";};cout<<endl
#define DAA(x,m,n) cout << #x ":\n";For(i,0,m){For(j,0,n){cout<<x[i][j]<<" ";};cout<<endl}
#else
#define D(x)
#define DA(x,n)
#define DAA(x,m,n)
#endif

const int N = 10;
int primes[N] = {2,3,5,7,11,13,17,19,23,29};
ll products[N];

void init() {
	ll accum = 1;

	For(i,0,N) {
		accum *= primes[i];
		products[i] = accum;
	}

	return;
}

bool solve(int T) {
	int n;
	cin >> n;
	if (n == 0)
		return false;

	vi a;
	a.assign(N, 0);

	cout << n << " = ";

	for (int i = N-1; i >= 0; i--) {
		a[i] = n / products[i];
		n = n % products[i];
	}

	bool first = true;

	if (n == 1) {
		cout << "1";
		first = false;
	}

	For(i,0,N) {
		if (a[i] != 0) {
			if (first)
				first = false;
			else
				cout << " + ";

			cout << a[i];

			For(j,0,i+1)
				cout << "*" << primes[j];
		}
	}

	cout << endl;

	return true;
}
 
int main() {
	init();
	int N = 1;
	while (solve(N++)) {}
	
	return 0;
}
