#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 6

struct thread_data {
  int number1;
  int number2;
  int size;
  int result;
  int *results;
};

void *sum(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int start = (number1 <= number2) ? number1 : number2;
  int end = (number1 >= number2) ? number1 : number2;
  int result = 0;
  for(int i = start; i <= end; i++) {
    result += i;
  }
  ((struct thread_data*) data) -> result = result;
  pthread_exit(NULL);
}

void *multi(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int result = 1;
  int start =  (number1 <= number2) ? number1 : number2;
  int end =  (number1 >= number2) ? number1 : number2;
  for(int i = start; i <= end; i++) {
    result *= i;
  }
  ((struct thread_data*) data) -> result = result;
  pthread_exit(NULL);
}

void *gcd(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int result = 1;
  for(int i = 1; i <= number1 && i <= number2; i++) {
    if(number1 % i == 0 && number2 % i == 0)  result = i;
  }
  ((struct thread_data*) data) -> result = result;
  pthread_exit(NULL);
}

void *lcm(void* data) {
  int number1 = ((struct thread_data*) data) -> number1;
  int number2 = ((struct thread_data*) data) -> number2;
  int result = (number1 > number2) ? number1 : number2;
  while (1) {
    if (result % number1 == 0 && result % number2 == 0) {
      break;
    }
    result++;
  }
  ((struct thread_data*) data) -> result = result;
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
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(int));

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
  ((struct thread_data*) data) -> results = malloc(((struct thread_data*) data) -> size*sizeof(int));

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
  printf("Answer 1: %d\n", thread_array[0].result);

  // second question
  printf("Answer 2: %d\n", thread_array[1].result);

  // third queston
  printf("Answer 3: %d\n", thread_array[2].result);

  // fourth queston
  printf("Answer 4: %d\n", thread_array[3].result);

  printf("Answer 5: \n");
  for(int i=0;i<thread_array[4].size;i++) {
    printf("%d\n", thread_array[4].results[i]);
  }

  // sixth queston
  printf("Answer 6: \n");
  for(int i=0;i<thread_array[5].size;i++) {
    printf("%d\n", thread_array[5].results[i]);
  }

  pthread_exit(NULL);

  return 0;
}
