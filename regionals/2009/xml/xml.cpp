#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool isAlphaNum(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z')))
			return false;
	}

	return true;
}

bool valid(string s, int n) {
	for (int i = 0; i < n; i++) {
		if (s[i] < 32 || s[i] > 127)
			return false;
	}

	for (int i = 0; i < n; i++) {
		bool possible = false;

		if (s[i] == '&') {
			string sub3 = s.substr(i, 4);
			string sub4 = s.substr(i, 5);

			if (sub3 == "&lt;" || sub3 == "&gt;")
				possible = true;
			if (sub4 == "&amp;")
				possible = true;

			if (s[i+1] == 'x') {
				possible = true;
				for (int j = i+2; j < n; j++) {
					if (j > i+2 && s[j] == ';')
						break;
					if (j == n-1)
						return false;
					if ((s[j] >= '0' && s[j] <= '9') || (s[j] >= 'a' && s[j] <= 'f') || (s[j] >= 'A' && s[j] <= 'F'))
						possible = !possible;
					else
						return false;
				}
			}
		}
		else {
			possible = true;
		}
		
		if (!possible)
			return false;
	}

	int pos = -1;
	stack<string> ss;
	while (pos = s.find('<', pos+1), pos != -1) {
		if (pos == s.length()-1)
			return false;

		int pos2 = s.find('>', pos+1);
		if (pos2 == -1)
			return false;

		if (s[pos2-1] == '/') {
			string temp = s.substr(pos+1, pos2-pos-2);

			if (!isAlphaNum(temp))
				return false;
		}
		else if (s[pos+1] == '/') {
			if (ss.size() == 0)
				return false;

			string temp = s.substr(pos+2, pos2-pos-2);

			if (!isAlphaNum(temp))
				return false;

			if (temp != ss.top())
				return false;
			ss.pop();
		}
		else {
			string temp = s.substr(pos+1, pos2-pos-1);

			if (!isAlphaNum(temp))
				return false;

			ss.push(temp);
		}
	}
	if (ss.size() > 0)
		return false;

	int bc = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '<')
			bc++;
		if (s[i] == '>')
			bc--;
	}
	if (bc != 0)
		return false;

	return true;
}

int main() {
	string s;
	while (getline(cin, s), !cin.eof()) {
		if (!valid(s, s.length())) {
			printf("in");
		}
		printf("valid\n");
	}
}
