#define PROBLEM NUMBER /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cassert>

using namespace std;

ifstream in;
ofstream out; 
int team=TEAM;
void solve_problem(); 

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
  solve_problem(); 
  out << "End of program " << NUMBER << " by team " << team << endl;
  return 0; 
}

int number(const string &s)
{
  int sum = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    sum = sum*10 + (s[i] - '0');
  }
  return sum;
}

string decode(const string &F, const string &C)
{
  int numF = number(F);
  int numC = number(C);
  string R;

  if (numC > numF) {
    return C;
  }

  if (C.length() <= F.length()) {
    numF = number(F.substr(F.length()-C.length(), C.length()));
  }
  if (numF < numC) {
    if (C.length() <= F.length()) {
      return F.substr(0, F.length() - C.length()) + C;
    } else {
      assert(0);
      return "";
    }
  } else {
    if (C.length() <= F.length()) {
      R = F.substr(0, F.length() - C.length()) + C;
    } else {
      R = C;
    }
    int carry = 1;
    int i;
    for (i = R.length() - 1 - C.length(); i >= 0; i--) {
      if (R[i] == '9') {
	R[i] = '0';
	carry = 1;
      } else {
	R[i] = R[i] + 1;
	carry = 0;
	break;
      }
    }
    if (i < 0 && carry) {
      R.insert(0, "1");
    }
    return R;
  }
}

void solve_problem(void)
{
  string F, C, R;

  getline(in, F, '-');
  getline(in, R);
  while (!in.eof()) {
    for (unsigned int i = 1; i <= R.length(); i++) {
      C = R.substr(R.length()-i, i);
      if (decode(F, C) == R) {
	out << F << '-' << C << endl;
	break;
      }
    }
    getline(in, F, '-');
    getline(in, R);
  }
}
