#define TEAM    0   /* Your team # here */
#define PROBLEM 3   /* The problem # here */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

FILE *in=0;
FILE *out=0;
void solve_problem();
int  debug = 0;

/*-----------------------------------------------------*/
int main(int argc, char *argv[])
{
    char inputFilename[64];
    char outputFilename[64];
    int  teamNumber = TEAM;
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

/*-----------------------------------------------------*/
void printMatrix(char matrix[100][100], int size)
{
  int j, k;
  
  for (j=0; j<size; j++)
  {
    for (k=0; k<size; k++)
      printf("%c ", matrix[j][k]);
    printf("\n");
  }
}
/*-----------------------------------------------------*/
void shake(char matrix[100][100], int size)
{
  int   r, c;
  char  temp;
  
  /* odd columns - 0, 2, 4, etc shifted up */
  for (c=0; c<size; c+=2)
  {
    temp = matrix[0][c]; 
    for (r=0; r<size-1; r++)
      matrix[r][c] = matrix[r+1][c];
    matrix[size-1][c] = temp;
  }
  
  /* even columns - 1, 3, 5, 7, etc. shifted down */
  for (c=1; c<size; c+=2)
  {
    temp = matrix[size-1][c]; 
    for (r=size-1; r>0; r--)
      matrix[r][c] = matrix[r-1][c];
    matrix[0][c] = temp;
  }
  
  if (debug)
  {
    printf("After shake\n");
    printMatrix(matrix, size);
  }
}
/*-----------------------------------------------------*/
void rattle(char matrix[100][100], int size)
{
  int   r, c;
  char  temp;
  
  /* odd rows - 0, 2, 4, etc shifted right */
  for (r=0; r<size; r+=2)
  {
    temp = matrix[r][size-1]; 
    for (c=size-1; c>0; c--)
      matrix[r][c] = matrix[r][c-1];
    matrix[r][0] = temp;
  }
  
  /* even rows - 1, 3, 5, 7, etc. shifted left */
  for (r=1; r<size; r+=2)
  {
    temp = matrix[r][0]; 
    for (c=0; c<size-1; c++)
      matrix[r][c] = matrix[r][c+1];
    matrix[r][size-1] = temp;
  }
  
  if (debug)
  {
    printf("After rattle\n");
    printMatrix(matrix, size);
  }
}
/*-----------------------------------------------------*/
void roll(char matrix[100][100], int size)
{
  int   r, c, loop;
  char  temp1, temp2, temp3;
  
  /* odd loops - 0, 2, 4, etc rotated right */
  for (loop=0; loop<size/2; loop+= 2)
  {
    /* top row of loop */
    r = loop;
    temp1 = matrix[loop][size-1-loop];
    for (c=size-1-loop; c>loop; c--)
      matrix[r][c] = matrix[r][c-1];

    /* right column of loop */
    c = size-1-loop;
    temp2 = matrix[c][c];
    for (r=c; r>loop; r--)
      matrix[r][c] = matrix[r-1][c];
    matrix[loop+1][c] = temp1;

    /* bottom row of loop */
    r = size-1-loop;
    temp3 = matrix[r][loop];
    for (c=loop; c<r-1; c++)
      matrix[r][c] = matrix[r][c+1];
    matrix[r][size-1-loop-1] = temp2;

    /* left column of loop */
    c = loop;
    for (r=loop; r<size-1-loop-1; r++)
      matrix[r][c] = matrix[r+1][c];
    matrix[size-1-loop-1][c] = temp3;
  }
  
  /* even loops - 1, 3, 5, 7, etc. rotated left */
  for (loop=1; loop<size/2; loop+= 2)
  {
    /* top row of loop */
    r = loop;
    temp1 = matrix[r][r];
    for (c=loop; c<size-1-loop; c++)
      matrix[r][c] = matrix[r][c+1];

    /* left column of loop */
    c = loop;
    temp2 = matrix[size-1-loop][c];
    for (r=size-1-loop; r>loop; r--)
      matrix[r][c] = matrix[r-1][c];
    matrix[loop+1][c] = temp1;

    /* bottom row of loop */
    r = size-1-loop;
    temp3 = matrix[r][r];
    for (c=size-1-loop; c>loop; c--)
      matrix[r][c] = matrix[r][c-1];
    matrix[r][loop+1] = temp2;

    /* right column of loop */
    c = size-1-loop;
    for (r=loop; r<size-1-loop; r++)
      matrix[r][c] = matrix[r+1][c];
    matrix[size-1-loop-1][c] = temp3;
  }
  
  if (debug)
  {
    printf("After roll\n");
    printMatrix(matrix, size);
  }
}
/*-----------------------------------------------------*/
void solve_problem()
{
  char    key[81];
  char    message[1001];
  char    matrix[100][100];
  int     size;
  char    extra[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int     j, k, n, m;
  
  while (fscanf(in, "%s\n", key) != EOF)
  {
    fgets(message, 1000, in);
    message[strlen(message)-1] = '\0';  /* remove the new-line on the end of the input */

    if (debug)
    {
      printf("Key = '%s'\n", key);
      printf("Message = '%s'\n", message);
    }

    /* Get the matrix size. */
    sscanf(key, "%2d", &size);
    if (size == 0) size = 100;

    if (debug) printf("Size = %d\n", size);

    /* Put the message into the array */
    n = 0;
    m = 0;
    for (j=0; j<size; j++)
      for (k=0; k<size; k++)
        if (n < strlen(message)) matrix[j][k] = toupper(message[n++]);
        else                     matrix[j][k] = extra[m++ % 26];
  
    if (debug)
    {
      for (j=0; j<size; j++)
      {
        for (k=0; k<size; k++)
          printf("%c ", matrix[j][k]);
        printf("\n");
      }
    }

    /* Perform the shake rattle roll */
    for (j=2; j<strlen(key); j++)
    {
           if (key[j] == 'S') shake(matrix, size);
      else if (key[j] == 'R') rattle(matrix, size);
      else if (key[j] == 'L') roll(matrix, size);
    }

    /* Output the encrypted message */
    for (j=0; j<size; j++)
      for (k=0; k<size; k++)
      {
        if (debug) printf("%c", matrix[j][k]);
        fprintf(out, "%c", matrix[j][k]);
      }
    if (debug) printf("\n");
    fprintf(out, "\n");
  }
}
