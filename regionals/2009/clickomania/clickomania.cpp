#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

bool solvable[151][151];

bool answer(string s, int n) {
	for (int i = 0; i < 151; i++)
		for (int j = 0; j < 151; j++)
			solvable[i][j] = false;

	for (int i = 0; i <= n; i++)
		solvable[i][i] = true;

	for (int k = 2; k <= n; k++) {
		for (int i = 0; i <= n-k; i++) {
			int j = i + k;
			bool solve = false;

			for (int p = i+1; p <= j-2; p++) {
				if (solvable[i][p] && solvable[p][j]) {
					solve = true; break;
				}
				if (s[i] == s[j-1] && s[i] == s[p]) {
					if (solvable[i+1][p] && solvable[p+1][j-1]) {
						solve = true; break;
					}
				}
			}

			if (s[i] == s[j-1])
				if (solvable[i+1][j-1])
					solve = true;

			solvable[i][j] = solve;
		}
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			//printf("%i ", solvable[i][j]);
		}
		//printf("\n");
	}

	return solvable[0][n];
}

int main() {
	string s;
	while (getline(cin, s), !cin.eof()) {
		if (answer(s, s.length()))
			cout << "solvable" << endl;
		else
			cout << "unsolvable" << endl;
	}
}
