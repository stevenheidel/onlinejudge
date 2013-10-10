#include <iostream>
#include <string>

using namespace std;

char spin(char c)
{
  switch(c) {
  case 'b': return 'q';
  case 'd': return 'p';
  case 'l': return 'l';
  case 'm': return 'w';
  case 'n': return 'u';
  case 'o': return 'o';
  case 'p': return 'd';
  case 'q': return 'b';
  case 'u': return 'n';
  case 'w': return 'm';
  case 'x': return 'x';
  default: return 0;
 };
}

int score(char c1,char c2)
{
  int ans=0;
  if (c1 == c2) ans += 1;
  if (spin(c1) == c2) ans += 2;
  return ans;
}

int score(const std::string &word)
{
  int ans=0;
  int n=word.length();
  for (int i=0; i<n; ++i) ans += score(word[i],word[n-i-1]);
  return ans;
}

int main()
{
  string word;
  while (cin >> word) {
    cout << word << " " << score(word) << endl;
  }
  return 0;
}
