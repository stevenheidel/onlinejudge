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

double average(int array[], int start, int end) {
	double count = end - start;
	double sum = 0;

	for (int i = start; i < end; i++) {
		sum += array[i];
	}

	return sum / count;
}

int wins[3][3];

bool beats(int i, int j) {
	return wins[i][j] > wins[j][i];
}

bool solve(int T) {
	char c;
	cin >> c;

	int dice[3][6];

	For(i,0,3)
		For(j,0,3)
			wins[i][j] = 0;

	For(i,0,3)
		For(j,0,6)
			cin >> dice[i][j];

	For(i,0,3)
	For(j,0,3)
	For(k,0,6)
	For(l,0,6) {
		if (dice[i][k] > dice[j][l])
			wins[i][j]++;
		else if (dice[i][k] < dice[j][l])
			wins[j][i]++;
	}

	if ((beats(0,1) && beats(0,2)) || (beats(1,0) && beats(1,2)) || (beats(2,0) && beats(2,1)))
		cout << c << endl;
	else if ((beats(1,0) || beats(2,0)) && (beats(0,1) || beats(2,1)) && (beats(0,2) || beats(1,2)))
		if (c == 'A')
			cout << 'B' << endl;
		else
			cout << 'A' << endl;
	else
		cout << "fair" << endl;

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
