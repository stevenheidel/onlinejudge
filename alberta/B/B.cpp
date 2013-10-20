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
#define DV(x) cout << #x " is " << x << endl
#define DA(x,n) cout << #x " is...\n";For(i,0,n){cout<<x[i]<<" ";}cout<<endl
#define DAA(x,m,n) cout << #x " is...\n";For(i,0,m){For(j,0,n){cout<<x[i][j]<<" ";}cout<<endl;}
#else
#define D(x)
#define DA(x,n)
#define DAA(x,m,n)
#endif

int N, K, D;

int dist(int i, int j) {
	return min((i-j+N)%N, (j-i+N)%N);
}

vvi matrixMult(vvi A, vvi B, int p, int q, int r) {
	vvi C;
	C.resize(p);
	For(i,0,p)
		C[i].resize(r);

	For(i,0,p)
	For(j,0,r)
	C[i][j] = 0;

	For(i,0,p)
	For(j,0,r)
	For(k,0,q) {
		C[i][j] = (C[i][j] + (A[i][k] % N) * (B[k][j] % N)) % N;
	}

	return C;
}

vvi fastExp(vvi M, int k) {
	if (k == 1)
		return M;
	if (k % 2 == 1)
		return matrixMult(M, fastExp(M, k-1), N, N, N);

	vvi temp = fastExp(M, k/2);

	return matrixMult(temp, temp, N, N, N);
}

bool solve(int T) {
	cin >> N >> K >> D;

	vvi init;
	init.resize(N);

	For(i,0,N) {
		init[i].resize(1);
		cin >> init[i][0];
	}

	vvi matrix;
	matrix.resize(N);
	For(i,0,N)
		matrix[i].resize(N);

	For(i,0,N)
		For(j,0,N)
			if (dist(i,j) >= 1 && dist(i,j) <= D)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;

	DAA(matrix,N,N);
	vvi MK = fastExp(matrix, K);

	DAA(MK,N,N);

	vvi result = matrixMult(MK, init, N, N, 1);

	DAA(result,N,1);

	int highest = INT_MAX;

	For(i,0,N)
		highest = min(result[i][0], highest);

	cout << highest << endl;
	
	vi players;
	For(i,0,N)
		if (result[i][0] == highest)
			players.push_back(i+1);

	for (size_t i = 0; i < players.size(); i++) {
		if (i != 0)
			cout << " ";
		cout << players[i];
	}
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
