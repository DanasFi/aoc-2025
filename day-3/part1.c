
#include <stdio.h>
#include <stdlib.h>

int get_max_joltage(char *sequence) {
  int sequence_length = 0;
  int k = 0;
  // printf("Getting max joltage of %s", sequence);
  int max_joltage = 0;
  int i = 1;
  char max_first_digit_char = '0';
  int max_first_digit_pos = 0;
  char first_digit[2] = {'\0'};
  while (!(sequence[i] == '\0' || sequence[i] == '\n' || sequence[i] == ' ')) {
    char curr_char = sequence[i-1];
    // printf("char is : %c \n", curr_char);
    if (curr_char > max_first_digit_char) {
      max_first_digit_pos = i-1;
      max_first_digit_char = curr_char;
    }
    i++;
  }
  first_digit[0] = max_first_digit_char;
  max_joltage += 10 * atoi(first_digit);
  
  char max_second_digit_char = '0';
  int max_second_digit_pos = 0;
  int j = max_first_digit_pos + 1;
  while (!(sequence[j] == '\0' || sequence[j] == '\n' || sequence[j] == ' ')) {
    char curr_char = sequence[j];
    if (curr_char > max_second_digit_char) {
      max_second_digit_pos = j;
      max_second_digit_char = curr_char;
    }
    j++;
  }

  first_digit[0] = max_second_digit_char;
  max_joltage += atoi(first_digit);
  // printf(" Max joltage is %i \n", max_joltage);
  return max_joltage;  
}

int main() {
  FILE *input = fopen("input.txt", "r");
  char buff[200], *result;
  int sum_of_max_joltage = 0;
  int lines = 0;
  while((result = fgets(buff, sizeof(buff), input)) != NULL) {
    // printf("%s", buff);
    int max_joltage = get_max_joltage(buff);
    sum_of_max_joltage += get_max_joltage(buff);
    printf("From %s getting joltage of %i \n", buff, max_joltage);
    lines++;
  }
  printf("Sum of joltage is: %i\n", sum_of_max_joltage);
}
