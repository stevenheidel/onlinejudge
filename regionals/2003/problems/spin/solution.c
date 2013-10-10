
#define TEAM    0   /* Your team # here */
#define PROBLEM NUMBER   /* The problem # here */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *in=0;
FILE *out=0;
void solve_problem();

/*-------------------------------------------------------*/
int main(int argc, char *argv[])
{
    char inputFilename[64];
    char outputFilename[64];
    int  teamNumber   = TEAM;
    int  j;

    sprintf(inputFilename, "prob%d.dat", PROBLEM);
    sprintf(outputFilename,"prob%d.out", PROBLEM);

    /* Process the command line arguments. This can change the filenames and/or team number */
    j=1;
    while (j<argc)
    {
      if (argv[j][0] == '-')
      {
        switch (argv[j][1])
        {
          case 'i' : strcpy(inputFilename, argv[++j]);
                     break; 
          case 'o' : strcpy(outputFilename, argv[++j]);
                     break;
          case 't' : sscanf(argv[++j], "%d", &teamNumber);
                     break;
          default  : printf("unrecognized command line argument\n");
                     break;
        }
      }
      j++;
    }

    in = fopen(inputFilename, "r");
    if (in == 0) {
	    printf("could not open input file %s\n", inputFilename);
	    exit(1);
    }
    
    out = fopen(outputFilename,"w");
    if (out == 0) {
	    printf("could not open output file %s\n", outputFilename);
	    exit(1);
    }

    fprintf(out,"Program %d by team %d\n",PROBLEM,teamNumber);

    solve_problem();

    fprintf(out,"End of program %d by team %d\n",PROBLEM,teamNumber);

    fclose(in);
    fclose(out);

    return 0;
}

/*-------------------------------------------------------*/
void solve_problem()
{
  char      wheels[100];  /* max is 10 */
  char      button[100];
  int       D;
  int       j;

  /* Get the initial position of the wheels */
  fscanf(in, "%s", wheels);
  D = strlen(wheels);

  while ( fscanf(in, "%s", button) != EOF)
  {
    /* update each wheel separately */
    for (j=0; j<D; j++)
    {
      wheels[j] += (button[j] - '0');
      if (wheels[j] > '9') wheels[j] -= 10;
    }
  }

  fprintf(out, "%s\n",wheels);
}
