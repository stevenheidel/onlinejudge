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

int rounda(double d) {
	int i = floor(d);
	double rem = d - i;
	if (rem >= 0.5)
		return i+1;
	else
		return i;
}

ll myround(ll i) {
	ll ret = (i/100);

	if (i%100 >= 50)
		ret += 1;

	return ret;
}

bool solve(int T) {
	double a,b,c;
	cin >> a >> b >> c;
	int R = (int)a*100;
	int B = (int)b*100;
	int M = (int)c*100;

	B *= 10000;
	M *= 10000;

	ll interest = 0ll;
	int success = -1;
	For(i,0,1200) {
		interest = R*(B/100);
		interest = myround(interest);
		B += interest;
		B -= M;
		if (B <= 0)
			success = i;
		else if (interest >= M) {
			success = -1;
			break;
		}
	}

	if (success >= 0)
		cout << success+1 << endl;
	else
		cout << "impossible" << endl;

	return true;
}

ll calc(ll R, ll cents) {
	ll ans = R*cents;
	if (ans % 10000 >= 5000)
		return ans/10000+1;
	else
		return ans/10000;
}

bool solvea(ll T) {
	double R,B,M;
	cin >> R >> B >> M;

	ll iB = (ll)(B*100);
	ll iM = (ll)(M*100);
	ll iR = (ll)(R*100);

	bool paid = false;
	ll i = 0;

	for (i=0; i<1200; i++) {
		ll interest = calc(iR, iB);
		if (interest >= iM)
			break;
		assert(iB < 10000000);
		iB=iB+interest;
		iB=iB-iM;
		if (iB<=0) {
			paid = true;
			break;
		}
	}

	if (paid)
		cout << i+1 << endl;
	else
		cout << "impossible" << endl;

	return true;
}

int main() {
	int N = 1;
	cin >> N;
	For(i,0,N)
		solvea(i+1);
	//while (solve(N++)) {}
	
	return 0;
}
