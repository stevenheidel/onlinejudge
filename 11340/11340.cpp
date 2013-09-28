#include <stdio.h>
#include <stdlib.h>

int main() {
	int N, temp;

	temp = scanf("%i", &N);

	for (int n = 0; n < N; n++) {
		int K;

		temp = scanf("%i", &K);

		int v[256];

		for (int i = 0; i < 256; i++) {
			v[i] = 0;
		}
		
		char idx;

		for (int k = 0; k < K; k++) {
			temp = scanf("\n%c ", &idx);
			temp = scanf("%i", &v[idx]);
		}

		int M;

		temp = scanf("%i", &M);

		char c = getchar();
		int sum = 0;
		for (int m = 0; m < M; m++) 
			do {
				c = getchar();
				sum += v[c];
			}
			while (c != '\n' && c != EOF);

		printf("%i.%02i$\n", sum/100, sum%100);
	}

	return EXIT_SUCCESS;
}
