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

bool opposite(string a, string b) {
	For(i,0,sz(a))
		if (a[i] == '0')
			a[i] = '1';
		else
			a[i] = '0';

	return (a == b);
}

bool solve(int T) {
	int N;
	cin >> N;

	string one;
	string two;
	cin >> one >> two;

	bool valid = false;
	if (N % 2 == 0) {
		if (one == two)
			valid = true;
	}
	else {
		if (opposite(one, two))
			valid = true;
	}

	if (valid)
		cout << "Deletion succeeded" << endl;
	else
		cout << "Deletion failed" << endl;

	return true;
}
 
int main() {
	int N = 1;
	For(i,0,N)
		solve(i+1);
	
	return 0;
}
