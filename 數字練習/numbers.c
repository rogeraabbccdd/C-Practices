#include <stdio.h>
#include <stdlib.h>

int sum(int number1, int number2);
int multi(int number1, int number2);
int gcd(int number1, int number2);
int lcm(int number1, int number2);
int* odd(int number1, int number2, int *sz);
int* even(int number1, int number2, int *sz);

int main() {
  int number1;
  int number2;

  // get user inputs
  printf("Enter number 1: \n");
  scanf("%d", &number1);
  printf("Enter number 2: \n");
  scanf("%d", &number2);

  // first question
  printf("Answer 1: %d\n", sum(number1, number2));

  // second question
  printf("Answer 2: %d\n", multi(number1, number2));

  // third queston
  printf("Answer 3: %d\n", gcd(number1, number2));

  // fourth queston
  printf("Answer 4: %d\n", lcm(number1, number2));

  // fifth queston
  int size = 0;
  int *odds = odd(number1, number2, &size);
  printf("Answer 5: \n");
  for(int i=0;i<size;i++) {
    printf("%d\n", odds[i]);
  }

  // sixth queston
  int *evens = even(number1, number2, &size);
  printf("Answer 6: \n");
  for(int i=0;i<size;i++) {
    printf("%d\n", evens[i]);
  }

  return 0;
}

int sum(int number1, int number2) {
  int result = 0;
  int  start =  (number1 <= number2) ? number1 : number2;
  int end =  (number1 >= number2) ? number1 : number2;
  for(int i = start; i <= end; i++) {
    result += i;
  }
  return result;
}

int multi(int number1, int number2) {
  int result = 1;
  int  start =  (number1 <= number2) ? number1 : number2;
  int end =  (number1 >= number2) ? number1 : number2;
  for(int i = start; i <= end; i++) {
    result *= i;
  }
  return result;
}

int gcd(int number1, int number2) {
  if(number1 == 0 || number2 == 0) {
    return 0;
  }
  while( number1 > 0 && number2 > 0 ) {
    if(number1 > number2) number1 = number1 % number2;
    else  number2 = number2 % number1;
  }
  return number1 == 0 ? number2 : number1;
}

int lcm(int number1, int number2) {
  int result = (number1 > number2) ? number1 : number2;
  while (1) {
    if (result % number1 == 0 && result % number2 == 0) {
      break;
    }
    result++;
  }
  return result;
}

int* odd(int number1, int number2, int *sz) {
  int *result;

  int start = (number1 <= number2) ? number1 : number2;
  // if start is even, start at start + 1
  start += !(start % 2);
  int end = (number1 >= number2) ? number1 : number2;
  // if end is even, end at end - 1
  end -= !(end % 2);

  // array size
  *sz = (int) (end - start) / 2 + 1;
  result = malloc(*sz*sizeof(int));

  for (int i = 0; start <= end; ++i, start += 2) {
    result[i] = start;
  }
  return result;
}

int* even(int number1, int number2, int *sz) {
  int *result;

  int start = (number1 <= number2) ? number1 : number2;
  // if start is odd, start at start + 1
  start += start % 2;
  int end = (number1 >= number2) ? number1 : number2;
  // if end is odd end, at end - 1
  end -= end % 2;

  // array size
  *sz = (end - start) / 2 + 1;
  result = malloc(*sz*sizeof(int));

  for (int i = 0; start <= end; ++i, start += 2) {
    result[i] = start;
  }
  return result;
}
