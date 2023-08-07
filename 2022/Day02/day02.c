#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10

void partOne() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int totalSum = 0;

    if(pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        char theirMove = buffer[0];
        char myMove = buffer[2];

        switch(myMove) {
            case 'X':
                totalSum += theirMove == 'A' ? 4 : theirMove == 'B' ? 1 : 7;
                break;
            case 'Y':
                totalSum += theirMove == 'A' ? 8 : theirMove == 'B' ? 5 : 2;
                break;
            case 'Z':
                totalSum += theirMove == 'A' ? 3 : theirMove == 'B' ? 9 : 6;
                break;
            default:
                break;
        }
    }

    printf("Part One: %d\n", totalSum);

    fclose(pFile);
}

void partTwo() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int totalSum = 0;

    if(pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        char theirMove = buffer[0];
        char myMove = buffer[2];

        switch(theirMove) {
            case 'A':
                totalSum += myMove == 'X' ? 3 : myMove == 'Y' ? 4 : 8;
                break;
            case 'B':
                totalSum += myMove == 'X' ? 1 : myMove == 'Y' ? 5 : 9;
                break;
            case 'C':
                totalSum += myMove == 'X' ? 2 : myMove == 'Y' ? 6 : 7;
                break;
            default:
                break;
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