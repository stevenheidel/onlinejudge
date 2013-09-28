#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

bool encoded_substring(char* input, char* output) {
	int outcount = 0;

	for (int i = 0; input[i] != '\0'; i++) {
		while (output[outcount] != input[i]) {
			if (output[outcount] == '\0')
				return false;

			outcount++;
		}

		outcount++;
	}

	return true;
}

int main(int argc, char* argv[])  {
	char* input = new char[16000000];
	char* output = new char[16000000];

	while (scanf("%s %s\n", input, output) != EOF)
		if (encoded_substring(input, output))
			printf("Yes\n");
		else
			printf("No\n");

	return EXIT_SUCCESS;
}
