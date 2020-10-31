#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
  int nthreads, tid;
  omp_set_num_threads(16);

  #pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    printf("Hello from thread %d\n", tid);
  }

  return 0;
}