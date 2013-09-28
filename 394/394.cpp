#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct array_t {
	char name[11];
	int base;
	int bytes;
	int dimensions;
	int* lower_bounds;
	int* upper_bounds;
} array;

int find_array(char* name, array* arrays, int size) {
	for (int i = 0; i < size; i++)
		if (strcmp(arrays[i].name, name) == 0)
			return i;

	return 0;
}

void output_answer(array arr, int dims[]) {
	printf("%s[", arr.name);
	for (int i = 0; i < arr.dimensions-1; i++) {
		printf("%i, ", dims[i]);
	}
	printf("%i] = ", dims[arr.dimensions-1]);

	int* C = new int[arr.dimensions + 1];

	C[arr.dimensions] = arr.bytes;

	for (int i = arr.dimensions - 1; i > 0; i--) {
		C[i] = C[i+1] * (arr.upper_bounds[i] - arr.lower_bounds[i] + 1);
	}

	C[0] = arr.base;

	for (int i = 1; i <= arr.dimensions; i++) {
		C[0] -= C[i] * arr.lower_bounds[i-1];
	}

	int sum = C[0];

	for (int i = 1; i <= arr.dimensions; i++) {
		sum += C[i] * dims[i-1];
	}

	printf("%i\n", sum);

	return;
}

int main() {
	int temp;
	int N, R;

	temp = scanf("%i %i", &N, &R);

	array* arrays = new array[N];

	for (int i = 0; i < N; i++) {
		temp = scanf("%s %i %i %i", arrays[i].name, &arrays[i].base, &arrays[i].bytes, &arrays[i].dimensions); 

		arrays[i].lower_bounds = new int[arrays[i].dimensions];
		arrays[i].upper_bounds = new int[arrays[i].dimensions];

		for (int j = 0; j < arrays[i].dimensions; j++) {
			temp = scanf("%i %i", &arrays[i].lower_bounds[j], &arrays[i].upper_bounds[j]);
		}
	}

	char current_string[11];
	int current_index;
	int current_dimensions[10];

	for (int i = 0; i < R; i++) {
		temp = scanf("%s", current_string);

		current_index = find_array(current_string, arrays, N);

		for (int j = 0; j < arrays[current_index].dimensions; j++) {
			temp = scanf("%i", &current_dimensions[j]);
		}

		output_answer(arrays[current_index], current_dimensions);
	}
	
	return EXIT_SUCCESS;
}
