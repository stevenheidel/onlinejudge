#include <iostream>
#include <vector>

using namespace std;
 
typedef vector<int> vi;

bool solve(int T) {
	int N, M;

	cin >> N >> M;

	if (N == 0 && M == 0)
		return false;

	vi factors1, factors2;

	factors1.resize(10);
	factors2.resize(10);
	factors1.assign(0, 10);
	factors2.assign(0, 10);

	int f;
	for (int i = 0; i < N; i++) {
		cin >> f;
		for (int j = 2; j <= f; j++) {
			if (j == 4)
				factors1[2] += 2;
			else if (j == 6) {
				factors1[2] += 1;
				factors1[3] += 1;
			}
			else if (j == 8)
				factors1[2] += 3;
			else if (j == 9)
				factors1[3] += 2;
			else
				factors1[j] += 1;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> f;
		for (int j = 2; j <= f; j++) {
			if (j == 4)
				factors2[2] += 2;
			else if (j == 6) {
				factors2[2] += 1;
				factors2[3] += 1;
			}
			else if (j == 8)
				factors2[2] += 3;
			else if (j == 9)
				factors2[3] += 2;
			else
				factors2[j] += 1;
		}
	}

	bool equal = true;

	for (int i = 2; i <= 9; i++) {
		if (factors1[i] != factors2[i]) {
			equal = false;
			break;
		}
	}

	if (equal)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return true;
}
 
int main() {
	int N = 1;
	while (solve(N++)) {}

	return 0;
}
