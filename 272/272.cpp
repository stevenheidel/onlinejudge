#include <stdlib.h>
#include <stdio.h>

int main() {
	bool open = true;

	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == '"')
			if (open) {
				putchar('`');
				putchar('`');
				open = false;
			}
			else {
				putchar('\'');
				putchar('\'');
				open = true;
			}
		else
			putchar(c);
	}

	return EXIT_SUCCESS;
}
