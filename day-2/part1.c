#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_sequence_sum(int first_number, int second_number) {
  int sum = 0;
  // get digits
  int digits = 1;
  int remaining = first_number;
  
  for (digits = 1; remaining / 10 == 0; digits++) {
    remaining /= 10;
  }

  if (digits % 2 == 0) {
    // if digits is even, then is possible to get numbers of repeated sequence
    
  }
  
  return 0;
} 
int main() {
  char first_number[20], second_number[20];
  char ch;
  FILE *input = fopen("input.txt", "r");
  int i = 0;
  int assigning_first_number = 0;
  int first, second;
  while ((ch = fgetc(input)) != EOF) {
    if (ch == ',') {
      // continue to next iteration
      printf("Second number is : %s \n", second_number);  
      i = 0;
      first = atoi(first_number);
      second = atoi(second_number);
      // clean array of numbers
      memset(first_number, '\0',sizeof(first_number));
      memset(second_number, '\0',sizeof(second_number));
    } else if (ch == '-') {
      // change to second number
      printf("First number is : %s \n", first_number);
      assigning_first_number = 1;
      i = 0;
    } else {
      if (assigning_first_number == 0) {
        // start adding first number
        first_number[i] = ch;
        i++;
      } else {
        // add to second number
        second_number[i] = ch; 
        i++;
      }
    }
  }
  return 0;
}
