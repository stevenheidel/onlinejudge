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
#define For(i, a, b) for (typeof(b) i=(a); i<(b); ++i)
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

string ones[] = {"\\ /", " o ", "   ", "   ", "_o_", "\\o/", "\\o_", "\\o/", "   ", " o "};
string twos[] = {" |  ", "/|\\ ", "    ", "    ", " |  ", " |  ", "\\|  ", "\\|/ ", " __o", "( ) "};
string threes[] = {"/o\\ ", "/ \\ ", "__\\o", "\\_\\o", "/ \\ ", "/ \\ ", " |  ", "    ", "/  |", "/ \\ "};

bool solve(int T) {
	if (T == 0)
		return false;

	int movie[73];
	char c = getchar();
	int i = 0;

	while (c != EOF && c != '\n') {
		movie[i] = (int) (c - '0');
		i++;
		c = getchar();
	}

	string one, two, three;

	for (int j = 0; j < i; j++) {
		if (j != 0) {
			one += " ";
			two += " ";
			three += " ";
		}

		one += ones[movie[j]] + " ";
		two += twos[movie[j]];
		three += threes[movie[j]];
	}

	cout << one << endl;
	cout << two << endl;
	cout << three << endl;
	if (T != 1)
		cout << endl;

	return true;
}
 
int main() {
	int N = 1;
	cin >> N;
	char c = getchar();
	while (solve(N--)) {}
	
	return 0;
}
