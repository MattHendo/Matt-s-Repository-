#include <stdio.h>


int main() {
    int array[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int n = sizeof(array) / sizeof(int);
    int i, j, temp, swpcount;

    for (i = 0; i < n - 1; i++) {
        swpcount = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j+1]) {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                 swpcount++; 
                /*
                if I understand the assignment correctly, this should
                just be a bubble sort that counts how many swaps were made per pass 
                */
            }
        }
    printf("pass #%d: %d\n", i+1, swpcount);
    }
    return 0;
}