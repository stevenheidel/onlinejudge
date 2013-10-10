#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

const int MAX_N = 100;

int compute(int N, int P[], int len)
{
  int maxP = *max_element(P, P+N);
  int total = accumulate(P, P+N, 0);
  
  int climbers = len / maxP + 1;
  if (climbers < 2 || len < 2*total) {
    // this takes care of "rope at least as long as the pitch" as well
    return 0;
  } else {
    return climbers;
  }
}

int main(void)
{
  int N;
  while (cin >> N && N != 0) {
    int P[MAX_N];
    for (int i = 0; i < N; i++) {
      cin >> P[i];
    }
    
    cout << compute(N, P, 50) << ' ';
    cout << compute(N, P, 60) << ' ';
    cout << compute(N, P, 70) << endl;
  }
  return 0;
}
