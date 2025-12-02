#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int position = 50;
    FILE *stream = fopen("input.txt", "r");
    char line[6], *result;
    int password = 0;
    int number = 0;

    // Part 1 of puzzle: times it stop at 0
    while ((result = fgets(line, 6, stream)) != NULL) {
        number = atoi(&*(result + 1));
        if (result[0] == 'R') {
            position = position + number;
        } else {
            position = position - number;
        }
        position = position % 100;
        if (position < 0 ) {
            position = 100 + position;
        } else if (position == 0) {
            password++;
        }
    }

    printf("Password is: %i \n", password);

    if (fclose(stream))
        perror("fclose error");
    return 0;
}
