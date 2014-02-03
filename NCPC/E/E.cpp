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
#define For(i, a, b) for (int i=(a); i<(b); ++i)
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

bool solve(int T) {
	string a, b;

	cin >> a >> b;

	int ans = sz(b);
	For(i,0,sz(a)) {
		if (i >= sz(b))
			break;

		if (a[i] == b[i])
			ans--;
		else
			break;
	}

	if (ans > 0) {
		int j = sz(b)-1;
		for (int i = sz(a)-1; i >= 0; i--) {
			if (j < 0 )
				break;

			if (a[i] == b[j])
				ans--;
			else
				break;

			j--;
		}
	}

	cout << ans << endl;

	return true;
}
 
int main() {
	int N = 2;
	For(i,0,N)
		solve(i+1);
	
	return 0;
}
