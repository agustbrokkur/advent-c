#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LENGTH 64

typedef struct Directory {
    char name[MAX_LENGTH];
    int size;
    int childCount;
    struct Directory *children;
    struct Directory *parent;
} Directory;

void updateDirectorySize(Directory *dir, int size) {
    dir->size += size;
    if (dir->parent != NULL) updateDirectorySize(dir->parent, size);
}

void createDirectory(Directory *parent, const char* name, int size) {
    Directory *newFolder = (Directory *)malloc(sizeof(Directory)); 
    strcpy(newFolder->name, name);
    newFolder->size = size;
    newFolder->childCount = 0;
    newFolder->children = NULL;
    newFolder->parent = parent;

    updateDirectorySize(parent, size);
    parent->childCount += 1;
    parent->children = (Directory *)realloc(parent->children, parent->childCount * sizeof(Directory));
    parent->children[parent->childCount - 1] = *newFolder;

}

void deleteDirectory(Directory *dir) {
    if (dir->children != NULL) {
        for (int i = 0; i < dir->childCount; i++) {
            deleteDirectory(&(dir->children[i]));
        }
        free(dir->children);
    }
    free(dir);
}

void printDirectory(Directory *dir, int depth) {
    printf("%-*s- %s %d\n", depth * 2, " ", dir->name, dir->size);
    if (dir->children != NULL) {
        for (int i = 0; i < dir->childCount; i++) {
            printDirectory(&(dir->children[i]), depth + 1);
        }
    }
}

int fileSizeSumUnder(Directory *dir, int size) {
    int localSize = 0;
    if (dir->size < size && dir->children != NULL) {
        localSize += dir->size;
    }
    if (dir->children != NULL) {
        for (int i = 0; i < dir->childCount; i++) {
            localSize += fileSizeSumUnder(&(dir->children[i]), size);
        }
    }

    return localSize;
}

void findSmallestTargetDir(Directory *dir, int size, int *value) {
    if (dir->children == NULL) return;

    if (dir->size > size && dir->size < *value) {
        *value = dir->size;
    }
    
    for (int i = 0; i < dir->childCount; i++) {
        findSmallestTargetDir(&(dir->children[i]), size, value);
    }
}

void fileStucture() {
    FILE *pFile = fopen("input.txt", "r");
    char buffer[MAX_LENGTH];
    Directory root = { "/", 0, 0, NULL, NULL };
    Directory *current = &root;

    if (pFile == NULL) {
        printf("input.txt file does not exist.\n");

        return;
    }

    while (fgets(buffer, MAX_LENGTH, pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '$') {
            char command[MAX_LENGTH], dir[MAX_LENGTH];
            sscanf(buffer, "$ %s %s", command, dir);

            if (strcmp(command, "cd") == 0) {
                if (strcmp(dir, "\\") == 0) {
                    current = &root;
                    continue;
                }
                if (strcmp(dir, "..") == 0) {
                    current = current->parent;
                    continue;
                }

                for (int i = 0; i < current->childCount; i++) {
                    if (strcmp(current->children[i].name, dir) == 0){
                        current = &(current->children[i]);
                        break;
                    }
                }
            }
            else continue;
        }
        else {
            if (buffer[0] == 'd') {
                char itemName[MAX_LENGTH];
                sscanf(buffer, "dir %s", itemName);
                createDirectory(current, itemName, 0);

            }
            else {
                int itemSize;
                char itemName[MAX_LENGTH];
                sscanf(buffer, "%d %s", &itemSize, itemName);
                createDirectory(current, itemName, itemSize);
            }
        }
    }

    fclose(pFile);

    printDirectory(&root, 0);
    int sizeUnder = fileSizeSumUnder(&root, 100000);

    printf("Total filesizes under 100000 is %d\n", sizeUnder);
    int sizeTarget = 30000000 - (70000000 - root.size);
    int target = INT_MAX;
    findSmallestTargetDir(&root, sizeTarget, &target);
    printf("Size target is %d\n", target);

    deleteDirectory(&root);
}



int main() {
    fileStucture();

    return 0;
}