
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
#define MAX_PARTITIONS    5002
#define TRUE                 1
#define FALSE                0
#define UPPER                0
#define LOWER                1

typedef struct point {
  float   x;
  float   y;
} point;

int    numberPartitions;
int    numberToys;
point  upperLeft;
point  lowerRight;
point  partitions[MAX_PARTITIONS][2];
int    counts[MAX_PARTITIONS];

/*-------------------------------------------------------*/
int leftOfPartition(point *common, point *partition, point *toy)
{
  if ( ((partition->x - common->x)*(toy->y - common->y) -
        (partition->y - common->y)*(toy->x - common->x)) > 0.0) return TRUE;
  else                                                          return FALSE;
}

/*-------------------------------------------------------*/
void addToyToCounts(point *toy)
{
  int  first, mid, last;

  /* binary search */
  first = 1;
  last  = numberPartitions+1;
  while (first <= last)
  {
    mid = (first + last) / 2;
    if (leftOfPartition(&partitions[mid][LOWER], &partitions[mid][UPPER], toy) )
    {
      /* Is it to the right of the previous partition? */
      if ( ! leftOfPartition(&partitions[mid-1][LOWER], &partitions[mid-1][UPPER], toy) )
      {
        counts[mid-1]++;
        return;
      }
      else
        last = mid-1;
    }
    else
      first = mid+1;
  }
  printf("Error - search failed\n");
}
/*-------------------------------------------------------*/
void solve_problem()
{
  int     j;
  int     firstProblem = 1;
  point   toy;

  while ( TRUE )
  {
    fscanf(in, "%d", &numberPartitions);
    if (numberPartitions == 0) break;
    fscanf(in, "%d %f %f %f %f\n", &numberToys,
                                   &upperLeft.x, &upperLeft.y,
                                   &lowerRight.x, &lowerRight.y);
    
    for (j=0; j<=numberPartitions; j++)
      counts[j] = 0;

    /* Add the left wall as a partition */
    partitions[0][UPPER].x = upperLeft.x;
    partitions[0][UPPER].y = upperLeft.y;
    partitions[0][LOWER].x = upperLeft.x;
    partitions[0][LOWER].y = lowerRight.y;
    for (j=1; j<=numberPartitions; j++)
    {
      partitions[j][UPPER].y = upperLeft.y;
      partitions[j][LOWER].y = lowerRight.y;
      fscanf(in, "%f %f\n", &partitions[j][UPPER], &partitions[j][LOWER]);
    }
    /* Add the right wall as a partition */
    partitions[j][UPPER].x = lowerRight.x;
    partitions[j][UPPER].y = upperLeft.y;
    partitions[j][LOWER].x = lowerRight.x;
    partitions[j][LOWER].y = lowerRight.y;

    if (debug)
    {
      for (j=0; j<numberPartitions+2; j++)
        printf("%d  (%f,%f) to (%f,%f)\n",
                j, partitions[j][LOWER].x, partitions[j][LOWER].y,
                   partitions[j][UPPER].x, partitions[j][UPPER].y);
    }

    for (j=0; j<numberToys; j++)
    {
      fscanf(in, "%f %f\n", &toy.x, &toy.y);
      addToyToCounts(&toy);
    }

    if (!firstProblem) fprintf(out, "\n");
    else               firstProblem = 0;
  
    for (j=0; j<=numberPartitions; j++)
      fprintf(out, "%d: %d\n", j, counts[j]);
  }
}
