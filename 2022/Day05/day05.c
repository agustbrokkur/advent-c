#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 50
#define STRING_LENGTH 100

typedef struct {
    char *string;
    int length;
} Array;

void freeLinesMemory(Array *array, int numLines) {
    for (int i = 0; i < numLines; i++) {
        free(array[i].string);
    }

    free(array);
}

void partOne() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int arrayCount;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        return;
    } 

    fgets(buffer, MAX_LENGTH, pFile);
    arrayCount = (int)ceil(strlen(buffer)/4.0f);
    rewind(pFile);
    
    Array *towers = (Array*)malloc(arrayCount * sizeof(Array));
    for (int i = 0; i < arrayCount; i++) {
        towers[i].length = 0;
        towers[i].string = (char*)malloc(STRING_LENGTH * sizeof(char));
    }

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        if (buffer[1] == '1') {
            fgets(buffer, MAX_LENGTH, pFile);
            break;
        }

        int count = 0;
        buffer[strcspn(buffer, "\n")] = '\0';
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (i % 4 == 1) {
                if (buffer[i] != ' ') {
                    for (int j = towers[count].length; j > 0; j--) {
                        towers[count].string[j] = towers[count].string[j - 1];
                    }
                    int newLength = towers[count].length + 1;
                    towers[count].string[newLength] = '\0';
                    towers[count].string[0] = buffer[i];
                    towers[count].length = newLength;
                }
                count++;
            }
        }
    }

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        int moves, posA, posB;
        sscanf(buffer, "move %d from %d to %d", &moves, &posA, &posB);
        posA--;
        posB--;

        for (int i = 0; i < moves; i++) {
            towers[posB].string[towers[posB].length + i] = towers[posA].string[towers[posA].length - i - 1];
        }
        towers[posB].length += moves;
        towers[posB].string[towers[posB].length] = '\0';
        towers[posA].length -= moves;
        towers[posA].string[towers[posA].length] = '\0';
    }

    fclose(pFile);

    printf("Part One: ");
    for (int i = 0; i < arrayCount; i++) {
        printf("%c", towers[i].string[towers[i].length - 1]);
    }
    printf("\n");

    freeLinesMemory(towers, arrayCount);
}

void partTwo() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int arrayCount;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        return;
    } 

    fgets(buffer, MAX_LENGTH, pFile);
    arrayCount = (int)ceil(strlen(buffer)/4.0f);
    rewind(pFile);
    
    Array *towers = (Array*)malloc(arrayCount * sizeof(Array));
    for (int i = 0; i < arrayCount; i++) {
        towers[i].length = 0;
        towers[i].string = (char*)malloc(STRING_LENGTH * sizeof(char));
    }

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        if (buffer[1] == '1') {
            fgets(buffer, MAX_LENGTH, pFile);
            break;
        }

        int count = 0;
        buffer[strcspn(buffer, "\n")] = '\0';
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (i % 4 == 1) {
                if (buffer[i] != ' ') {
                    for (int j = towers[count].length; j > 0; j--) {
                        towers[count].string[j] = towers[count].string[j - 1];
                    }
                    int newLength = towers[count].length + 1;
                    towers[count].string[newLength] = '\0';
                    towers[count].string[0] = buffer[i];
                    towers[count].length = newLength;
                }
                count++;
            }
        }
    }

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        int moves, posA, posB;
        sscanf(buffer, "move %d from %d to %d", &moves, &posA, &posB);
        posA--;
        posB--;
        
        for (int i = 0; i < moves; i++) {
            towers[posB].string[towers[posB].length + i] = towers[posA].string[towers[posA].length + i - moves];
        }
        towers[posB].length += moves;
        towers[posB].string[towers[posB].length] = '\0';
        towers[posA].length -= moves;
        towers[posA].string[towers[posA].length] = '\0';
    }

    fclose(pFile);

    printf("Part Two: ");
    for (int i = 0; i < arrayCount; i++) {
        printf("%c", towers[i].string[towers[i].length - 1]);
    }
    printf("\n");

    freeLinesMemory(towers, arrayCount);
}

int main() {
    partOne();

    partTwo();

    return 0;
}