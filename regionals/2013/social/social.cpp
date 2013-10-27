#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
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

#define Each(x,v) for (typeof((v).begin()) x=(v).begin(); x != (v).end(); ++x)
#define For(i,a,b) for (int i=(a); i<(b); ++i)
#define mp make_pair
#define pb push_back
#define all(a) a.begin() a.end()
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

vi bestsofar;
int n;
vvi G;

bool covers(vi S);

void minCover(vi S, int max) {
	if (covers(S) && sz(S) < sz(bestsofar)) {
		bestsofar = S;
	}
	else if (max == n || sz(S) > sz(bestsofar))
		return;
	else {
		S.pb(max);
		minCover(S,max+1);
		S.pop_back();
		minCover(S,max+1);
	}
}

bool covers(vi S) {
	vector<bool> marked(n,false);

	Each(x,S) {
		For(j,0,sz(G[*x])) {
			marked[*x] = true;
			marked[G[*x][j]] = true;
		}
	}

	bool ans = true;
	For(i,0,n) {
		if (!marked[i])
			ans = false;
	}

	return ans;
}

bool solve(int T) {
	cin >> n;
	G = vvi(n,vi(0));

	For(i,0,n) {
		int d;
		cin >> d;
		int frien;
		For(j,0,d) {
			cin >> frien;
			G[i].pb(frien-1);
		}
	}

	bestsofar.clear();
	For(i,0,n)
		bestsofar.pb(i);

	minCover(vi(),0);
	//cout << "OUTPUT!!!" << endl;
	cout << sz(bestsofar) << endl;

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
