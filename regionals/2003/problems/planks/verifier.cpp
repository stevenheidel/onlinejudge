#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "regex.h"

#define PROBLEM NUMBER
using namespace std;

ifstream dat;
string datfile;
string datline;
int datcount;
ifstream out;
string outfile;
string outline;
int outcount;
ifstream vfy;
string vfyfile;
string vfyline;
int vfycount;

class matcher {
public:
    regex_t reg;
    enum { MAX_PARTS = 20 };
    regmatch_t pmatch[MAX_PARTS];
    int parts;
    string s;
    
    matcher(const string &rx,int flags=(REG_EXTENDED)) {
	regcomp(&reg, rx.c_str(), flags);
    }
    
    ~matcher() { regfree(&reg); }
    
    bool operator()(const string &_s,int eflags=0) {
	s=_s;
	return regexec(&reg,_s.c_str(),MAX_PARTS,pmatch,eflags)==0;
    }
    
    int begin(int i) { 
	if (i < 0 || i>= MAX_PARTS || pmatch[i].rm_so==-1) return -1;
	return pmatch[i].rm_so;
    }

    int end(int i) {
	if (i < 0 || i>= MAX_PARTS || pmatch[i].rm_so==-1) return -2;
	return pmatch[i].rm_eo;
    }

    string operator[](int i) {
	string ans;
	if (i < 0 || i>= MAX_PARTS || pmatch[i].rm_so==-1) return ans;
	int b=pmatch[i].rm_so;
	int n=pmatch[i].rm_eo-b;
	return s.substr(b,n);
    }
};

#define FMT(S,F) do { ostringstream tmp; tmp << F; (S)=tmp.str(); } while (0)
int main(int argc, char *argv[]) {
    bool ok=false;
    int c=0; // case count
    datcount=0;
    outcount=0;
    vfycount=0;

    try {
	FMT(datfile,"prob" << PROBLEM << ".dat");
	FMT(outfile,"prob" << PROBLEM << ".out.body");
	FMT(outfile,"prob" << PROBLEM << ".vfy.body");

        dat.open(datfile.c_str()); if (!dat) throw "could not open .dat file";
	out.open(outfile.c_str()); if (!out) throw "could not open .out file";
        vfy.open(outfile.c_str()); if (!vfy) throw "could not open .vfy file";


	matcher no_solution("^no solution possible$");
	matcher place("^place plank ([0-9]+) to stump \\(([0-9]+),([0-9]+)\\)$");
	matcher blank("^$");

	vector < string > grid(10);
	for (int r=0; r<10; ++r) { 
	    getline(dat,datline); if (!dat) break; else ++datcount;
            grid[r]=datline;
	}
	for (;;) {
	    ++c; // next case
	    // read plank from dat file
	    getline(dat,datline); if (!dat) break; else ++datcount;
	    istringstream iss(datline);
	    int plank,nplanks;
	    iss >> nplanks;
	    vector < int > planks;
	    vector < bool > used;
	    while (iss >> plank) { 
		planks.push_back(plank); 
		used.push_back(false); 
	    }

	    // read solution from vfy file
	    vector < string > vfyans;
	    for (;;) { 
		getline(vfy,vfyline); if (!vfy) break; else ++vfycount;
		if (blank(vfyline)) break;
		vfyans.push_back(vfyline);
		cout << "case " << c << " vfy: " << vfyline << endl;
	    }

	    // read solution from out file
	    vector < string > outans;
	    for (;;) {
		getline(out,outline); if (!out) break; else ++outcount;
		if (blank(outline)) break;
		outans.push_back(outline);
		cout << "case " << c << " out: " << outline << endl;
	    }

	    // end of file case
	    if (vfyans.size() == 0 && outans.size() != 0) throw "too much output";
	    else if (vfyans.size() == 1 && no_solution(vfyans[0])) {
		if (outans.size()!=1 || !no_solution(outans[0])) {
		    cout << "case " << c << " judge's solution states no solution, but team has one";
		    throw "invalid solution";
		}
	    } else { // walk the planks...
		int r=0,c=0,r1,c1,s;
		for (s=0; s<outans.size(); ++s) {
		    outline=outans[s];
		    if (!place(outans[s])) throw "not a plank placement";
		    sscanf(outans[s].c_str(),"place plank %d to stump (%d,%d)",&plank,&r1,&c1);
		    --plank; --r1; --c1;
		    if (plank < 0 || plank >= nplanks || used[plank]) throw "invalid plank";
		    used[plank]=true;
		    if (r1<0 || 10<=r1) throw "invalid row";
		    if (c1<0 || 10<=c1) throw "invalid column";
		    if (grid[r1][c1]!='*')   throw "missed stump";
		    if (!((c==c1 && abs(r-r1)==planks[plank]) || (r==r1 && abs(c-c1)==planks[plank])))
			throw "invalid move";
		    r=r1; c=c1;
		}
		if (r!=9 || c!=9) {
		    throw "path does not end at lower right corner";
		}
	    }
	}
	ok=true;
    } catch (const char *err) {
	cout << "case " << c << ": " << datfile << "("<< datcount<<":"<<datline<<")" << "/"
	     << outfile << "("<< outcount<< ":" << outline << ")" << "/"
	     << vfyfile << "("<< vfycount<< ":" << vfyline << "): " << err << endl;
	
	ok=false; 
    }
    if (!ok) {
	cout << "WRONG OUTPUT." << endl;
	return 1;
    } else {
      cout << "CORRECT!" << endl;
      return 0;
    }
}
