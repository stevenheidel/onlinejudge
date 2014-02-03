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

int convert(vvi stars, int off) {
	int start = off * 4;
	string rep;

	For(i,0,5)
	For(j,start,start+3) {
		if (stars[i][j])
			rep += "*";
		else
			rep += " ";
	}

	string reps[] = {
"**** ** ** ****",
"  *  *  *  *  *",
"***  *****  ***",
"***  ****  ****",
"* ** ****  *  *",
"****  ***  ****",
"****  **** ****",
"***  *  *  *  *",
"**** ***** ****",
"**** ****  *  *"};

	For(i,0,10)
		if (reps[i] == rep)
			return i;

	return 0;
}

bool solve(int T) {
	vvi stars(5, vi());

	char c;
	int i = 0;
	while (i < 5) {
		c = getchar();

		if (c == '\n')
			i++;
		else if (c == '*')
			stars[i].pb(1);
		else
			stars[i].pb(0);
	}

	int count = (stars[0].size()+1)/4;

	vi ans;
	For(j,0,count) {
		ans.pb(convert(stars, j));
	}

	ll num = 0;
	count--;
	Each(x,ans) {
		num += ((ll)*x) * pow(10,count--);
	}

	if (num % 6 == 0)
		cout << "BEER!!" << endl;
	else
		cout << "BOOM!!" << endl;

	return true;
}
 
int main() {
	int N = 1;
	For(i,0,N)
		solve(i+1);
	
	return 0;
}
