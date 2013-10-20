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
 
#define Each(x, v) for (typeof((v).begin()) x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (typeof(b) i=(a); i<(b); ++i)
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) ((int)(a.size()))

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<int> si;
typedef map<string, int> msi;

#define DEBUG true

#if DEBUG
#define D(x) cout << #x " is " << x << endl
#define DA(x,n) cout << #x " is...\n";For(i,0,n){cout<<x[i]<<" ";}cout<<endl
#define DAA(x,m,n) cout << #x " is...\n";For(i,0,m){For(j,0,n){cout<<x[i][j]<<" ";}cout<<endl;}
#else
#define D(x)
#define DA(x,n)
#define DAA(x,m,n)
#endif

bool adj(ii p, ii q) {
	return (p.second == q.first-1) || (q.second == q.first-1);
}

ii merge(ii p, ii q) {
	if (p.first < q.first)
		return mp(p.first, q.second);
	return mp(q.first, p.second);
}

bool solve(int T) {
	int N;

	cin >> N;

	vii columns;
	columns.resize(N);

	int temp;
	For(i,0,N) {
		cin >> temp;
		columns[i] = mp(temp, temp);
	}

	bool changed = true;

	while (changed) {
		changed = false;
		vii newpairs;

		ii curRange = columns[0];

		For(i,0,columns.size()) {
			if (adj(curRange, columns[i])) {
				curRange = merge(curRange, columns[i]);
				changed = true;
			}
			else {
				newpairs.pb(curRange);
			}
		}

		columns = newpairs;
	}

	if (columns.size() == 1)
		cout << "yes" << endl;
		else 
			cout << "no" << endl;

	return true;
}
 
int main() {
	int N = 1;
	cin >> N;
	For(i,0,N)
		solve(i+1);
	//while (solve(N++)) {}
	
	return 0;
}
