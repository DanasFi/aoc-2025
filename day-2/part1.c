#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int get_digits(long long number) {
  int digits = 1;
  long long remaining = number;
  while (remaining / 10 != 0) {
    remaining /= 10;
    digits++;
  }

  return digits;
}

long long find_sequence_sum(long long first_number, long long second_number) {
  printf("Finding invalid ids from %lli to %lli \n", first_number, second_number);
  long long sum = 0;
  // get digits
  int first_number_digits = get_digits(first_number); 
  long curr_number = first_number;

  if (first_number_digits % 2 == 1) {
    
    curr_number = pow(10, first_number_digits);
    first_number_digits += 1;    
  }
  if (first_number_digits % 2 == 0) {
    // if digits is even, then is possible to get numbers of repeated sequence
    long long ms_half = curr_number/ pow(10, first_number_digits / 2);
    long long ls_half = curr_number% (int) pow(10, first_number_digits / 2);

    if (ms_half < ls_half) {
      ms_half += 1;
    }
    
    curr_number = ms_half * pow(10, first_number_digits / 2) + ms_half;
    while ( curr_number <= second_number ) {
      if (curr_number < 0) {
        break;
      }
      sum += curr_number;
      // printf("Invalid id : %i \n", curr_number);
      ms_half += 1;
      curr_number = ms_half * pow(10, first_number_digits / 2) + ms_half;
      if (get_digits(curr_number) % 2 == 1) {
        curr_number = pow (10, first_number_digits + 2);
        first_number_digits += 2;
      }
    }
  }
  // printf("Returning sum of %lu", sum);  
  return sum;
} 
int main() {
  char first_number[20], second_number[20];
  char ch;
  FILE *input = fopen("input.txt", "r");
  int i = 0;
  int assigning_first_number = 0;
  long long first, second;
  long long sum_of_valid_ids = 0;
  while ((ch = fgetc(input)) != EOF) {
    if (ch == ',') {
      // continue to next iteration
      i = 0;
      first = atoll(first_number);
      second = atoll(second_number);
      sum_of_valid_ids += find_sequence_sum(first, second);
      printf("Current sum of invalids ids %lli \n", sum_of_valid_ids);
      // clean array of numbers
      memset(first_number, '\0',sizeof(first_number));
      memset(second_number, '\0',sizeof(second_number));
      assigning_first_number = 0;
    } else if (ch == '-') {
      // change to second number
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

  first = atoi(first_number);
  second = atoi(second_number);
  sum_of_valid_ids += find_sequence_sum(first, second);
  printf("Sum of invalid ids is: %lli \n", sum_of_valid_ids);

  return 0;
}
