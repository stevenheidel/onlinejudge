
#define TEAM    0   /* Your team # here */
#define PROBLEM NUMBER   /* The problem # here */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *in=0;
FILE *out=0;
void solve_problem();

/*--------------------------------------------------------*/
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

/*--------------------------------------------------------*/

#define   TRUE  1
#define   FALSE 0
#define   DEBUG 0

int   size;
int   permutation[13];
int   inverted;
int   numberOfPermutations;
int   answer;
int   counts[200];
int   available[20];


/*--------------------------------------------------------*/
void testPermutation(void)
{
  int      j, k;
  int      sum;
  
  numberOfPermutations++;

  sum = 0;
  for (j=1; j<size; j++)
  {
    for (k=0; k<j; k++)
    {
      if (permutation[k] > permutation[j]) sum++;
    }
  }

  counts[sum]++;
}

/*--------------------------------------------------------*/
void buildPermutations( int level )
{
  int  j;
  
  if (level == size) testPermutation();
  else
  {
    for (j=0; j<size; j++)
    {
      if (available[j])
      {
        available[j] = FALSE;
        permutation[level] = j+1;
        buildPermutations( level+1 );
        available[j] = TRUE;
      }
    }
  }
}
/*--------------------------------------------------------*/
double factorial(int n)
{
  double answer = 1.0;

  while (n > 1)
  {
    answer *= (double) n;
    n--;
  }
  return answer;
}
/*--------------------------------------------------------*/
void solve_problem()
{
  int     j, k;
  double  answers[21][200] = {0.0};
  double  total;
  double  remainder;
  int     array_size;
  int     half;
  int     numberInverted;
    
  /* initial case */
  size = 0;
  answers[0][0] = 0.0;

  size = 1;
  answers[1][0] = 1.0;

  size = 2;
  answers[2][0] = 1.0;
  answers[2][1] = 1.0;

  size = 3;
  answers[3][0] = 1.0;
  answers[3][1] = 2.0;
  answers[3][2] = 2.0;
  answers[3][3] = 1.0;

  array_size = 7;
  for (size = 4; size<=20; size++)
  {
    half = array_size / 2;
    
    /* calculate the first "easy" half of the array */
    total = 1.0;
    answers[size][0] = 1.0;
    for (j=1; j<size; j++)
    {
      answers[size][j] = answers[size][j-1] + answers[size-1][j];
      total += answers[size][j];
    }

    /* calculate the second "hard" half of the array */
    for (j=size, k=0; j<half; j++, k++)
    {
      answers[size][j] = answers[size][j-1] + answers[size-1][j] - answers[size-1][k];
      total += answers[size][j];
    }

    /* fill in the middle terms */
    remainder = ((double) factorial(size)) - 2.0*total;

    if (half >= size)
    {
      if (array_size % 2 == 1) answers[size][half] = remainder;
      else                     answers[size][half] = remainder/2.0;
    }

    /* copy the first half of the array to the second half but reverse it */
    for (j=0, k=array_size-1; j <= half; j++, k--)
      answers[size][k] = answers[size][j]; 
    
    if (size <= 10) /* compare these answers to the brute force answers for small permutations */
    {
      for (j=0; j<size; j++)
        available[j] = TRUE;

      for (j=0; j<200; j++)
        counts[j] = 0;

      numberOfPermutations = 0;
      buildPermutations( 0 );

      for (j=0; j<array_size; j++)
        if (((double) counts[j]) != answers[size][j])
          printf("\nERROR - mismatch found\n");
    }

    array_size = array_size + size;
  }

  if (DEBUG)
  {
    /* print the answer matrix for debugging */
    array_size = 0;
    for (size=0; size<21; size++)
    {
      printf("%2d: ", size);
      for (j=0; j<=array_size; j++)
        printf("%16.0lf ", answers[size][j]);
      printf("\n");

      array_size = array_size + size;
    }
  }

  /* Actual solution */
  while ( fscanf(in, "%d %d", &size, &numberInverted) != EOF)
  {
    if (size == 0 && numberInverted == 0) break;
    
    fprintf(out, "%1.0f\n", answers[size][numberInverted]);
  }
}


