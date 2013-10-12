#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

double w, h, d;
int workers;
double area;
double pos;
int wall;

double base(double aarea) {
	if (wall == 1)
		return 2.0*aarea/d;
	if (wall == 2)
		return 2.0*aarea/h;
	if (wall == 3)
		return 2.0*aarea/(w-d);

	return -1.0;
}

double curArea(double bbase) {
	if (wall == 1)
		return bbase * d / 2.0;
	if (wall == 2)
		return bbase * h / 2.0;
	if (wall == 3)
		return bbase * (w-d) / 2.0;

	return -1.0;
}

double maxdim() {
	if (wall == 2)
		return w;
	else
		return h;

	return -1.0;
}

void printloc(int i) {
	double m, n;
	if (i != 0)
		printf(" ");
	if (wall == 1)
		m = w, n = pos;
	if (wall == 2)
		m = w-pos, n = h;
	if (wall == 3)
		m = 0.0, n = h-pos;

	cout << fixed << setprecision(3) << m << " " << n;
}

int main() {
	while (scanf("%lf %lf %lf %i", &w, &h, &d, &workers), w != 0 && h != 0 && d != 0 && workers != 0) {
		d = w-d;
		area = w * h / ((double) workers);
		pos = 0.0;
		wall = 1;

		//printf("w: %f, h: %f, workers: %i\n", w, h, workers);
		//printf("area: %f\n", area);

		for (int i = 0; i < workers-1; i++) {
			double b = base(area);

			if (pos + b <= maxdim()) {
				pos = pos + b;
				printloc(i);
			}
			else {
				double a = curArea(maxdim() - pos);

				wall++;
				pos = base(area - a);
				printloc(i);
			}
		}

		printf("\n");
	}
}
