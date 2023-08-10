#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 64
#define HALF_LENGTH 32

void getSubString(char* outputString, char* inputString, int start, int length) {
    const char* subString = inputString + start;
    for (int i = 0; i < length; i++) {
        outputString[i] = subString[i];
    }

    outputString[length] = '\0';
}

int getCharValue(char character) {
    int value = character - 'a';

    if (value < 0) {
        return (character - 'A') + 27;
    }
    return (character - 'a') + 1;
}

char getCommonChar(const char *firstLine, const char *secondLine, const char *thirdLine) {
    for (int i = 0; firstLine[i] != '\0'; i++) {
        for (int j = 0; secondLine[j] != '\0'; j++) {
            if (firstLine[i] == secondLine[j]) {
                for (int k = 0; thirdLine[k] != '\0'; k++) {
                    if(secondLine[j] == thirdLine[k]) {
                        return thirdLine[k];
                    }
                }
            }
        }
    }

    return '\0';
}

void partOne() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int totalSum = 0;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        int lineLength = strlen(buffer);
        int halfLength = lineLength/2;
        char firstHalf[HALF_LENGTH] = "";
        char secondHalf[HALF_LENGTH] = "";

        strncat(firstHalf, buffer, halfLength);
        getSubString(secondHalf, buffer, halfLength, halfLength);
        char commonChar = strpbrk(firstHalf, secondHalf)[0];

        totalSum += getCharValue(commonChar);
    }

    printf("Part One: %d\n", totalSum);

    fclose(pFile);
}

void partTwo() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int totalSum = 0;
    int position = 0;
    char firstLine[MAX_LENGTH] = "";
    char secondLine[MAX_LENGTH] = "";
    char thirdLine[MAX_LENGTH] = "";

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        fclose(pFile);
        return;
    } 

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (position == 0) {
            strcpy(firstLine, buffer);
            position++;
            continue;
        } else if (position == 1) {
            strcpy(secondLine, buffer);
            position++;
            continue;
        } else {
            strcpy(thirdLine, buffer);
            position = 0;
        }

        char commonChar = getCommonChar(firstLine, secondLine, thirdLine);
        totalSum += getCharValue(commonChar);
    }

    printf("Part Two: %d\n", totalSum);

    fclose(pFile);
}

int main() {
    partOne();

    partTwo();

    return 0;
}