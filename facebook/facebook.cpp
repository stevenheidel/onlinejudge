#include <stdio.h>

int balanced(int stave[], int length, int b1, int b2) {
	int sum = 0;
	int multiplier = 1;

	int weights[4];
	for (int i = 0; i < 4; i++)
		weights[i] = 0;

	for (int i = 0; i < length; i++) {
		sum += stave[b1 + i];

		weights[0] += stave[b1 + i] * multiplier;
		weights[1] += stave[b1 + length - i - 1] * multiplier;

		multiplier++;
	}
	for (int i = 0; i < length; i++) {
		sum += stave[b2 + i];

		weights[2] += stave[b2 + i] * multiplier;
		weights[3] += stave[b2 + length - i - 1] * multiplier;

		multiplier++;
	}
	
	int s, t;
	s = weights[0];
	t = weights[1];
	weights[0] += weights[2];
	weights[1] += weights[3];
	weights[2] += t;
	weights[3] += s;

	for (int i = 0; i < 4; i++) {
		weights[i] *= 2;

		if (((weights[i] % sum) == 0) && ((weights[i] / sum) == (length * 2) + 1))
			return 1;
	}

	return 0;
}

int main() {
	char c;

	int stave[500];
	int size;

	for (size = 0; size < 500; size++) {
		c = getchar();

		if (c == EOF || c == '\n')
			break;
		
		stave[size] = c - '0';
	}

	for (int i = size / 2; i > 0; i--) {
		for (int j = 0; j <= size - 2 * i; j++) {
			for (int k = i + j; k <= size - i; k++) {
				if (balanced(stave, i, j, k)) {
					printf("%i %i %i\n", j, k, i);
					return 0;
				}
			}
		}
	}

	return 1;
}
