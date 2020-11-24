#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

double timetic = (double)(CLOCKS_PER_SEC);

void printboard(char *ss, int *d, int n)
{
  int i, j, k, n2;

  n2 = 2 * n;

  for (i = 0; i < n2; i = i + 2)
  {
    ss[i] = '-';
    ss[i + 1] = ' ';
  }

  ss[n2] = '\0';

  for (j = 1; j <= n; j++)
  {
    k = 2 * (d[j] - 1);
    ss[k] = 'Q';
    printf("%s\n", ss);
    ss[k] = '-';
  }
}

int main(int argc, char *argv[]) 
{
  int i, k, s, c, n, nn, n1;
  double ftime;
  int *d;
  char *ss;

  clock_t time1, timediff;

  if (argc != 3)
  {
    printf("Usage: %s n1i nmaxi\n", argv[0]);
    exit(0);
  }

  n1 = atoi(argv[1]);
  nn = atoi(argv[2]);

  if (n1 < 4)
  {
    n1 = 4;
  }

  if (nn < 4)
  {
    nn = 4;
  }

  d = (int *)calloc(nn + 1, sizeof(int));
  ss = (char *)calloc(2 * nn + 3, sizeof(char));

  for (n = n1; n <= nn; n++)
  {
    s = 0;
    i = 2;
    d[1] = 1;
    d[2] = 1;
    time1 = clock();

    while (i > 0)
    {
      d[i]++;
      k = 0;
      do
      {
        k++;
        c = d[i] - d[k];
      } while ((c != 0) && (abs(c) != abs(i - k)));

      if ((i == n) && (k == i))
      {
        s++;
        // printboard(ss, d, n);
      }
      else if (k == i)
      {
        i++;
      } /* if */
      while (d[i] == n)
      {
        d[i] = 0;
        i--;
      }
    }

    timediff = clock() - time1;
    ftime = (double)(timediff) / timetic;
    printf("%6d %10d %10.2f\n", n, s, ftime);
  }
}
