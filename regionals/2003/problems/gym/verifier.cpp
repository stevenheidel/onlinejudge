#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "regex.h"

#define PROBLEM NUMBER

using namespace std;

char ifile[100];
ifstream is;
int ic=0;

char ofile[100];
ifstream os;
int oc=0;


char vfile[100];
ifstream vs;
int vc=0;

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
    char ifile[100],ofile[100],vfile[100];
    sprintf(ifile,"prob%d.dat",PROBLEM);
    sprintf(ofile,"prob%d.out.body",PROBLEM);
    sprintf(vfile,"prob%d.vfy.body",PROBLEM);
    is.open(ifile);
    os.open(ofile);
    vs.open(vfile);

    matcher match_numbers("^( *[0-9]*[.][0-9]*)*$");
    matcher match_head("^Program [0-9]+ by team [0-9]+$");
    matcher match_foot("^End of program [0-9]+ by team [0-9]+$");
    
    string iline,oline,vline;
    bool ok=false; // guilty until proven innocent

    try {
	for (;;) {
	    
	    vline=""; getline(vs,vline); ++vc; if (!vs) break;
	    oline=""; getline(os,oline); ++oc; if (!os) throw "too little output";

	    cout << "line " << oc << ": " << oline << "vs " << vline << endl;
	    
	    if (!match_numbers(oline)) {
		cout << ofile << " had " << oline << ", which doesn't look like a bunch of numbers" << endl;
		throw "incorrect output";
	    }
	    double xv,xo;
	    istringstream oss(oline);
	    istringstream vss(vline);

	    int basket=0;
	    while (vss >> xv) {
		++basket;
		if (!(oss >> xo)) {
		    cout << ofile << " is missing a value in " << oline << endl;
		    throw "incorrect output";
		}
		if (fabs(xv-xo)>0.0001) {
		    cout << ofile << " does not have 4 digits of precision between the output value " << xo << " and the correct value " << xv << " for basket " << basket << endl;
		    throw "incorrect output";
		}
	    }
	    if (!!(oss>>xo)) {
		cout << ofile << " has too many numbers on this line " << oline << endl;
		throw "incorrect output";
	    }
	}
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
