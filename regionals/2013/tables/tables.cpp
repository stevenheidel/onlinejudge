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

vector<vector<pair<int, int> > > ans;
int m;
int width;

bool peq(ii a, ii b) {
	return a.first == b.first && a.second == b.second;
}

void print_sep(int r) {
	if (r == 0) {
		For(i,0,width)
			cout << " --";
	}
	else if (r == m) {
		For(i,0,width)
			cout << " --";
	}
	else {
		For(i,0,width) {
			if (!peq(ans[r-1][i], ans[r][i])) {
				cout << " --";
			}
			else {
				bool end = true;
				For(j,i+1,width) {
					if (!peq(ans[r-1][j], ans[r][j])) {
						end = false;
					}
				}
				if (!end) {
					cout << "   ";
				}
				else {
					break;
				}
			}
		}
	}
	cout << endl;
}


void print_row(int r) {
	cout << "|";
	For(i,0,width) {
		bool above = false;
		bool left = false;
		bool right = false;

		if (r > 0)
			above = peq(ans[r-1][i], ans[r][i]);
		if (i > 0)
			left = peq(ans[r][i-1], ans[r][i]);
		if (i < width-1)
			right = peq(ans[r][i+1], ans[r][i]);

		if (above || left)
			cout << "  ";
		else
			cout << ans[r][i].first << ans[r][i].second;

		if (i<width-1) {
			if (!right)
				cout << "|";
			else
				cout << " ";
		}
	}
	cout << "|" << endl;
}

bool solve(int T) {
	cin >> m;
	if (m == 0)
		return false;
	if (T != 1)
		cout << endl;
	vvi rows(m,vi(0,0));

	int n = 0;
	For(i,0,m) {
		cin >> n;
		For(j,0,n) {
			int temp;
			cin >> temp;
			rows[i].pb(temp);
			cin >> temp;
			rows[i].pb(temp);
		}
	}

	width = 0;
	For(i,0,sz(rows[0])/2)
		width += rows[0][i*2+1];

	ans.clear();
	ans = vector<vector<pair<int, int> > >(m, vii(width, mp(0,0)));

	For(i,0,m) {
		For(j,0,sz(rows[i])/2) {
			int h = rows[i][j*2];
			int w = rows[i][j*2+1];

			For(m,0,h) {
				For(n,0,w) {
					while (ans[i+m][j+n].first != 0) {
						j++;
					}
					if (j+n < width)
						ans[i+m][j+n] = mp(i+1,j+1);
				}
			}
		}
	}

	For(i,0,m) {
		print_sep(i);
		print_row(i);
	}
	print_sep(m);

	return true;
}

int main() {
	int N = 1;
	while (solve(N++)) {}
	
	return 0;
}
