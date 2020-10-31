#include <stdio.h>
#include <time.h>

long long num_steps = 1000000;
double step;

int main(int argc, char* argv[]){
  clock_t start, stop;
  double x, pi, sum=0.0;
  int i;step = 1./(double)num_steps;

  start = clock();

  for (i=0; i<num_steps; i++){
    x = (i + .5)*step;
    sum = sum + 4.0/(1.+ x*x);
  }

  pi = sum*step;
  stop = clock();

  printf("The number of steps ran is %lld\n", num_steps);
  printf("The value of PI is %15.12f\n",pi);
  printf("The time to calculate PI was %f seconds\n",((double)(stop -start)/ CLOCKS_PER_SEC ));
  
  return 0;
}
