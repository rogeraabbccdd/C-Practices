#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS 5000

int main() {
  clock_t start, stop;
  int number[NUMBERS] = {0};
  

  // Generate numbers
  start = clock();
  
  printf("Generating random numbers...\n");

  #pragma omp parallel for
  for(int i = 0; i < NUMBERS; i++) {
    number[i] = rand();
  }

  stop = clock();

  printf("The time to generate numbers was %f seconds\n",((double)(stop -start)/ CLOCKS_PER_SEC ));

  // Sort numbers
  start = clock();
  printf("Sorting numbers...\n");
  #pragma omp parallel for
  for(int i = 0; i < NUMBERS; i++) {
    int temp = 0;
    for(int j = i; j < NUMBERS; j++) {
      if(number[j] < number[i]) {
        temp = number[j];
        number[j] = number[i];
        number[i] = temp;
      }
    }
  }
  stop = clock();

  printf("The time to sort numbers was %f seconds\n",((double)(stop -start)/ CLOCKS_PER_SEC ));

  printf("Sorted numbers:\n");
  #pragma omp parallel for
  for(int i = 0; i < NUMBERS; i++ ) {
    printf("%d ", number[i]);
  }

  return 0;
}