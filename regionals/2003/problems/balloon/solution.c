#include "string.h"
#include "stdio.h"
#include "math.h"

#ifndef TEAM
#define TEAM 0
#endif

#ifndef NUMBER
#define NUBMER 0
#endif

FILE *in=0;
FILE *out=0;
int debug=0;
int team=TEAM;
int number=NUMBER;

void solve()
{
  double rope4 = 14.0 + 8.0*(M_PI-atan2(1.0,8.0)-atan2(7.0,4.0));
  if (debug) {
    fprintf(out,"DEBUG> rope4=%lg\n",rope4);
  }
  for (;;) {
    double r;
    if (fscanf(in," %lf",&r) < 1) break;
    double rope = rope4*(r/4.0);
    fprintf (out,"%0.4lf\n", rope);
  }
}

int main(int argc, const char *argv[])
{
  int argi;
  int suppress_leader_and_trailer=0;
  char infilename[100];
  char outfilename[100];

  sprintf(infilename,"prob%d.dat",number);
  sprintf(outfilename,"prob%d.out",number);

  for (argi=1; argi<argc; ++argi) {
    const char *arg=argv[argi];
    if (strcmp(arg,"-i")==0) {
      strcpy(infilename,argv[++argi]);
      continue;
    }
    if (strcmp(arg,"-t")==0) {
      team=atoi(argv[++argi]);
      continue;
    }
    if (strcmp(arg,"-p")==0) {
      number=atoi(argv[++argi]);
      continue;
    }
    if (strcmp(arg,"-o")==0) {
      strcpy(outfilename,argv[++argi]);
      continue;
    }
    if (strcmp(arg,"-d")==0) {
      debug=1;
      continue;
    }
    if (strcmp(arg,"-s")==0) {
      suppress_leader_and_trailer=1;
      continue;
    }
    if (strcmp(arg,"-h")!=0) {
      printf("unknown argument arg[%d]=\"%s\"\n",argi,arg);
    }
    printf("usage prob%d [-d] [-s] [-i infile] [-o outfile]\n");
    printf("    -d enables debug (debug=1)\n");
    printf("    -s supresses leader and trailer lines\n");
    printf("    -i file Specify an input file other than prob%d.dat\n",number);
    printf("    -o file Specify an output file other than prob%.out\n",number);
    printf("       (use -i - for stdin, -o - for stdout)\n");
    exit(1);
  }

  if (strcmp(infilename,"-")!=0) {
    in = fopen(infilename,"r");
  } else {
    in = stdin;
  }

  if (in == 0) 
  {
    printf("prob%d: failed to open input file %s\n",number,infilename);
    exit(1);
  }

  if (strcmp(outfilename,"-")!=0) {
    out = fopen(outfilename,"w");
  } else {
    out = stdout;
  }

  if (out == 0) 
  {
    printf("prob%d: failed to open output file %s\n",number,outfilename);
    exit(1);
  }
  
  if (!suppress_leader_and_trailer) {
    fprintf(out,"Program %d by team %d\n",number,team);
  }

  if (debug) {
    fprintf(out,"DEBUG> prob%d%s%s -i %s -o %s\n",number,
            (debug ? " -d" : ""),
            (suppress_leader_and_trailer ? " -s" : ""),
            infilename,
            outfilename);
  }

  solve();

  if (!suppress_leader_and_trailer) {
    fprintf(out,"End of program %d by team %d\n",number,team);
  }
  if (in != stdin) fclose(in);
  if (out != stdout) fclose(out);

  return 0;
}
