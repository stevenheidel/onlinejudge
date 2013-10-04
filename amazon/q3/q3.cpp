#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

vector<int> intersection(vector<int> a, vector<int> b) {
	sort(a.begin(), a.end());
 	sort(b.begin(), b.end());

	vector<int> result(min(a.size(), b.size()));
	
	vector<int>::iterator it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), result.begin());

	result.resize(it - result.begin());

	return result;
}

int main() {
	vector<int> a, b;
	
	a.push_back(4);
	a.push_back(2);
	a.push_back(73);
	a.push_back(11);
	a.push_back(-5);

	b.push_back(-5);
	b.push_back(73);
	b.push_back(-1);
	b.push_back(9);
	b.push_back(9);
	b.push_back(4);
	b.push_back(7);

	vector<int> c = intersection(a, b);

	for (vector<int>::const_iterator it = c.begin(); it != c.end(); ++it) {
		cout << *it << endl;
	}

	return EXIT_SUCCESS;
}
