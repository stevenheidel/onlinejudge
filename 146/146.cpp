#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	string s;

	while (true) {
		cin >> s;

		if (s.compare("#") == 0)
			break;

		if (next_permutation(s.begin(), s.end()))
			cout << s << endl;
		else
			cout << "No Successor" << endl;
	}

	return EXIT_SUCCESS;
}
