#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

const long long int M = 1000000007;
int T, C;
int P[16];
int A[16];
int accum;

int powmod(int b, int e) {
	if (e == 0)
		return 1;
	if (e % 2 == 0) {
		int p = powmod(b, e / 2);
		return (p * p) % M;
	}
	
	return (b * powmod(b, e-1)) % M;
}

void calc(int idx, int a, int b, bool equal) {
	if (idx < 0) {
		accum += a + b;
		accum %= M;
		printf("%i %i\n", a, b);
		return;
	}

	int ap, bp;
	for (int i = 0; i <= A[idx]; i++) {
		ap = a * powmod(P[idx], i);
		bp = b * powmod(P[idx], A[idx]);
		calc(idx-1, ap, bp, i==A[idx]&&equal);
		if (!equal && ap != bp)
			calc(idx-1, bp, ap, false);
	}
}

int main() {
	scanf("%i", &T);
	int num = 1;
	while (T--) {
		scanf("%i", &C);

		for (int i = 0; i < C; i++) {
			scanf("%i %i", &P[i], &A[i]);
		}

		accum = 0;

		calc(C-1,1,1,true);

		printf("Case %i: %i\n", num++, accum);
	}
}
