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
typedef set<ll> si;
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

ll n;

ll sibling(ll i) {
	if (i%2==0)
		return i+1;
	else
		return i-1;
}

si siblings(si R) {
	si S;

	ll sib;
	Each(i,R) {
		sib = sibling(*i);
		if (R.count(sib) == 0)
			S.insert(sib);
	}

	return S;
}

si div2(si R) {
	si div;

	Each(i,R) {
		if (div.count(*i/2) == 0)
			div.insert(*i/2);
	}

	return div;
}

bool solve(ll T) {
	ll nR;
	cin >> n >> nR;

	si R;
	R.clear();

	For(i,0,nR) {
		ll temp;
		cin >> temp;
		R.insert(temp);
	}

	si acc;
	acc.clear();
	For(i,0,n) {
		si te = siblings(R);
		if (sz(te) != 0) 
			Each(x,te) {
				acc.insert(*x);
			}

		R = div2(R);
	}

	si::iterator last = acc.end();
	last--;
	for (si::iterator x = acc.begin(); x != acc.end(); ++x) {
		cout << *x;
		if (x != last)
			cout << " ";
	}
	cout << endl;

	return true;
}

int main() {
	int N = 1;
	while (N--)
		solve(N);
	
	return 0;
}
