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

struct crop {
	int minutes;
	int profit;
};
struct time {
	int start;
	int end;
};

int calls;
bool times[2881];
vector<crop> crops;
int mem[2881];

int plant(int t) {
	calls++;
	if (t > 2880)
		return 0;
	if (mem[t] != -1)
		return mem[t];
	if (!times[t])
		return (mem[t] = plant(t+1));

	int best = 0;
	int next = 0;
	Each(c,crops) {
		if (t + c->minutes - 1 <= 2880) {
			next = plant(t + c->minutes);
			best = max(best, next + c->profit);
		}
	}

	return (mem[t] = best);
}

bool solve(int T) {
	int N, M;
	cin >> N >> M;
	
	int start, end;
	crop x;
	crops.clear();

	For(i,1,2881) {
		times[i] = false;
		mem[i] = -1;
	}

	For(i,0,N) {
		cin >> x.minutes >> x.profit;
		crops.pb(x);
	}
	For(i,0,M) {
		cin >> start >> end;
		For(i,start,end+1)
			times[i] = true;
	}

	calls = 0;
	cout << plant(1) << endl;
	D(calls);

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
