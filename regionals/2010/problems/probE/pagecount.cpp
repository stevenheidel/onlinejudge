#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

bool do_case(void)
{
  int total;
  cin >> total;
  cin.ignore(1);
  if (total == 0) {
    return false;
  }

  string line;
  getline(cin, line);

  vector< pair<int, int> > ranges;
  istringstream iss(line);
  int low, high;
  while (iss >> low) {
    char c;
    iss.get(c);
    if (c == ',' && low <= total) {
      ranges.push_back(make_pair(low, low));
    } else if (c == '-') {
      iss >> high;
      iss.get(c);
      high = min(high, total);
      if (low <= high) {
	ranges.push_back(make_pair(low, high));
      }
    }
  }

  sort(ranges.begin(), ranges.end());

  int pages = 0;
  int last =  0;

  for (unsigned int i = 0; i < ranges.size(); i++) {
    if (ranges[i].first <= last && ranges[i].second <= last) {
      // this one is covered by the current range, do nothing
    } else if (ranges[i].first <= last && ranges[i].second > last) {
      // overlap need to extend current range
      pages += ranges[i].second - last;
      last = ranges[i].second;
    } else if (ranges[i].first > last) {
      // no overlap, extend
      pages += ranges[i].second - ranges[i].first + 1;
      last = ranges[i].second;
    } else {
      // there should not be any other case due to the ordering of the ranges
      assert(false);
    }
  }

  cout << pages << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
