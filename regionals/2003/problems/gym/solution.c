#include <stdio.h>

#define TEAM 0
#define PROBLEM NUMBER
#define NMAX 10
int np;
double p[NMAX][NMAX];
double q[NMAX],q0[NMAX];

char datfile[100];
FILE *dat;
char outfile[100];
FILE *out;
int debug=0;
void solve()
{
  char line[1024];
  int r,c,s;
  r=0;
  for (;;) {
    int base=0,shift,c=0;
    double sum;
    if (!fgets(line,sizeof(line),dat)) break;
    sum=0.0;
    while (sscanf(line+base," %lf%n",&p[r][c],&shift)>0) {
      sum += p[r][c];
      ++c;
      base += shift;
    }
    np=c;
    for (c=0; c<np; ++c) { p[r][c] = p[r][c]/sum; }
    ++r;
  }

  if (debug) {
    fprintf(out,"np=%d",np);
    for (r=0; r<np; ++r) { 
      for (c=0; c<np; ++c) {
        fprintf(out," %10.8lf",p[r][c]);
      }
      fprintf(out,"\n");
    }
  }

  for (c=0; c<np; ++c) q[c]=(c==0);
  for (s=0; s<10; ++s) {
    for (c=0; c<np; ++c) {
      fprintf(out,"%s%7.5lf",((c>0)?" ":""),q[c]);
    }
    fprintf(out,"\n");
    for (c=0; c<np; ++c) {
      q0[c]=q[c];
    }
    for (c=0; c<np; ++c) {
      q[c]=0;
      for (r=0; r<np; ++r) {
        q[c] += p[r][c]*q0[r];
      }
    }
  }
}

int main(int argc, char *argv[])
{
  int argi;
  int team=TEAM;

  sprintf(datfile,"prob%d.dat",PROBLEM);
  sprintf(outfile,"prob%d.out",PROBLEM);
  for (argi=1; argi<argc; ++argi) {
    const char *arg=argv[argi];
    if (strcmp(arg,"-i")==0) { strcpy(datfile,argv[++argi]); continue; }
    if (strcmp(arg,"-o")==0) { strcpy(outfile,argv[++argi]); continue; }
    if (strcmp(arg,"-t")==0) { team=atoi(argv[++argi]); continue; }
    if (strcmp(arg,"-d")==0) { debug=1; continue; }
    printf("unknown arg[%d]=%s\n",argi,arg);
    exit(1);
  }

  if (!(dat=strcmp(datfile,"-")==0?stdin:fopen(datfile,"r"))) {
    printf("Could not open input file: %s\n",datfile);
    exit(1);
  }

  if (!(out=strcmp(outfile,"-")==0?stdout:fopen(outfile,"w"))) {
    printf("Could not open output file: %s\n",outfile);
    exit(1);
  }

  fprintf(out,"Program %d by team %d\n",PROBLEM,team);
  solve();
  fprintf(out,"End of program %d by team %d\n",PROBLEM,team);  
  if (out != stdout) fclose(out);
  if (dat != stdin)  fclose(dat);
}
