#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <iostream>
#include <limits.h>

using namespace std;

int main() {
	int n;
	long unsigned int m;

	while (scanf("%i", &n) != EOF) {
		printf("%i converts to ", n);

		bitset<32> b (n);
		bitset<32> l;

		for (int i = 0; i < 4; i++) 
			for (int j = 0; j < 8; j++) 
				if (b.test(i*8 + j))
					l.set((4-i-1)*8 + j);

		m = l.to_ulong();

		if (l.test(31)) {
			l.set(31, false);
			m = l.to_ulong();
			m = INT_MAX - m + 1;	
			printf("-");
		}

		printf("%lu\n", m);
	}	

	return EXIT_SUCCESS;
}
