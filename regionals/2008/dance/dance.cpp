#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
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

vector<string> steps;
string capital_dips;

bool rule1() {
	capital_dips = "";
	bool valid = true;

	For(i,0,steps.size()) {
		if (i>0)
			capital_dips += " ";

		if (steps[i] == "dip") {
			bool good = false;

			if (i>0 && steps[i-1] == "jiggle")
				good = true;
			if (i>1 && steps[i-2] == "jiggle")
				good = true;
			if (i<steps.size()-1 && steps[i+1] == "twirl")
				good = true;

			if (good)
				capital_dips += "dip";
			else {
				valid = false;
				capital_dips += "DIP";
			}
		}
		else {
			capital_dips += steps[i];
		}
		
	}

	return valid;
}

bool rule2() {
	int l = steps.size()-1;

	if (steps.size() < 3)
		return false;

	if (steps[l-2] == "clap" && steps[l-1] == "stomp" && steps[l] == "clap")
		return true;

	return false;
}

bool rule3() {
	bool twirl = false;
	bool hop = false;

	For(i,0,steps.size()) {
		if (steps[i] == "twirl")
			twirl = true;
		if (steps[i] == "hop")
			hop = true;
	}

	return ((!twirl) || (twirl && hop));
}

bool rule4() {
	return (steps[0] != "jiggle");
}

bool rule5() {
	bool dip = false;

	For(i,0,steps.size()) {
		if (steps[i] == "dip") {
			dip = true;
		}
	}

	return dip;
}

bool solve(int T) {
	string s;
	getline(cin, s);

	if (cin.eof())
		return false;

	istringstream iss(s);

	steps.clear();

	string temp;
	while (iss >> temp)
		steps.push_back(temp);

	vi errors;
	if (!rule1())
		errors.push_back(1);
	if (!rule2())
		errors.push_back(2);
	if (!rule3())
		errors.push_back(3);
	if (!rule4())
		errors.push_back(4);
	if (!rule5())
		errors.push_back(5);

	if (errors.size() == 0)
		cout << "form ok: " << s << endl;
	else {
		if (errors.size() == 1) {
			cout << "form error " << errors[0] << ": ";
		}
		if (errors.size() >= 2) {
			cout << "form errors ";

			For(i,0,errors.size()) {
				if (i == errors.size()-1)
					cout << errors[i] << ": ";
				if (i == errors.size()-2)
					cout << errors[i] << " and ";
				if (i < errors.size()-2)
					cout << errors[i] << ", ";
			}

		}

		
		cout << capital_dips << endl;
	}

	return true;
}
 
int main() {
	int N = 1;
	while (solve(N++)) {}
	
	return 0;
}
