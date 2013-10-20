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

#define DEBUG false

#if DEBUG
#define D(x) cout << #x " is " << x << endl
#define DA(x,n) cout << #x " is...\n";For(i,0,n){cout<<x[i]<<" ";}cout<<endl
#define DAA(x,m,n) cout << #x " is...\n";For(i,0,m){For(j,0,n){cout<<x[i][j]<<" ";}cout<<endl;}
#else
#define D(x)
#define DA(x,n)
#define DAA(x,m,n)
#endif

int N = 100000;
map<int, int> heights;

void addheight(int a, int b, int y) {
	map<int, int>::iterator itlow = heights.lower_bound(a);
	map<int, int>::iterator ithigh = heights.upper_bound(b);

	for (map<int, int>::iterator it = itlow; it != ithigh; ++it) {
		it->second += y;
	}

	int h;
	if (heights.count(a) == 0) {
		itlow--;
		h = itlow->second;
		heights[a] = h + y;
	}

	ithigh = heights.upper_bound(b);

	if (heights.count(b+1) == 0) {
		if (b + 1 < N) {
			ithigh--;
			h = ithigh->second;
			heights[b+1] = h - y;
		}
	}
#if DEBUG
	for (map<int,int>::iterator it = heights.begin(); it != heights.end(); ++it) {
		cout << it->first << ";" << it->second << endl;
	}
#endif
}

int query(int a) {
	map<int, int>::iterator it = heights.upper_bound(a);

	it--;
	return it->second;
}

struct build {
	int start;
	int end;
	int height;
};

vector<build> buildings;
void addheight2(int a, int b, int y) {
	build temp;
	temp.start = a;
	temp.end = b;
	temp.height = y;

	buildings.push_back(temp);
}

int query2(int a) {
	int ans = 0;
	For(i,0,buildings.size()) {
		if (buildings[i].start <= a && buildings[i].end >= a)
			ans += buildings[i].height;
	}
	return ans;
}

int array[100001] = {};
void addheight3(int a, int b, int y) {
	For(i,a,b+1)
		array[i] += y;
}

int query3(int a) {
	return array[a];
}

bool solve(int ignore) {
	buildings.clear();

	heights.clear();
	heights[0] = 0;

	int T;
	cin >> T;

	char c;
	int a, b, y;
	For(i,0,T) {
		cin >> c;

		if (c == 'B') {
			cin >> a >> b >> y;
			addheight3(a-1,b-1,y);
		}
		else if (c == 'Q') {
			cin >> a;
			cout << query3(a-1) << endl;
		}
	}

	return true;
}
 
int main() {
	solve(1);

	return 0;
}
