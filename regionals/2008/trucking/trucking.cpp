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

//Graph templates
typedef pair<int,int> weight;
typedef pair<weight,ii> edge;
typedef vector<edge> ve;
typedef vector<weight> vw;
edge make_edge(int u, int v, weight w) { 
	return make_pair(w, make_pair(u,v));
}
#define pb(i) push_back(i)

typedef vector<vector<edge> > wgraph;
vw d;
int hmax;

pair<int, int> wplus(weight w1, weight w2) {
	return make_pair(max(w1.first, w2.first), w1.second+w2.second);
}

bool wgreater(weight w1, weight w2) {
	if (w1.first <= hmax && w2.first <= hmax)
		return (w1.second > w2.second);

	if (w1.first > w2.first)
		return true;
	else if (w1.first == w2.first)
		return (w1.second > w2.second);
	return false;
}

void init_ss(int V, int source) {
	d.clear();
	d.assign(V, make_pair(INT_MAX, INT_MAX));
	d[source] = make_pair(0,0);

	return;
}

void relax(edge e) {
	int u = e.second.first;
	int v = e.second.second;

	weight w = e.first;
	weight r = wplus(w, d[u]);

	if (hmax != INT_MIN && w.first > hmax)
		return;

	if (wgreater(d[v],r))
		d[v] = r;

	return;
}

void dijkstra(wgraph & G, int source) {
	init_ss(G.size(), source);
	set<pair<weight, int> > Q;
	vector<bool> done;
	done.resize(G.size());
	
	For(i,0,G.size()) {
		done[i] = false;
		Q.insert(make_pair(d[i],i));
	}

	while (!Q.empty()) {
		int u = Q.begin()->second;
		Q.erase(Q.begin());
		done[u] = true;

		For(i,0,G[u].size()) {
			edge e = G[u][i];
			int v = e.second.second;
			if (!done[v]) {
				Q.erase(make_pair(d[v],v));
				relax(e);
				Q.insert(make_pair(d[v],v));
			}
		}
	}
}

bool solve(int T) {
	hmax = INT_MIN;
	int C, R;
	cin >> C >> R;
	if (C==0&&R==0)
		return false;

	if (T != 1)
		cout << endl;
	cout << "Case " << T << ":" << endl;

	wgraph G;
	For(i,0,C)
		G.pb(vector<edge>());

	int c1, c2, h, l;
	For(i,0,R) {
		cin >> c1 >> c2 >> h >> l;
		weight w = make_pair(h,l);
		edge e = make_edge(c1-1,c2-1,w);
		G[c1-1].pb(e);
		e = make_edge(c2-1,c1-1,w);
		G[c2-1].pb(e);
	}

	int s,t,hlim;
	cin >> s >> t >> hlim;

	For(i,0,G.size()) {
		For(j,0,G[i].size()) {
			h = G[i][j].first.first;
			if ((h == -1) || (h >= hlim))
				h = 0;
			else
				h = hlim - h;

			G[i][j].first.first = h;
		}
	}

	dijkstra(G,s-1);
	hmax = d[t-1].first;
	dijkstra(G,s-1);

	weight ans = d[t-1];

	if (ans.first == INT_MAX)
		cout << "cannot reach destination" << endl;
	else {
		h = hlim - ans.first;
		cout << "maximum height = " << h << endl;
		cout << "length of shortest route = " << ans.second << endl;
	}

	return true;
}
 
int main() {
	int N = 1;
	while (solve(N++)) {}
	
	return 0;
}
