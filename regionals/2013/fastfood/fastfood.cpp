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

int contains(vi a, int b) {
	For(i,0,sz(a)) {
		if (a[i] == b) {
			return i;
		}
	}

	return -1;
}

bool solve(int T) {
	int n, m;
	cin >> n >> m;

	vvi prizes(n,vi());
	For(i,0,n) {
		int k;
		cin >> k;
		prizes[i].pb(0);
		For(j,0,k) {
			int t;
			cin >> t;
			prizes[i].pb(t);
		}
		cin >> k;
		prizes[i][0] = k;
	}

	vi have(m,0);
	For(i,0,m) {
		int num;
		cin >> num;
		have[i] = num;
	}

	int ans = 0;
	For(i,0,n) {
		bool again = true;

		For(j,1,sz(prizes[i])) {
			if (have[prizes[i][j]-1] > 0)
				have[prizes[i][j]-1]--;
			else {
				again = false;
				break;
			}
		}

		if (again) {
			ans += prizes[i][0];
			i--;
		}
	}

	cout << ans << endl;

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
