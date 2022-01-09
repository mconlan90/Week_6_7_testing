#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void bubbleSort(char arr[][11], size_t);

void removeSpecial(char *, size_t);

void reformatDate(char *);

void swapChars(char *, char *);

void swapStrings(char *, char *);

int main() {
    char arr[][11] = {"10/12/1990", "26/02/1991", "05/02/1966", "10/07/1997", "25/08/1966"};
    int rows = sizeof(arr) / sizeof(arr[0]);
    unsigned long len = strlen(*arr);


    // printf("%zu", len);
    // unsigned long newLen = strlen(*arr);

    for (size_t i = 0; i < rows; i++) {
        // remove special characters from string
        // printf("%s", arr[i]);
        removeSpecial(arr[i], len);

        // sort dates into YYYYMMDD
        reformatDate(arr[i]);
    }

    bubbleSort(arr, rows);

   /* for (int i = 0; i < rows; i++) {
        printf("%s\n", arr[i]);
    } */
    return 0;
}

void bubbleSort(char arr[][11], size_t rows) {
    int comparisons = 0, swaps = 0;
    for (int pass = 1; pass < rows; pass++) {
        printf("Pass: %d\n", pass);
        comparisons++;
        for (size_t i = 0; i < rows - pass; ++i) {
            printf("\tComparing %s with %s\n", arr[i], arr[i+1]);
            for (size_t j = 0; j < 11; ++j) {
                printf("\t\t i: %zu, j: %zu, char1: %c, char2: %c\n", i, j, arr[i][j], arr[i+1][j]);
                if (arr[i][j] < arr[i + 1][j]) {
                    break;
                }
                if (arr[i][j] > arr[i + 1][j]) {
                    printf("\t\tSwapping: %s with %s\n", arr[i], arr[i + 1]);
                    swapStrings(arr[i], arr[i + 1]);
                    swaps++;
                    break;
                }
            }
        }
        for (int i = 0; i < rows; i++) {
            printf("\tArray: %s\n", arr[i]);
        }
    }

    printf("Number of swaps: %d\n", swaps);
    printf("Number of comparisons: %d\n", comparisons);
}

// swapChars two values
void swapChars(char *elem1Ptr, char *elem2Ptr) {
    char hold;
    hold = *elem1Ptr;
    *elem1Ptr = *elem2Ptr;
    *elem2Ptr = hold;
}

// remove special characters
void removeSpecial(char *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (ispunct(arr[i])) {
            for (size_t j = i; j < size; j++) {
                arr[j] = arr[j + 1];
            }
            i--;
            size--;
        }
    }
}

void swapStrings(char *elemPtr1, char *elemPtr2) {
    char hold[9];
    strcpy(hold, elemPtr1);
    strcpy(elemPtr1, elemPtr2);
    strcpy(elemPtr2, hold);
}

// put the dates in a sortable format
void reformatDate(char *arr) {
    swapChars(&arr[0], &arr[6]);
    swapChars(&arr[1], &arr[7]);
    swapChars(&arr[2], &arr[4]);
    swapChars(&arr[3], &arr[5]);
    swapChars(&arr[0], &arr[2]);
    swapChars(&arr[1], &arr[3]);
}