#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

void partOne() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int totalSum = 0;
    int a, b, c, d;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        sscanf(buffer, "%u-%u,%u-%u", &a, &b, &c, &d);

        if ((a <= c && b >= d) || (c <= a && d >= b)) {
            totalSum++;
        }
    }

    printf("Part One: %d\n", totalSum);

    fclose(pFile);
}

void partTwo() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int totalSum = 0;
    int a, b, c, d;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        sscanf(buffer, "%u-%u,%u-%u", &a, &b, &c, &d);

        if (!((b < c) || (a > d))) {
            totalSum++;
        }
    }

    printf("Part Two: %d\n", totalSum);

    fclose(pFile);
}

int main() {
    partOne();

    partTwo();

    return 0;
}