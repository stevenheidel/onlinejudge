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

const double EPS = 1e-10;

typedef vector<int> VI;
typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

T GaussJordan(VVT &a, VVT &b) {
	const int n = a.size();
	const int m = b[0].size();
	VI irow(n), icol(n), ipiv(n);
	T det = 1;

	For(i,0,n) {
		int pj = -1, pk = -1;
		For(j,0,n) if (!ipiv[j])
			For(k,0,n) if (!ipiv[k])
				if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) {
					pj = j;
					pk = k;
				}

		if (fabs(a[pj][pk]) < EPS) {
			//cerr << "Matrix is singular." << endl;
			return 0.0;
		}

		ipiv[pk]++;
		swap(a[pj], a[pk]);
		swap(b[pj], b[pk]);
		if (pj!=pk) det *= -1;
		irow[i] = pj;
		icol[i] = pk;

		T c = 1.0 / a[pk][pk];
		det *= a[pk][pk];

		a[pk][pk] = 1.0;

		For(p,0,n) a[pk][p] *= c;
		For(p,0,m) b[pk][p] *= c;
		For(p,0,n) if (p != pk) {
				c = a[p][pk];
				a[p][pk] = 0;
				For(q,0,n) a[p][q] -= a[pk][q] * c;
				For(q,0,m) b[p][q] -= b[pk][q] * c;
		}
	}

	for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
		For(k,0,n) swap(a[k][irow[p]], a[k][icol[p]]);
	}

	return det;
}

bool solve(int ignore) {
	int N;
	cin >> N;

	vi A(N,0);
	For(i,0,N) {
		cin >> A[i];
	}

	if (A[1] % A[0] == 0) {
		int ratio = A[1] / A[0];

		bool good = true;

		For(i,1,N) {
			if (A[i-1] * ratio != A[i]) {
				good = false;
				break;
			}
		}

		if (good) {
			cout << ratio * A[N-1] << endl;
			return true;
		}
	}

	vector<vector<double> > B(2,vector<double>(2,0));
	vector<vector<double> > C(2,vector<double>(1,0));

	B[0][0] = A[1];
	B[0][1] = A[0];
	B[1][0] = A[2];
	B[1][1] = A[1];

	C[0][0] = A[2];
	C[1][0] = A[3];

	double det = GaussJordan(B, C);

	if (fabs(det) > EPS) {
		bool good = true;

		For(i,2,N) {
			if (fabs(A[i-1]*C[0][0]+A[i-2]*C[1][0]-A[i]) > EPS) {
				good = false;
				break;
			}
		}

		if (good) {
			cout << round(A[N-1]*C[0][0] + A[N-2]*C[1][0]) << endl;
			return true;
		}
	}
	
	B = vector<vector<double> >(3,vector<double>(3,0));
	C = vector<vector<double> >(3,vector<double>(1,0));

	B[0][0] = A[2];
	B[0][1] = A[1];
	B[0][2] = A[0];
	B[1][0] = A[3];
	B[1][1] = A[2];
	B[1][2] = A[1];
	B[2][0] = A[4];
	B[2][1] = A[3];
	B[2][2] = A[2];

	C[0][0] = A[3];
	C[1][0] = A[4];
	C[2][0] = A[5];

	det = GaussJordan(B,C);
	assert(fabs(det) > EPS);

	double next = A[N-1]*C[0][0]+A[N-2]*C[1][0]+A[N-3]*C[2][0];
	cout << round(next) << endl;

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
