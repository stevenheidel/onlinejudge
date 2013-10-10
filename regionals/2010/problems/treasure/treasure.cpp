#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct Info {
  unsigned int denom;
  vector<string> children;

  Info()
    : denom(1) { };

  void add_child(const string &child)
  {
    children.push_back(child);
  }

  bool is_leaf() const
  {
    return children.size() == 0;
  }
};

void distribute(map<string, Info> &info, const string &parent,
		unsigned int denom = 1)
{
  if (info[parent].is_leaf()) {
    info[parent].denom = denom;
    return;
  }

  for (vector<string>::const_iterator it = info[parent].children.begin();
       it != info[parent].children.end(); ++it) {
    distribute(info, *it, denom * info[parent].children.size());
  }
}

bool do_case(void)
{
  string line;

  getline(cin, line);
  if (line == "**") {
    return false;
  }

  vector<string> names;
  map<string, Info> info;

  // build the tree
  bool first = true;
  do {
    istringstream iss(line);
    string parent, child;
    iss >> parent;
    if (first) {
      // if not first, the parent has already appeared as a child before
      names.push_back(parent);
    }
    while (iss >> child) {
      names.push_back(child);
      info[parent].add_child(child);
    }
    first = false;
    getline(cin, line);
  } while (line != "*");

  // process the tree
  distribute(info, names[0]);

  // print the results
  for (vector<string>::const_iterator it = names.begin(); it != names.end();
       ++it) {
    if (info[*it].is_leaf()) {
      cout << *it << ": 1/" << info[*it].denom << endl;
    }
  }
  
  return true;
}

int main(void)
{
  while (do_case()) {
    // string('-', 20)
    cout << "--------------------"  << endl;
  }

  return 0;
}
