#include "string.h"
#include "stdio.h"

int problem=NUMBER;
int team=0;
FILE *in=0;
FILE *out=0;
int debug=0;
char linebuffer[80000];

void solve()
{
    int count=0;
    while (fgets(linebuffer,sizeof(linebuffer),in)!=0) {
	++count;
    }
    fprintf(out,"%d\n",count);
}
    

int main(int argc, const char *argv[])
{
  int argi;
  int suppress=0;
  char infilename[100];
  char outfilename[100];

  strcpy(infilename,"");
  strcpy(outfilename,"");

  for (argi=1; argi<argc; ++argi) {
    const char *arg=argv[argi];
    if (strcmp(arg,"-i")==0) {
      strcpy(infilename,argv[++argi]);
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
    if (strcmp(arg,"-t")==0) {
      team=atoi(argv[++argi]);
      continue;
    }
    if (strcmp(arg,"-p")==0) {
      problem=atoi(argv[++argi]);
      continue;
    }
    if (strcmp(arg,"-s")==0) {
      suppress=1;
      continue;
    }
    printf("unknown argument arg[%d]=\"%s\"\n",argi,arg);
    exit(1);
  }

  if (strcmp(infilename,"")==0) {
    sprintf(infilename,"prob%d.dat",problem);
  }

  if (strcmp(infilename,"-")!=0) {
    in = fopen(infilename,"r");
  } else {
    in = stdin;
  }

  if (in == 0) 
  {
    printf("prob%d: failed to open input file %s\n",problem,infilename);
    exit(1);
  }

  if (strcmp(outfilename,"")==0) {
    sprintf(outfilename,"prob%d.out",problem);
  }

  if (strcmp(outfilename,"-")!=0) {
    out = fopen(outfilename,"w");
  } else {
    out = stdout;
  }

  if (out == 0) 
  {
    printf("prob%d: failed to open output file %s\n",problem,outfilename);
    exit(1);
  }
  
  if (!suppress) {
    fprintf(out,"Program %d by team %d\n",problem,team);
  }

  solve();

  if (!suppress) {
    fprintf(out,"End of program %d by team %d\n",problem,team);
  }
  if (in != stdin) fclose(in);
  if (out != stdout) fclose(out);

  return 0;
}
