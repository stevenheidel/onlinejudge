#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_CARS = 1000;

int N1, N2;
int t1[MAX_CARS], t2[MAX_CARS], tout[2*MAX_CARS];


void compute(int possible[MAX_CARS+1][MAX_CARS+1], int n1, int n2)
{
  if (possible[n1][n2] >= 0) {
    return;
  }

  // the last car needed is at index tout[n1+n2-1], and is either the
  // last car from train 1 or train 2
  int car = tout[n1+n2-1];
  if (n1 > 0 && car == t1[n1-1]) {
    // can take from train 1
    compute(possible, n1-1, n2);
    if (possible[n1-1][n2] == 1) {
      possible[n1][n2] = 1;
      return;
    }
  }
  if (n2 > 0 && car == t2[n2-1]) {
    // can take from train 2
    compute(possible, n1, n2-1);
    if (possible[n1][n2-1] == 1) {
      possible[n1][n2] = 1;
      return;
    }
  }

  possible[n1][n2] = 0;
}

bool do_case(void)
{
  cin >> N1 >> N2;
  if (!N1 && !N2) {
    return false;
  }

  // possible[i][j] = 1 if the first i cars from train 1 and
  //                       the first j cars from train 2 can be
  //                       used to form the first i+j cars in output
  //                = 0 not possible
  //                = -1 not computed
  int possible[MAX_CARS+1][MAX_CARS+1];
  
  for (int i = 0; i < N1; i++) {
    cin >> t1[i];
  }
  for (int i = 0; i < N2; i++) {
    cin >> t2[i];
  }
  for (int i = 0; i < N1+N2; i++) {
    cin >> tout[i];
  }

  for (int i = 0; i <= N1; i++) {
    fill(possible[i], possible[i]+N2+1, -1);
  }
  possible[0][0] = 1;

  compute(possible, N1, N2);
  cout << (possible[N1][N2] == 1 ? "possible" : "not possible") << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
