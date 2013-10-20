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

typedef int Coord;
const Coord MINCOORD = -999;

struct Pt {
	Coord x, y;
	static bool coordOrder(Pt p1, Pt p2) {
		if (p1.y == p2.y)
			return (p1.x < p2.x);
		return (p1.y < p2.y);
	}
	static Coord crossProduct(Pt p1, Pt p2, Pt p3) {
		return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
	}
	Pt(Coord _x, Coord _y) : x(_x), y(_y) {};
};

void printList(list<Pt> pts) {
	for (list<Pt>::iterator i = pts.begin(); i != pts.end(); ++i) {
		cout << "(" << i->x << "," << i->y << ")\n";
	}
}

static Pt pp = Pt(MINCOORD, MINCOORD);
static Coord length(Pt p) {
	return (((pp.x - p.x) * (pp.x - p.x)) + ((pp.y - p.y) * (pp.y - p.y)));
}

static bool angleOrder(Pt p2, Pt p3) {
	Coord xp = Pt::crossProduct(pp, p2, p3);
	if (0 == xp) return (length(p2) < length(p3));
	return (0 < xp);
}

list<Pt> CCWPoly(list<Pt> pts) {
	list<Pt> ccw;
	pts.sort(ptr_fun(& Pt::coordOrder));

	while (!pts.empty()) {
		pp = pts.front();
		ccw.push_back(pp);
		pts.pop_front();
		pts.sort(ptr_fun(& angleOrder));
	}

	return ccw;
}

list<Pt> Graham(list<Pt> pts) {
	list<Pt> hull;

	pts.sort(ptr_fun(& Pt::coordOrder));
	pp = *(pts.begin());
	pts.sort(ptr_fun(& angleOrder));

	list<Pt>::iterator i = pts.begin();
	hull.push_back(*i++);
	hull.push_back(*i++);
	for (; i != pts.end(); i++) {
		do {
			Pt p = hull.back();
			hull.pop_back();
			if (0 < Pt::crossProduct(hull.back(), p, *i)) {
				hull.push_back(p);
				break;
			}
		} while (1 < hull.size());

		hull.push_back(*i);
	}

	Pt p = hull.back();
	hull.pop_back();
	if (0 < Pt::crossProduct(hull.back(), p, hull.front())) {
		hull.push_back(p);
	}
	return hull;
}

bool solve(int T) {
	int N;
	cin >> N;

	list<Pt> pts;

	int x, y;
	For(i,0,N) {
		cin >> x >> y;
		pts.push_back(Pt(x,y));
	}

	printList(pts);

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
