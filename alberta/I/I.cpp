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

#define MAXCOST 1000000
typedef int coeff;
typedef vector<vector<coeff> > matrix;

void get_path_h(vvi & path, vi & p, int src, int dst) {
	if (path[src][dst] >= 0) {
		get_path_h(path,p, src, path[src][dst]);
		p.push_back(path[src][dst]);
		get_path_h(path,p, path[src][dst], dst);
	}
}
vi get_path(vvi & path, int src, int dst) {
	vi p;
	p.push_back(src);
	get_path_h(path, p, src, dst);
	p.push_back(dst);
	return p;
}

vvi floyd_warshall(matrix & adj, int n) {
	vvi path; path.resize(n);
	For(i,0,n) {
		path[i].assign(n, -1);
		path[i][i] = i;
	}

	For(k,0,n) {
		For(i,0,n) {
			For(j,0,n) {
				coeff p = adj[i][k] + adj[k][j];

				if (adj[i][k] == MAXCOST || adj[k][j] == MAXCOST)
					continue;

				if (adj[i][j] > p) {
					adj[i][j] = p;
					path[i][j] = k;
				}
			}
		}
	}

	return path;
}

bool solve(int T) {
	int N, M, A, B, F;
	cin >> N >> M;

	matrix dist;

	dist.resize(N);
	For(i,0,N)
		dist[i].resize(N);

	For(i,0,N) {
		For(j,0,N) {
			if (i != j)
				dist[i][j] = MAXCOST;
			else
				dist[i][j] = 0;
		}
	}

	For(i,0,M) {
		cin >> A >> B >> F;
		dist[A-1][B-1] = -1*F;
	}

	vvi path;
	path = floyd_warshall(dist, N);

	DAA(dist,N,N);
	DAA(path,N,N);

	bool foundNeg = false;
	For(i,0,N) {
		if (path[0][i] != -1 && dist[i][i] < 0)
			foundNeg = true;
	}

	int end = 0;
	For(i,0,N)
		end = min(end, dist[0][i]);

	if (foundNeg)
		cout << "Unlimited!" << endl;
	else
		cout << end * -1 << endl;

	return true;
}
 
int main() {
#if DEBUG
	int N = 3;
#else
	int N = 1;
#endif
	while (N--)
		solve(1);
	
	return 0;
}
