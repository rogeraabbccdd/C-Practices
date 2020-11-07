#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS 5000

int main() {
  double start_time, run_time, sequential_time, parallel_time;
  int number[NUMBERS] = {0};
  

  // Generate numbers
  printf("Generating %d random numbers...", NUMBERS);

  #pragma omp parallel for
  for(int i = 0; i < NUMBERS; i++) {
    number[i] = rand();
  }

  printf("done.\n");

  // Sequntial
  printf("Sequntial sorting numbers...");

  start_time = omp_get_wtime();

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
  run_time = omp_get_wtime() - start_time;
  sequential_time = run_time;

  printf("done.\n");

  // Parallel
  start_time = omp_get_wtime();

  printf("Parallel sorting numbers...");

  int i, j, temp = 0;
  // static speedup: 6.x
  // runtime speedup: > 7.5
  #pragma omp parallel for schedule(runtime) private(temp, i, j) shared(number)
  for(i = 0; i < NUMBERS; i++) {
    for(j = i; j < NUMBERS; j++) {
      if(number[j] < number[i]) {
        temp = number[j];
        number[j] = number[i];
        number[i] = temp;
      }
    }
  }

  run_time = omp_get_wtime() - start_time;
  parallel_time = run_time;

  printf("done.\n");

  // Print Results
  printf("The Sequential time is %f\n", sequential_time);
  printf("The Parallel time is %f\n", parallel_time);
  printf("The speedup of the program is %f\n", sequential_time / parallel_time);

  printf("Sorted numbers:\n");
  for(int i = 0; i < NUMBERS; i++ ) {
    printf("%d ", number[i]);
  }

  return 0;
}