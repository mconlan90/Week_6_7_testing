#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STR_LEN 20

void bubbleSort(char [][STR_LEN], size_t);

void removeSpecial(char *, size_t);

void reformatDate(char *);

void swapChars(char *, char *);

void swapStrings(char *, char *);

void writeArrayToFile(char [][STR_LEN], char *);

int main() {
    char string[STR_LEN] = {};
    char file_name[30], output_name[30];
    char timestamps[50][STR_LEN] = {};
    int i = 0;

    FILE *tsPtr;
    // get file name from user, expecting "timestamps.txt"
    printf("Enter the file to be opened:\n");
    scanf("%s", file_name);
    printf("Enter the file to write to:\n");
    scanf("%s", output_name);
    // check file name is correct
    if ((tsPtr = fopen(file_name, "r")) == NULL) {
        printf("File could not be opened. Please try again:\n");
        scanf("%s", file_name);
    } else {
        // continue until EOF
        while (!feof(tsPtr) && (fgets(string, STR_LEN, tsPtr) != NULL)) {
            // append strings to string array
            if (strlen(string) == STR_LEN - 1) {
                strcpy(timestamps[i], string);
                i++;
            }
        }
        fclose(tsPtr);
    }

    int rows = sizeof(timestamps) / sizeof(timestamps[0]);

    for (size_t j = 0; j < rows; j++) {
        // remove special characters from string
        removeSpecial(timestamps[j], STR_LEN);
        // sort dates into YYYYMMDD format
        reformatDate(timestamps[j]);
    }
    // sort timestamps chronologically
    bubbleSort(timestamps, rows);
    // output sorted array to file
    writeArrayToFile(timestamps, output_name);

    return 0;
}

void bubbleSort(char arr[][STR_LEN], size_t rows) {
    for (int pass = 1; pass < rows; pass++) {
        for (size_t i = 0; i < rows - pass; ++i) {
            for (size_t j = 0; j < 11; ++j) {
                if (arr[i][j] < arr[i + 1][j]) {
                    break;
                }
                if (arr[i][j] > arr[i + 1][j]) {
                    swapStrings(arr[i], arr[i + 1]);
                    break;
                }
            }
        }
    }

  //  printf("Number of swaps: %d\n", swaps);
  //  printf("Number of comparisons: %d\n", comparisons);
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
    char hold[STR_LEN];
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

void writeArrayToFile(char stringArray[][STR_LEN], char *output_name) {
    FILE *outPtr;

    int year, month, day, hour, minute, second;

    if ((outPtr = fopen(output_name, "w")) == NULL) {
        printf("File can not be opened.\n");
    } else {
        for (int i = 0; i < 50; i++) {
            sscanf(stringArray[i], "%4d%2d%2d%2d%2d%2d", &year, &month, &day, &hour, &minute, &second);
            fprintf(outPtr, "%02d/%02d/%4d-%02d:%02d:%02d\n", day, month, year, hour, minute, second);
        }
        fclose(outPtr);
    }
}