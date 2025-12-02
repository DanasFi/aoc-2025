#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int previous_position = 50;
    int position = 50;
    FILE *stream = fopen("input.txt", "r");
    char line[6], *result;
    int password = 0;
    int number = 0;

    while ((result = fgets(line, 6, stream)) != NULL) {
        number = atoi(&*(result + 1));
        // Add the full circles it makes
        password = password + (number / 100);
        // Add the rest of the moves
        number = number % 100;
        if (result[0] == 'R') {
            position = position + number;
        } else {
            position = position - number;
        }

        if ((position <= 0 || position > 99) && previous_position != 0) {
            password++;
        }
        if (position < 0) {
            position = 100 + position;
        } else if (position > 99) {
            position = position % 100;
        }
        previous_position = position;
    }

    printf("Password for 0x434C49434B is: %i \n", password);


    if (fclose(stream))
        perror("fclose error");
    return 0;
}
