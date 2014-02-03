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

int n;

int numconnected(vvi GG) {
	int ret = 0;
	vector<vector<bool> > marked(n,vector<bool>(n,false));
	queue<ii> open;
	open.push(mp(0,0));

	while (!open.empty()) {
		ret += 1;
		int x = open.front().first;
		int y = open.front().second;
		open.pop();

		marked[x][y] = true;

		if (x+1<n && !marked[x+1][y] && GG[0][0] == GG[x+1][y])
			open.push(mp(x+1,y));
		if (x-1>=0 && !marked[x-1][y] && GG[0][0] == GG[x-1][y])
			open.push(mp(x-1,y));
		if (y+1<n && !marked[x][y+1] && GG[0][0] == GG[x][y+1])
			open.push(mp(x,y+1));
		if (y-1>=0 && !marked[x][y-1] && GG[0][0] == GG[x][y-1])
			open.push(mp(x,y-1));
	}

	return ret;
}

vvi floodfill(vvi GG, int color) {
	vvi ret = GG;
	vector<vector<bool> > marked(n,vector<bool>(n,false));
	queue<ii> open;
	open.push(mp(0,0));

	while (!open.empty()) {
		int x = open.front().first;
		int y = open.front().second;
		ret[x][y] = color;
		open.pop();

		marked[x][y] = true;

		if (x+1<n && !marked[x+1][y] && GG[0][0] == GG[x+1][y])
			open.push(mp(x+1,y));
		if (x-1>=0 && !marked[x-1][y] && GG[0][0] == GG[x-1][y])
			open.push(mp(x-1,y));
		if (y+1<n && !marked[x][y+1] && GG[0][0] == GG[x][y+1])
			open.push(mp(x,y+1));
		if (y-1>=0 && !marked[x][y-1] && GG[0][0] == GG[x][y-1])
			open.push(mp(x,y-1));
	}

	return ret;
}

int bestcolor(vvi GG) {
	vvi potentials[6];

	For(color,0,6)
		potentials[color] = floodfill(GG,color);

	int best = 0;
	int max = numconnected(potentials[best]);
	For(i,1,6) {
		int cur = numconnected(potentials[i]);
		if (cur > max) {
			best = i;
			max = cur;
		}
	}

	D(best);
	return best;
}

bool solve(int T) {
	cin >> n;
	vvi G(n, vi(n,0));
	vi ret(6,0);
	For(i,0,n)
		For(j,0,n) {
			char c;
			cin >> c;
			G[i][j] = c-'0'-1;
		}

	while(true) {
		bool same = true;
		int color = G[0][0];
		For(i,0,n) {
			For(j,0,n) {
				if (G[i][j] != color) {
					same = false;
					break;
				}
			}
			if (!same)
				break;
		}

		if (T==1) {
		DAA(G,sz(G),sz(G[0]));
		}
		if (same)
			break;
	
		int thebestcolor = bestcolor(G);
		G = floodfill(G,thebestcolor);
		ret[thebestcolor]++;
	}

	int sum = 0;
	For(i,0,6)
		sum += ret[i];
	cout << sum << endl;
	For(i,0,6)
		cout << ret[i] << " ";
	cout << endl;

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
