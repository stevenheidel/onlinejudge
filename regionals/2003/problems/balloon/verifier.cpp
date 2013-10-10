#include <iostream>
#include <fstream>
#include <string>
#include "regex.h"

#define PROBLEM 11
#define INPUT   "prob11.dat"
#define OUTPUT  "prob11.out"
#define VERIFY  "prob11.vfy"

using namespace std;

ifstream is;
ifstream os;
ifstream vs;

class matcher {
public:
  regex_t reg;

  matcher(const string &rx="",int flags=(REG_EXTENDED|REG_NOSUB)) {
    regcomp(&reg, rx.c_str(), flags);
  }

  ~matcher() { regfree(&reg); }

  bool operator()(const string &s,int eflags=0) {
    return regexec(&reg,s.c_str(),0,0,eflags)==0;
  }
};


int main(int argc, char *argv[]) {
  is.open(INPUT);
  os.open(OUTPUT);
  vs.open(VERIFY);

  matcher match_number("^ *[0-9]+[.][0-9]*$");
  matcher match_head("^Program [0-9]+ by team [0-9]+$");
  matcher match_foot("^End of program [0-9]+ by team [0-9]+$");

  double length1 = 0.25*(14.0 + 8.0*(M_PI-atan2(1.0,8.0)-atan2(7.0,4.0)));
  double length,length_verify;

  string iline,oline,vline;
  int ic=0;
  int oc=0;
  int vc=0;
  bool ok=false; // guilty until proven innocent

  try {
    getline(os,oline); ++oc; if (!os || !match_head(oline)) throw "wrong head line.";
    for (;;) {
      getline(is,iline); ++ic; if (!is) break;
      double r;
      sscanf(iline.c_str()," %lf",&r);
      length=length1*r;
      getline(os,oline); ++oc; 
      if (!os) {
        cout << OUTPUT << " " << oc << ": " << " missing output line" << endl;
        throw "missing output line";
      }
      if (!match_number(oline)) {
         cout << OUTPUT << " " << oc << ": " << oline << " should look like a number." << endl;
         throw "nonconforming output line.";
      }
      sscanf(oline.c_str()," %lf",&length_verify);
      double re = fabs(length-length_verify)/length;
      if (re > 0.01) {
        cout << OUTPUT << " " << oc << ": " << oline << " re = " << re*100 << "% (too big)" <<  endl;
        throw "incorrect value";
      } else {
        cout << OUTPUT << " " << oc << ": " << oline << " re = " << re*100 << "% (ok)" <<  endl;
      }
    }
    getline(os,oline); ++oc; if (!os || !match_foot(oline)) throw "wrong foot line.";
    getline(os,oline); ++oc; if (!!os) throw "too much output";
    ok=true;
  } catch (char *err) { }

  if (!ok) {
      cout << "WRONG OUTPUT." << endl;
      return 1;
  } else {
      cout << "CORRECT!" << endl;
      return 0;
  }
}
