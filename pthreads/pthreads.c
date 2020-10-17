#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 6

struct thread_data {
  int number1;
  int number2;
  int size;
  long *results;
};

void *sum(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int start = (number1 <= number2) ? number1 : number2;
  int end = (number1 >= number2) ? number1 : number2;
  long result = 0;
  for(int i = start; i <= end; i++) {
    result += i;
  }
  ((struct thread_data*) data) -> size = (int) 1;
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(long));
  ((struct thread_data*) data) -> results[0] = result;
  pthread_exit(NULL);
}

void *multi(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  long result = 1;
  int start =  (number1 <= number2) ? number1 : number2;
  int end =  (number1 >= number2) ? number1 : number2;
  for(int i = start; i <= end; i++) {
    result *= i;
  }
  ((struct thread_data*) data) -> size = (int) 1;
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(long));
  ((struct thread_data*) data) -> results[0] = result;
  pthread_exit(NULL);
}

void *gcd(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;

  long result = 0;
  if(number1 == 0 || number2 == 0) {
    result = 0;
  }

  while( number1 > 0 && number2 > 0 ) {
    if(number1 > number2) number1 = number1 % number2;
    else  number2 = number2 % number1;
  }

  result = number1 == 0 ? number2 : number1;
  ((struct thread_data*) data) -> size = (int) 1;
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(long));
  ((struct thread_data*) data) -> results[0] = result;
  pthread_exit(NULL);
}

void *lcm(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  long result = (number1 > number2) ? number1 : number2;
  while (1) {
    if (result % number1 == 0 && result % number2 == 0) {
      break;
    }
    result++;
  }
  ((struct thread_data*) data) -> size = (int) 1;
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(long));
  ((struct thread_data*) data) -> results[0] = result;
  pthread_exit(NULL);
}

void *odd(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int start = (number1 <= number2) ? number1 : number2;
  // if start is even, start at start + 1
  start += !(start % 2);
  int end = (number1 >= number2) ? number1 : number2;
  // if end is even, end at end - 1
  end -= !(end % 2);

  // array size
  ((struct thread_data*) data) -> size = (int) (end - start) / 2 + 1;
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(long));

  for (int i = 0; start <= end; ++i, start += 2) {
    ((struct thread_data*) data) -> results[i] = start;
  }
}

void *even(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int start = (number1 <= number2) ? number1 : number2;
  // if start is odd, start at start + 1
  start += start % 2;
  int end = (number1 >= number2) ? number1 : number2;
  // if end is odd end, at end - 1
  end -= end % 2;

  // array size
  ((struct thread_data*) data) -> size = (int) (end - start) / 2 + 1;
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(long));

  for (int i = 0; start <= end; ++i, start += 2) {
    ((struct thread_data*) data) -> results[i] = start;
  }
}

int main() {
  int number1;
  int number2;

  // get user inputs
  printf("Enter number 1: \n");
  scanf("%d", &number1);
  printf("Enter number 2: \n");
  scanf("%d", &number2);

  // threads
  pthread_t threads[NUM_THREADS];
  struct thread_data* thread_array = malloc(NUM_THREADS * sizeof(struct thread_data));

  for(int i=0;i<NUM_THREADS;i++) {
    thread_array[i].number1 = number1;
    thread_array[i].number2 = number2;
  }

  int rc = pthread_create(&threads[0], NULL, sum, (void*) &thread_array[0]); 
  rc = pthread_create(&threads[1], NULL, multi, (void*) &thread_array[1]); 
  rc = pthread_create(&threads[2], NULL, gcd, (void*) &thread_array[2]); 
  rc = pthread_create(&threads[3], NULL, lcm, (void*) &thread_array[3]); 
  rc = pthread_create(&threads[4], NULL, odd, (void*) &thread_array[4]); 
  rc = pthread_create(&threads[5], NULL, even, (void*) &thread_array[5]); 

  // first question
  printf("Sum: %ld\n", thread_array[0].results[0]);

  // second question
  printf("Multi: %ld\n", thread_array[1].results[0]);

  // third queston
  printf("GCD: %ld\n", thread_array[2].results[0]);

  // fourth queston
  printf("LCM: %ld\n", thread_array[3].results[0]);

  printf("Odds: \n");
  for(int i=0;i<thread_array[4].size;i++) {
    printf("%ld\n", thread_array[4].results[i]);
  }

  // sixth queston
  printf("Evens: \n");
  for(int i=0;i<thread_array[5].size;i++) {
    printf("%ld\n", thread_array[5].results[i]);
  }

  pthread_exit(NULL);

  return 0;
}
