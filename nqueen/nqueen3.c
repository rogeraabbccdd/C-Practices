/******************************************************************/
/* */
/* Program: queens2.c */
/* */
/* Description: */
/* */
/* This program finds all the possible ways that N queens can */
/* be placed on an NxN chessboard so that the queens cannot */
/* capture one another. The code makes no attemt to */
/* eliminate symmetrical solutions, so the number of solutions */
/* reported will always be higher than the actual number of */
/* distinct solutions. */
/* */
/* */
/* */
/* */
/* *****/
/* Benchmark */
/* ========= */
/* */
/* The test was run on a Intel Celeron (Tualatin core) computer */
/* with 256 kbyte cache memory and 512 Mbyte primary memory. */
/* The operating system was Red Hat 7.2 Linux. Compiler tested */
/* was GNU GCC 2.96 (gcc) for Linux. Under Windows XP the compiler */
/* GNU DJGPP 3.0.4 (gcc, djgpp) for DOS was used. */
/* */
/* Numbers tested: */
/* --------------- */
/* */
/* na = 12 */
/* */
/* nb = 14 */
/* */
/* Results: */
/* -------- */
/* */
/* n: Computer: CPU-time (s): Compiler options: */
/* ================================================================ */
/* */
/* na Celeron 1200 MHz 0.71 gcc -O3 */
/* na Celeron 1200 MHz 0.60 gcc -O2 (djgpp) */
/* */
/* nb Celeron 1200 MHz 29.45 gcc -O3 */
/* nb Celeron 1200 MHz 27.69 gcc -O2 (djgpp) */
/* */
/* */
/* *****/
/* */
/* Old benchmark */
/* ============= */
/* */
/* n=12 */
/* */
/* Computer: CPU-time (s): Compilation: */
/* */
/* Pentium 180 MHz 4.31 gcc -O3 */
/* */
/******************************************************************/
/**********************************************************************
**********/
/*
*/
/* Notice
*/
/* ======
*/
/*
*/
/* I make no warranties that this program is (1) free of errors, (2) consistent
*/
/* with any standard merchantability, or (3) meeting the requirements of
a */
/* particular application. This software shall not, partly or as a whole,
*/
/* participate in a process, whose outcome can result in injury to a person
or */
/* loss of property. It is solely designed for analytical work. Permission
to */
/* use, copy and distribute is hereby granted without fee, providing that
the */
/* header above including this notice appears in all copies.
*/
/*
*/
/*
*/
/**********************************************************************
**********/
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
