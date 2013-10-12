#include <cstdio>
#include <cstdlib>
#include <cmath>

int main() {
	double po = 0.0;
	double pw = 0.0;
	double o,w;

	double oc = 0.0;
	double wc = 0.0;

	while (scanf("%lf %lf", &o, &w), o != -1.0 && w != -1.0) {
		if (o == 0.0 && w == 0.0) {
			printf("%.0lf\n", oc * pw / wc);

			oc = 0.0;
			wc = 0.0;
		}
		else if (pw > w) {
			wc += pw - w;
			oc += o - po;
		}

		po = o;
		pw = w;
	}
}
