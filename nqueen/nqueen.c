#include <stdio.h>
//#include<conio.h>
#include <stdlib.h>
#include <time.h>

int queen[25], sols;
int place(int, int);
int abs(int);

void n_queens(int k, int n)
{
  int r, w, i, j;
  static int l = 1;
  for (i = 1; i <= n; i++)
  {
    if (place(k, i) == 1)
    {
      queen[k] = i;
      if (k == n)
      {
        if (l == 1)
        {
          //printf("Pictorial solution to %d QUEENS PROBLEM:\n",n);
          l++;
          for (r = 1; r <= n; r++)
          {
            for (w = 1; w <= n; w++)
            {
              if (w != queen[r])
                printf(" *");
              else
                printf(" Q");
            }
            printf("\n");
          }
          printf("Other solutions:\n");
        }
        for (j = 1; j <= n; j++) //printf(" %d",queen[j]);
          //printf("\n");
          sols++;
      }
      else
        n_queens(k + 1, n);
    }
  }
}

int place(int k, int i)
{
  int j;
  for (j = 1; j < k; j++)
  {
    if ((queen[j] == i) || ((abs(queen[j] - i)) == (abs(j - k))))
    {
      return 0;
    }
  }
  return 1;
}

int abs(x)
{
  if (x < 0)
    return (-x);
  else
    return x;
}

void main()
{
  int num;
  clock_t start, stop;

  // clrscr();
  printf("\t\t\t\tN - QUEENS PROBLEM\n\n");
  printf("Enter the no. of queens: ");
  scanf("%d", &num);

  if (num > 24)
  {
    printf("Maximum of Queen 24 only: you have exceeded the limit\n");
    exit(0);
  }

  printf("\n\tAll possible placements of %d queens\n\n", num);

  start = clock();

  n_queens(1, num);

  stop = clock();
  
  printf("Amount of time it took to solve the puzzle %lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
  printf("\nTotal number of solutions: %d", sols);
  //getch();
}