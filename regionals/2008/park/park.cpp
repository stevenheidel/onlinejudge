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
 
#define Each(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef map<string, int> msi;

#define DEBUG true

#if DEBUG
#define D(x) cout << #x " is " << x << endl
#define DA(x,n) cout << #x ":\n";For(i,0,n){cout<<x[i]<<" ";};cout<<endl
#define DAA(x,m,n) cout << #x ":\n";For(i,0,m){For(j,0,n){cout<<x[i][j]<<" ";};cout<<endl}
#else
#define D(x)
#define DA(x,n)
#define DAA(x,m,n)
#endif

struct tree {
	int x;
	int y;
	int id;
};

bool xfirst(tree t1, tree t2) {
	if (t1.x == t2.x)
		return t1.y < t2.y;

	return t1.x < t2.x;
}

bool yfirst(tree t1, tree t2) {
	if (t1.y == t2.y)
		return t1.x < t2.x;

	return t1.y < t2.y;
}

bool ffind(pair<int, int> interval, vi nums) {
	int tlow = interval.first;
	int tup = interval.second;

	int l = lower_bound(nums.begin(), nums.end(), tlow) - nums.begin();
	int u = lower_bound(nums.begin(), nums.end(), tup) - nums.begin();

	return (l != u);
}

bool solve(int T) {
	int NTREES, NPATHS;
	cin >> NTREES >> NPATHS;

	vector<tree> trees;
	trees.resize(NTREES);

	For(i,0,NTREES){
		cin >> trees[i].x >> trees[i].y;
		trees[i].id = i;
	}

	vi xpaths;
	vi ypaths;
	char c;
	int x;

	For(i,0,NPATHS){
		cin >> c;
		if (c == 'x') {
			cin >> c >> x;
			xpaths.push_back(x);
		}
		else if (c == 'y') {
			cin >> c >> x;
			ypaths.push_back(x);
		}
	}
	
	vector<tree> treesx (trees);
	vector<tree> treesy (trees);
	sort(treesx.begin(), treesx.end(), xfirst);
	sort(treesy.begin(), treesy.end(), yfirst);

	sort(xpaths.begin(), xpaths.end());
	sort(ypaths.begin(), ypaths.end());

	bool visible[100001];
	memset(visible, false, NTREES);
	
	// top and bottom
	For(i,0,NTREES) {
		tree t,t2;

		t = treesx[i];
		int upper = INT_MAX;
		int lower = INT_MIN;
		if (i+1 < NTREES) {
			t2 = treesx[i+1];
			if (t.x == t2.x)
				upper = t2.y;
		}
		if (i > 0) {
			t2 = treesx[i-1];
			if (t.x == t2.x)
				lower = t2.y;
		}
		if (ffind(make_pair(t.y, upper), ypaths)) {
			visible[t.id] = true;
		}
		if (ffind(make_pair(lower, t.y), ypaths)) {
			visible[t.id] = true;
		}
	}
	// left and right
	For(i,0,NTREES) {
		tree t,t2;

		t = treesy[i];
		int upper = INT_MAX;
		int lower = INT_MIN;
		if (i+1 < NTREES) {
			t2 = treesy[i+1];
			if (t.y == t2.y)
				upper = t2.x;
		}
		if (i > 0) {
			t2 = treesy[i-1];
			if (t.y == t2.y)
				lower = t2.x;
		}
		if (ffind(make_pair(t.x, upper), xpaths))
			visible[t.id] = true;
		if (ffind(make_pair(lower, t.x), xpaths))
			visible[t.id] = true;
	}

	int ans = 0;
	For(i,0,NTREES)
		if (visible[i])
			ans++;

	cout << ans << endl;

	return false;
}
 
int main() {
	int N = 1;
	while (solve(N++)) {}
	
	return 0;
}
