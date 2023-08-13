#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 4200

void setStartingSignal(char *signal, char* buffer, int signalLength, int* lastDuplicate) {
    for (int i = 0; i < signalLength; i++) {
        signal[i] = buffer[i];
        for (int j = i - 1; j >= 0; j--) {
            if (signal[i] == signal[j]) {
                *lastDuplicate = j;
            }
        }
    }
    signal[signalLength] = '\0';
}

void updateSignal(char *signal, int lastSignalChar, char currentChar) {
    for (int j = 0; j < lastSignalChar; j++) {
        signal[j] = signal[j + 1];
    }
    signal[lastSignalChar] = currentChar;
}

void checkAndUpdateLastDuplicate(char *signal, int *lastDuplicate, int position, int lastSignalChar, char currentChar) {
    for (int i = lastSignalChar - 1; i >= 0; i--) {
        if (currentChar == signal[i]) {
            int newDuplicate = position - ((lastSignalChar) - i);
            if (newDuplicate > *lastDuplicate) {
                *lastDuplicate = newDuplicate;
            }
        }
    }
}

void genericSolution(int signalLength) {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    char *signal = (char *)malloc(sizeof(char) * (signalLength + 1));
    int location = 0;
    int lastDuplicate = 0;
    int lastSignalChar = signalLength - 1;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        return;
    } 

    fgets(buffer, MAX_LENGTH, pFile);

    setStartingSignal(signal, buffer, signalLength, &lastDuplicate);

    for (int i = signalLength; i < MAX_LENGTH; i++) {
        char currentChar = buffer[i];
        
        updateSignal(signal, lastSignalChar, currentChar);

        checkAndUpdateLastDuplicate(signal, &lastDuplicate, i, lastSignalChar, currentChar);

        if ((lastDuplicate + signalLength) - 1 < i) {
            location = i + 1;
            break;
        }
    }

    fclose(pFile);

    printf("Solution for length of %d is: %d - %s\n", signalLength, location, signal);
    free(signal);
}



int main() {
    genericSolution(4);
    genericSolution(14);

    return 0;
}