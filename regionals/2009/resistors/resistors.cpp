#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct Fraction {
	int num;
	int denom;
};

Fraction process(vector<Fraction> vs, char op);

Fraction readExp() {
	char c;
	while (c = cin.peek(), c == ' ' || c == '\n')
		c = cin.get();

	if (c == '(') {
		c = cin.get();
		vector<Fraction> vs;
		vs.push_back(readExp());
		char op;

		//cerr << vs[0].num << "/" << vs[0].denom << endl;

		while (true) {
			while (c = cin.peek(), c == ' ')
				c = cin.get();

			c = cin.get();
			if (c == ')')
				return process(vs, op);
			else {
				op = c;
				vs.push_back(readExp());
			}
		}
	}
	Fraction ret;
	cin >> ret.num;
	c = cin.get();
	cin >> ret.denom;
	return ret;
}

int gcd(int a, int b) {
	if (b > a)
		return gcd(b, a);
	else if (b == 0)
		return a;
	
	return gcd(b, a%b);
}

Fraction fplus(Fraction f1, Fraction f2) {
	Fraction res;
	res.num = f1.num*f2.denom + f2.num*f1.denom;
	res.denom = f1.denom*f2.denom;

	int g = gcd(res.num, res.denom);

	res.num /= g;
	res.denom /= g;
	
	return res;
}

Fraction reciprical(Fraction f) {
	Fraction f2;
	f2.num = f.denom;
	f2.denom = f.num;
	return f2;
}

Fraction process(vector<Fraction> vs, char op) {
	Fraction accum;
	accum.num = 0;
	accum.denom = 1;

	if (op == '|') {
		for (int i = 0; i < vs.size(); i++) {
			accum = fplus(accum, reciprical(vs[i]));
		}
		
		return reciprical(accum);
	}
	
	for (int i = 0; i < vs.size(); i++)
		accum = fplus(accum, vs[i]);
	
	return accum;
}

int main() {
	char c;
	while (!cin.eof()) {
		Fraction ans = readExp();
		cout << ans.num << "/" << ans.denom << endl;
		
		while (c = cin.peek(), c == ' ' || c == '\n')
			c = cin.get();
	}
}
