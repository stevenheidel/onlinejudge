#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

const int MAX_VALUE = 1000000-1;

struct MyPair {
  int num;
  string name;
};

const MyPair card_table[] = {
  { 1, "one" },
  { 2, "two" },
  { 3, "three" },
  { 4, "four" },
  { 5, "five" },
  { 6, "six" },
  { 7, "seven" },
  { 8, "eight" },
  { 9, "nine" },
  { 10, "ten" },
  { 11, "eleven" },
  { 12, "twelve" },
  { 13, "thirteen" },
  { 14, "fourteen" },
  { 15, "fifteen" },
  { 16, "sixteen" },
  { 17, "seventeen" },
  { 18, "eighteen" },
  { 19, "nineteen" },
  { 20, "twenty" },
  { 30, "thirty" },
  { 40, "forty" },
  { 50, "fifty" },
  { 60,	"sixty" },
  { 70, "seventy" },
  { 80, "eighty" },
  { 90, "ninety" },
  { 100, "hundred" },
  { 1000, "thousand" },
  { -1, "endoftable"}
};

const MyPair ord_table[] = {
  { 1, "first" },
  { 2, "second" },
  { 3, "third" },
  { 4, "fourth" },
  { 5, "fifth" },
  { 6, "sixth" },
  { 7, "seventh" },
  { 8, "eighth" },
  { 9, "ninth" },
  { 10, "tenth" },
  { 11, "eleventh" },
  { 12, "twelfth" },
  { 13, "thirteenth" },
  { 14, "fourteenth" },
  { 15, "fifteenth" },
  { 16, "sixteenth" },
  { 17, "seventeenth" },
  { 18, "eighteenth" },
  { 19, "nineteenth" },
  { 20, "twentieth" },
  { 30, "thirtieth" },
  { 40, "fortieth" },
  { 50, "fiftieth" },
  { 60,	"sixtieth" },
  { 70, "seventieth" },
  { 80, "eightieth" },
  { 90, "ninetieth" },
  { 100, "hundredth" },
  { 1000, "thousandth" },
  { -1, "endoftable"}
};

string find(const MyPair table[], int n)
{
  int i;
  for (i = 0; table[i].num > 0 && table[i].num != n; i++)
    ;
  if (table[i].num == n) {
    return table[i].name;
  }
  assert(false);
}

string cardinal(int n)
{
  assert(n < 1000);
  if (n < 20) {
    return find(card_table, n);
  } else if (n < 100) {
    int tens = (n / 10) * 10;
    int rem = n % 10;
    if (rem == 0) {
      return find(card_table, tens);
    } else {
      return find(card_table, tens) + cardinal(rem);
    }
  } else {
    int hundreds = n / 100;
    int rem = n % 100;

    string ans = cardinal(hundreds) + find(card_table, 100);
    if (rem > 0) {
      ans += cardinal(rem);
    }
    return ans;
  }

}

string ordinal(int n)
{
  if (n < 20) {
    return find(ord_table, n);
  } else if (n < 100) {
    int tens = (n / 10) * 10;
    int rem = n % 10;
    if (rem == 0) {
      return find(ord_table, tens);
    } else {
      return find(card_table, tens) + ordinal(rem);
    }
  } else if (n < 1000) {
    int hundreds = n / 100;
    int rem = n % 100;

    string ans = cardinal(hundreds);
    if (rem == 0) {
      return ans + find(ord_table, 100);
    } else {
      return ans + find(card_table, 100) + ordinal(rem);
    }
  } else {
    assert(n <= MAX_VALUE);
    int thousands = n / 1000;
    int rem = n % 1000;

    string ans = cardinal(thousands);
    if (rem == 0) {
      return ans + find(ord_table, 1000);
    } else {
      return ans + find(card_table, 1000) + ordinal(rem);
    }
  }
}

vector<int> value;

void setup(void)
{
  string defn = "tisthe";
  string::size_type index = 1;

  value.clear();
  value.push_back(index);
  while (index <= (unsigned int)MAX_VALUE) {
    if (defn.length() < (unsigned int)MAX_VALUE) {
      defn += ordinal(index);
    }
    index = defn.find('t', index);
    assert(index != string::npos);
    index++;
    if (index <= (unsigned int)MAX_VALUE) {
      value.push_back(index);
    }
  }
  //  cout << defn.substr(0, 2850) << endl;
}

int main(void)
{
  setup();
  int k;
  while (cin >> k && k > 0) {
    if ((unsigned int)k-1 < value.size()) {
      cout << value[k-1] << endl;
    } else {
      cout << "Too big." << endl;
    }
  }
  return 0;
}
