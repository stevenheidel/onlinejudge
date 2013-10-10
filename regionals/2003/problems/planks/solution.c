#define TEAM    0   /* Your team # here */
#define PROBLEM NUMBER   /* The problem # here */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

FILE *in=0;
FILE *out=0;
void solve_problem();
int  debug = 0;

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
#define TRUE   1
#define FALSE  0

char   swamp[10][10];
int    numberPlanks;
int    plankLength[20];
int    plankAvailable[20];
int    usePlank[20];
int    stump[20][2];

/*-------------------------------------------------------*/
int nextPlank(int step, int row, int col)
{
  int length;
  int j;

  if (debug)
    printf("step = %d  row = %d  col = %d\n", step, row, col);

  /* base case - we have reached the destination */
  if (row == 9 && col == 9) return step;

  /* search for a plank to lay */
  for (j=0; j<numberPlanks; j++)
  {
    if (plankAvailable[j])
    {
      if (row + plankLength[j] < 10 &&
          swamp[row + plankLength[j]][col] == '*') /* move possible */
      {
        plankAvailable[j] = FALSE;
        length = nextPlank( step+1, row + plankLength[j], col);
        if (length > 0)
        {
          usePlank[step] = j;
          stump[step][0] = row + plankLength[j];
          stump[step][1] = col;
          return length;
        }
        plankAvailable[j] = TRUE;
      }

      if (row - plankLength[j] >= 0 &&
          swamp[row - plankLength[j]][col] == '*') /* move possible */
      {
        plankAvailable[j] = FALSE;
        length = nextPlank( step+1, row - plankLength[j], col);
        if (length > 0)
        {
          usePlank[step] = j;
          stump[step][0] = row - plankLength[j];
          stump[step][1] = col;
          return length;
        }
        plankAvailable[j] = TRUE;
      }

      if (col + plankLength[j] < 10 &&
          swamp[row][col + plankLength[j]] == '*') /* move possible */
      {
        plankAvailable[j] = FALSE;
        length = nextPlank( step+1, row, col + plankLength[j]);
        if (length > 0)
        {
          usePlank[step] = j;
          stump[step][0] = row;
          stump[step][1] = col + plankLength[j];
          return length;
        }
        plankAvailable[j] = TRUE;
      }

      if (col - plankLength[j] >= 0 &&
          swamp[row][col - plankLength[j]] == '*') /* move possible */
      {
        plankAvailable[j] = FALSE;
        length = nextPlank( step+1, row, col - plankLength[j]);
        if (length > 0)
        {
          usePlank[step] = j;
          stump[step][0] = row;
          stump[step][1] = col - plankLength[j];
          return length;
        }
        plankAvailable[j] = TRUE;
      }
    }
  }
  return 0; 
}
/*-------------------------------------------------------*/
void solve_problem()
{
  int    j, k;
  int    numberSteps;

  /* Read the swamp definition */
  for (j=0; j<10; j++)
  {
    for (k=0; k<10; k++)
      fscanf(in, "%c", &swamp[j][k]);

    fscanf(in, "\n");
  }

  if (debug)
  {
    for (j=0; j<10; j++)
    {
      for (k=0; k<10; k++)
        printf("%c", swamp[j][k]);

      printf("\n");
    }
  }

  while ( fscanf(in, "%d", &numberPlanks) != EOF)
  {
    for (j=0; j<numberPlanks; j++)
      fscanf(in, "%d", &plankLength[j]);

    if (debug)
    {
      printf("For %d planks of length ", numberPlanks);
      for (j=0; j<numberPlanks; j++)
        printf("%d  ", plankLength[j]);
      printf("\n");
    }

    for (j=0; j<20; j++)
      plankAvailable[j] = TRUE;
    
    numberSteps = nextPlank(0, 0, 0);
    if ( numberSteps > 0 )
    {
      for (j=0; j<numberSteps; j++)
        fprintf(out, "place plank %d to stump (%d,%d)\n",
                      usePlank[j]+1, stump[j][0]+1, stump[j][1]+1 );
      fprintf(out, "\n");
    }
    else
    {
      fprintf(out, "no solution possible\n\n");
    }

  }

}


