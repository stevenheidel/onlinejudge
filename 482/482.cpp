#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int N, temp;
	string tempf;
	stringstream ss;

	cin >> N;

	string blank;
	string order;
	vector<int> oa;
	string floats;
	vector<string> fa;

	getline(cin, blank);

	for (int i = 0; i < N; i++) {
		if (i > 0)
			cout << endl;

		getline(cin, blank);
		getline(cin, order);
		getline(cin, floats);

		ss.clear();
		ss << order;
		while (ss >> temp) {
			oa.push_back(temp);
		}

		ss.clear();
		ss << floats;
		while (ss >> tempf) {
			fa.push_back(tempf);
		}

		string* ans = new string[fa.size()];

		for (int j = 0; j < oa.size(); j++) {
			ans[oa[j]-1] = fa[j];	
		}

		for (int j = 0; j < oa.size(); j++) {
			cout << ans[j] << endl;
		}

		oa.clear();
		fa.clear();
	}

	return EXIT_SUCCESS;
}
