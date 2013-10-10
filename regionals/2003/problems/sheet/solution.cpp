#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>


using namespace std;

int team=0;
ifstream in;
ofstream out; 
int debug=0;
void solve();

int main(int argc, char *argv[])
{
    char datfilename[100];
    char outfilename[100];

    sprintf(datfilename, "prob%d.dat", NUMBER); 
    sprintf(outfilename, "prob%d.out", NUMBER); 
    for (int argi=1; argi<argc; ++argi) {
	const char *arg=argv[argi];
	if (strcmp(arg,"-i")==0) {
	    strcpy(datfilename,argv[++argi]);
	    continue;
	}
	if (strcmp(arg,"-o")==0) {
	    strcpy(outfilename,argv[++argi]);
	    continue;
	}
	if (strcmp(arg,"-t")==0) {
	    team=atoi(argv[++argi]);
	    continue;
	}
	printf("unknown argument arg[%d]=\"%s\"\n",argi,arg);
	exit(1);
  }
  in.open(datfilename, ios::in); 
  if (!in) { 
    cout << "could not open input file " << datfilename << endl; 
    exit(1); 
  } 
  out.open(outfilename, ios::out); 
  if (!out) { 
    cout << "could not open output file " << outfilename << endl; 
    exit(1);
  } 
  out << "Program " << NUMBER << " by team " << team << endl; 
  solve(); 
  out << "End of program " << NUMBER << " by team " << team << endl;
  return 0; 
}

int cell_index(const string &s, int i)
{
  int r = (s[i+1]-'0')*10 + s[i+2]-'0';
  int c = (s[i+4]-'0')*10 + s[i+5]-'0';
  return (r-1)*20 + (c-1);
}

void print_cell(int i)
{
  int r = (i / 20) + 1;
  int c = (i % 20) + 1;
  out << "R" << setfill('0') << setw(2) << r;
  out << "C" << setfill('0') << setw(2) << c;
}

void solve(void)
{
  const unsigned int max_cell = 400;
  bool graph[max_cell][max_cell];
  int order[max_cell];
  unsigned int count = 0;
  unsigned int i, j, k;

  for (i = 0; i < max_cell; i++) {
    order[i] = -1;
    for (j = 0; j < max_cell; j++) {
      graph[i][j] = false;
    }
    graph[i][i] = true;
  }
  
  string defn;
  while (in >> defn) {
    i = 0;
    int lhs = cell_index(defn, i);
    i += 7;
    if (order[lhs] < 0) {
      order[lhs] = count++;
    }
    while (i < defn.length() && (j = defn.find("R", i)) != string::npos) {
      int rhs = cell_index(defn, j);
      if (order[rhs] < 0) {
	order[rhs] = count++;
      }
      graph[order[lhs]][order[rhs]] = true;
      i = j + 6;
    }
  }
  
  for (k = 0; k < count; k++) {
    for (i = 0; i < count; i++) {
      for (j = 0; j < count; j++) {
	graph[i][j] |= (graph[i][k] && graph[k][j]);
      }
    }
  }
  
  for (i = 0; i < max_cell; i++) {
    if (order[i] < 0) continue;
    k = order[i];
    for (j = 0; j < count; j++) {
      if (j != k && graph[k][j] && graph[j][k]) {
	break;
      }
    }
    print_cell(i);
    if (j < count) {
      out << " circular" << endl;
    } else {
      out << " ok" << endl;
    }
  }

}
