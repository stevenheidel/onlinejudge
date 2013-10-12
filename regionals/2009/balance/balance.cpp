#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
	int NI, NT, NR;
	scanf("%i %i %i", &NI, &NT, &NR);

	double ffees[11], pfees[11], accounts[11], ratios[11];

	for (int i = 0; i < NI; i++) {
		scanf("%lf", &ffees[i]);
	}
	for (int i = 0; i < NI; i++) {
		scanf("%lf", &pfees[i]);
	}
	for (int i = 0; i < NI; i++) {
		scanf("%lf", &accounts[i]);
	}

	double s = 0;
	for (int i = 0; i < NI; i++) {
		s += accounts[i];
	}
	for (int i = 0; i < NI; i++) {
		ratios[i] = accounts[i] / s;
	}

	for (int i = 1; i <= NT; i++) {
		for (int j = 0; j < NI; j++) {
			double ret;
			scanf("%lf", &ret);
			double fee = accounts[j] * pfees[j];
			double rret = accounts[j] * ret;
			accounts[j] = max((accounts[j] - ffees[j] - fee) + rret, 0.0);
		}

		if (i % NR == 0 && i != NT) {
			s = 0;
			for (int ii = 0; ii < NI; ii++) {
				s += accounts[ii];
			}
			for (int j = 0; j < NI; j++) {
				accounts[j] = ratios[j] * s;
			}
		}
	}

	printf("%0.2lf", accounts[0]);
	for (int i = 1; i < NI; i++) {
		printf(" %0.2lf", accounts[i]);
	}
	printf("\n");
}
