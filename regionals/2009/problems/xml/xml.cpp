#include <iostream>
#include <string>
#include <list>

#define DEBUG 0

using namespace std;

list<string> stack;
string line;
int pos;

bool match(char pattern, char value)
{
  if (pattern == 'H') { /* hex code */
    return (value >= '0' && value <= '9') 
      || (value >= 'A' && value <= 'F') 
      || (value >= 'a' && value <= 'f');
  }
  if (pattern == 'A') { /* lowercase alphanumeric */
    return (value >= '0' && value <= '9') 
      || (value >= 'a' && value <= 'z');
  }
  if (pattern == 'T') { /* plain text */
    return (value >= 32 && value <= 127)
      && value != '<' 
      && value != '>' 
      && value != '&';
  }
  return pattern == value;
}

bool matches(const char *m)
{
  int delta=0;
  while (m[delta] != 0 && 
	 pos+delta < (int)line.length() && match(m[delta],line[pos+delta]))
    ++delta;
  if (m[delta]==0) {
    pos += delta;
    return true;
  } else { 
    return false;
  }
}


bool ok()
{
  bool end_tag,short_tag;
  pos=0;
  stack.clear();

  while (pos < (int)line.length()) {
    if (matches("T")) continue;
    if (matches("&")) {
      if (matches("lt;") || matches("gt;") || matches("amp;")) continue;
      if (matches("xHH")) {
	while (matches("HH")) { }
	if (!matches(";")) return false;
      } else {
	// & not followed by valid escape sequence
	return false;
      }
      continue;
    }
    if (matches("<")) {
      end_tag=matches("/");

      int name_start=pos;
      while (matches("A")) { };
      int name_end=pos;
      string tag=line.substr(name_start,name_end-name_start);
      if (tag == "") return false;

      if (!end_tag) short_tag=matches("/");
      else short_tag = false;
      if (!matches(">")) return false;

      if (DEBUG) { cout << "encountered <" << (end_tag ? "/" : "") << tag << (short_tag ? "/" : "") << ">" << endl; }

      if (!end_tag && !short_tag) { stack.push_back(tag); }
      if (end_tag) { 
	if (stack.empty() || *stack.rbegin() != tag) return false;
	stack.pop_back();
      }
      continue;
    }
    return false;
  }
  return stack.empty();
}

int main()
{
  for (;;) {
    getline(cin,line);
    if (cin.eof()) break;
    if (DEBUG) { cout << "checking: '" << line << "'" << endl; }
    
    if (ok()) {
      cout << "valid" << endl;
    } else {
      cout << "invalid" << endl;
    }
  }

  return 0;
}
