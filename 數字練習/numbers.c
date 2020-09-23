#include <stdio.h>

int sum(int number1, int number2);
int multi(int number1, int number2);
int gcd(int number1, int number2);

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
  int result;
  for(int i = 1; i <= number1 && i <= number2; i++) {
    if(number1 % i == 0 && number2 % i == 0)  result = i;
  }
  return result;
}
