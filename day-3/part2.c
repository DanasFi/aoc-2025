
#include <stdio.h>
#include <stdlib.h>

#define DIGITS_TO_TURN 12

int get_sequence_length(char *sequence) {
  int i = 0;
  while (!(sequence[i] == '\0' || sequence[i] == '\n' || sequence[i] == ' ')) {
    i++;
  }
  return i;
}

long long get_max_joltage(char *sequence, int sequence_length) {
  long long max_joltage = 0;
  char max_digit = '0';
  char max_digit_pos = 0;
  char number[13] = {'\0'};
  int assigning_idx = 0;
  int starting_idx = 0;
  int limit_idx = DIGITS_TO_TURN - 1;
  while(assigning_idx < 12) {
    // printf("starting_idx: %i, limit_idx: %i, assigning idx : %i, number: %s \n",starting_idx, limit_idx, assigning_idx, number);
    for (int i = starting_idx; i < sequence_length - limit_idx; i++) {
      if (sequence[i] > max_digit) {
        max_digit = sequence[i];
        max_digit_pos = i;
        if (sequence[i] == '9') {
          break;
        }
      }      
    }

    // assign value
    number[assigning_idx] = max_digit;
    starting_idx = max_digit_pos + 1;
    limit_idx--;
    max_digit = '0';
    assigning_idx++;
  }

  max_joltage = atoll(number);
  printf("Max joltage: %lli\n", max_joltage);
  return max_joltage;  
}

int main() {
  FILE *input = fopen("input.txt", "r");
  char buff[200], *result;
  long long sum_of_max_joltage = 0;
  int lines = 0;
  result = fgets(buff, sizeof(buff), input);
  int sequence_length = get_sequence_length(result);
  do {
    sum_of_max_joltage += get_max_joltage(result, sequence_length);
    result = fgets(buff, sizeof(buff), input); 
    
  } while (result != NULL);
  printf("Sum of joltage is: %lli\n", sum_of_max_joltage);
}
