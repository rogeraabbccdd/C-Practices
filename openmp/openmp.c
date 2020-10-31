#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
  #pragma omp parallel 
  {
    #pragma omp critical 
    {
      printf("Hello world from %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
  }

  return 0;
}
