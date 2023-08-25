#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 128

void deleteForest(int **forest, int lineCount) {
    for (int i = 0; i < lineCount; i++) {
        free(forest[i]);
    }
    free(forest);
}

int checkNorth(int **forest, int x, int y) {
    for (int north = y - 1; north >= 0; north--) {
        if (forest[north][x] >= forest[y][x]) break;
        if (north == 0) return 1;
    }

    return 0;
}

int checkSouth(int **forest, int x, int y, int lineCount) {
    for (int south = y + 1; south < lineCount; south++) {
        if (forest[south][x] >= forest[y][x]) break;
        if (south == lineCount - 1) return 1;
    }

    return 0;
}

int checkWest(int **forest, int x, int y) {
    for (int west = x - 1; west >= 0; west--) {
        if (forest[y][west] >= forest[y][x]) break;
        if (west == 0) return 1;
    }

    return 0;
}

int checkEast(int **forest, int x, int y, int lineLength) {
    for (int east = x + 1; east < lineLength; east++) {
        if (forest[y][east] >= forest[y][x]) break;
        if (east == lineLength - 1) return 1;
    }

    return 0;
}

int checkDirection(int **forest, int x, int y, int lineCount, int lineLength, char direction) {
    if (direction == 'N') return checkNorth(forest, x, y);
    if (direction == 'S') return checkSouth(forest, x, y, lineCount);
    if (direction == 'W') return checkWest(forest, x, y);
    if (direction == 'E') return checkEast(forest, x, y, lineLength);

    return 0;
}

void solutionOne() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int lineCount = 0;
    int lineLength = 0;
    int **forest = NULL;
    char directions[] = { 'N', 'S', 'W', 'E' };

    fgets(buffer, MAX_LENGTH, pFile);
    buffer[strcspn(buffer, "\n")] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) lineLength++;
    rewind(pFile);

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        lineCount++;
        forest = (int **)realloc(forest, sizeof(int *) * lineCount);
        forest[lineCount - 1] = (int *)malloc(sizeof(int) * lineLength);
        for (int i = 0; i < lineLength; i++) {
            forest[lineCount - 1][i] = buffer[i] - '0';
        }
    }

    fclose(pFile);

    int count = 0;
    for (int y = 0; y < lineCount; y++) {
        for (int x = 0; x< lineLength; x++) {
            if (x == 0 || x == lineLength - 1 || y == 0 || y == lineCount - 1) count++;
            else {
                for (int i = 0; i < 4; i++) {
                    if(checkDirection(forest, x, y, lineCount, lineLength, directions[i])) {
                        count++;
                        break;;
                    }
                }
            }
        }
    }
    printf("%d\n", count);


    deleteForest(forest, lineCount);
}

int scoreNorth(int ** forest, int x, int y) {
    int count = 0;
    for (int north = y - 1; north >= 0; north--) {
        count++;
        if (forest[north][x] >= forest[y][x] || north == 0) return count;
    }

    return count;
}

int scoreSouth(int **forest, int x, int y, int lineCount) {
    int count = 0;
    for (int south = y + 1; south < lineCount; south++) {
        count++;
        if (forest[south][x] >= forest[y][x] || south == lineCount - 1) return count;
    }

    return count;
}

int scorekWest(int **forest, int x, int y) {
    int count = 0;
    for (int west = x - 1; west >= 0; west--) {
        count++;
        if (forest[y][west] >= forest[y][x] || west == 0) return count;
    }

    return count;
}

int scoreEast(int **forest, int x, int y, int lineLength) {
    int count = 0;
    for (int east = x + 1; east < lineLength; east++) {
        count++;
        if (forest[y][east] >= forest[y][x] || east == lineLength - 1) return count;
    }

    return count;
}

int directionScore(int** forest, int x, int y, int lineCount, int lineLength, char direction) {
    if (direction == 'N') return scoreNorth(forest, x, y);
    if (direction == 'S') return scoreSouth(forest, x, y, lineCount);
    if (direction == 'W') return scorekWest(forest, x, y);
    if (direction == 'E') return scoreEast(forest, x, y, lineLength);
    return 1;
}

int scoreView(int** forest, int x, int y, int lineCount, int lineLength) {
    char directions[] = { 'N', 'S', 'W', 'E' };
    int currentScore = 1;

    for (int i = 0; i < 4; i++) {
        currentScore *= directionScore(forest, x, y, lineCount, lineLength, directions[i]);
    }

    return currentScore;
}

void solutionTwo() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    int lineCount = 0;
    int lineLength = 0;
    int **forest = NULL;

    fgets(buffer, MAX_LENGTH, pFile);
    buffer[strcspn(buffer, "\n")] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) lineLength++;
    rewind(pFile);

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        lineCount++;
        forest = (int **)realloc(forest, sizeof(int *) * lineCount);
        forest[lineCount - 1] = (int *)malloc(sizeof(int) * lineLength);
        for (int i = 0; i < lineLength; i++) {
            forest[lineCount - 1][i] = buffer[i] - '0';
        }
    }

    fclose(pFile);

    int maxScore = 0;
    for (int y = 0; y < lineCount; y++) {
        for (int x = 0; x< lineLength; x++) {
            if (x == 0 || x == lineLength - 1 || y == 0 || y == lineCount - 1) continue;
            int currentScore = scoreView(forest, x, y, lineCount, lineLength);
            if (currentScore > maxScore) maxScore = currentScore;
        }
    }
    printf("%d", maxScore);


    deleteForest(forest, lineCount);
}

int main() {
    solutionOne();

    solutionTwo();

    return 0;
}