#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SEQUENCE_ARRAY_SIZE 2

int* get_possible_digit_sequenece(int digits) {
  int* array = (int*)malloc(SEQUENCE_ARRAY_SIZE * sizeof(int));
  for (int i = 0; i < SEQUENCE_ARRAY_SIZE; i++) {
    array[i] = 0;
  }
  if (digits > 10) {
    printf("ERROR, trying to pass more than 10 digit number \n");
    return array;
  }

  switch (digits) {
    case 4:
      array[0] = 2;
      break;
    case 6:
      array[0] = 2;
      array[1] = 3;
      break;
    case 8:
      array[0] = 4;
      break;
    case 9:
      array[0] = 3;
      break;
    case 10:
      array[0] = 2;
      array[1] = 5;
      break;
    default:
      array[0] = 1;
  }

  return array;
}

int get_digits(long long number) {
  int digits = 1;
  long long remaining = number;
  while (remaining / 10 != 0) {
    remaining /= 10;
    digits++;
  }

  return digits;
}


long long find_sequence_sum(long long starting_sequence, long long ending_sequence) {
  printf("looking in sequence %lli - %lli \n",starting_sequence, ending_sequence);
  long long sum = 0;
  long long invalid_ids_found[1000] = {0};
  int invalid_id_curr_idx = 0;

  int first_number_digits = get_digits(starting_sequence); 
  if (first_number_digits == 1) {
    return 0;
  }
  int* possible_sequence_digits = get_possible_digit_sequenece(first_number_digits);
  long curr_number = 0;

  for (int i= 0; i < SEQUENCE_ARRAY_SIZE; i++) {
    if (possible_sequence_digits[i] == 0) {
      break;
    }
      int ms_part = starting_sequence / pow(10, first_number_digits - possible_sequence_digits[i]);
    while (1) {
      curr_number = 0;
      // printf("Repeating sequence: %i \n", ms_part);
      if (ms_part > pow(10, possible_sequence_digits[i])) {
        break;
      }

      // make number to check
      for (int j = 0; j < (first_number_digits / possible_sequence_digits[i]); j++) {
        curr_number += ms_part * pow(10, possible_sequence_digits[i] * j);
      }

      // check if curr_number is in range
      if (curr_number >= starting_sequence && curr_number <= ending_sequence ) {
        // check if the number is already in the sequence
        int repeated_number = 0;
        for (int k = 0; k < invalid_id_curr_idx; k++) {
          if (curr_number == invalid_ids_found[k]) {
            repeated_number = 1;
            break;
          }
        }
        if (repeated_number) {
          // printf("Found repeated number %li \n", curr_number);
        } else {
          invalid_ids_found[invalid_id_curr_idx] = curr_number;
          invalid_id_curr_idx++;
          printf("Found invalid id %li \n", curr_number);
        }
      } else if (curr_number > ending_sequence){
        break;
      }
    ms_part += 1;
    }
  }
  free(possible_sequence_digits);
  for (int i = 0; i < invalid_id_curr_idx; i++) {
    sum += invalid_ids_found[i];
  }
  return sum;
} 

long long main_find_sequence_sum(long long starting_sequence, long long ending_sequence) {
  printf("\n");
  printf("Finding invalid ids from %lli to %lli \n", starting_sequence, ending_sequence);
  int first_number_digits = get_digits(starting_sequence);
  int last_number_digits = get_digits(ending_sequence); 
  
  long long sequence_sum = 0;
  if (first_number_digits == last_number_digits) {
    sequence_sum = find_sequence_sum(starting_sequence, ending_sequence);
  } else if (last_number_digits > first_number_digits) {
    int difference_digits = last_number_digits - first_number_digits;
    sequence_sum += find_sequence_sum(starting_sequence, pow(10, first_number_digits));
    for (int i = 0; i < difference_digits; i++) {
      // get upper limit
      long long upper_limit = 0;
      if (powl(10, first_number_digits + i + 1) < ending_sequence) {
        upper_limit = powl(10, first_number_digits);
      } else {
        upper_limit = ending_sequence;
      }
      sequence_sum += find_sequence_sum(pow(10, first_number_digits + i), upper_limit); 
    }
  }
  printf("Adding %lli \n", sequence_sum);
  return sequence_sum;
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
      sum_of_valid_ids += main_find_sequence_sum(first, second);
      // printf("Current sum of invalids ids %lli \n", sum_of_valid_ids);
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
