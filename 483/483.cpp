#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

stack<char> print_stack(stack<char> s) {
	while (!s.empty()) {
		putchar(s.top());
		s.pop();
	}

	return s;
}

int main() {
	char c;
	stack<char> s;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n') {
			s = print_stack(s);
			putchar(c);
		}
		else {
			s.push(c);
		}
	}

	return EXIT_SUCCESS;
}
