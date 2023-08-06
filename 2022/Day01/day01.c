#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 300
#define MAX_LENGTH 64

void partOne() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    char lines[MAX_LINES][MAX_LENGTH];

    int maxSum = 0;
    int currentSum = 0;

    if(pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        if (buffer[0] != '\n') {
            currentSum += atoi(buffer);
            continue;
        }

        maxSum = (currentSum > maxSum) ? currentSum : maxSum;
        currentSum = 0;
    }

    printf("Part One: %d\n", maxSum);

    fclose(pFile);
}

void partTwo() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    char lines[MAX_LINES][MAX_LENGTH];

    int firstSum = 0;
    int secondSum = 0;
    int thirdSum = 0;
    int currentSum = 0;

    if(pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        if (buffer[0] != '\n') {
            currentSum += atoi(buffer);
            continue;
        }

        if (currentSum > firstSum) {
            thirdSum = secondSum;
            secondSum = firstSum;
            firstSum = currentSum;
        } else if(currentSum > secondSum) {
            thirdSum = secondSum;
            secondSum = currentSum;
        } else if(currentSum > thirdSum) {
            thirdSum = currentSum;
        }

        currentSum = 0;
    }

    int totalSum = firstSum + secondSum + thirdSum;
    printf("Part Two: %d\n", totalSum);

    fclose(pFile);
}

int main() {
    partOne();

    partTwo();

    return 0;
}