
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 641 to low
// 650 not right answer
// 660 not right answer
// 681 to high
#define NUMBERS 1000
#define INPUT_FILE "input.txt"

enum LEFTRIGHT{
    LEFT,
    RIGHT
};

unsigned int leftColumn[NUMBERS];
unsigned int rightColumn[NUMBERS];
unsigned int diffList[NUMBERS];

bool diffToLarge(int *numbers, int len){
    int diff = 0;
    for(int i=0; i<len-1; i++){
        diff = numbers[i] - numbers[i+1];
        if (diff < 0) 
            diff *= -1;
        if (diff > 3)
            return true;
    }
    return false;
}

bool increaseAndDecrease(int *numbers, int len){
    int increasing = 0;
    int decreasing = 0;
    int doubles = 0;
    int diff = 0;
    int diffToLarge = 0;
    for(int i=0; i<len-1; i++){
        diff = numbers[i] - numbers[i+1];
        if (diff < 0) {
            diff *= -1;
            increasing++;
        }
        else if (diff > 0 && diff < 4)
            decreasing++;
        else
            doubles++;

        if (diff > 3)
            diffToLarge++;
    }
    if(increasing > 1 && decreasing > 1)
        return true;
    if (increasing && decreasing && doubles)
        return true;
    if (doubles > 1)
        return true;
    if (increasing && decreasing && diffToLarge)
        return true;
    if (diffToLarge > 1)
        return true;
    if (doubles && diffToLarge)
        return true;
    return false;
}

bool findDouble(int *numbers, int len){
    int diff = 0;
    int doubles = 0;
    int doubleIndex = 0;
    for(int i=0; i<len-1; i++){
        diff = numbers[i] - numbers[i+1];
        if (diff == 0) {
            doubles++;
            if (doubles == 1)
                doubleIndex = i;
        }
    }
    // if there are more than 2 doubles set all to 0 because it is an invalid input
    if (doubles > 1){
        return false;
    }
    else if (doubles == 1)
    {
        // set the index of the first double to 0xFF so we can see later that this is a changed value
        numbers[doubleIndex] = 0xFF;
    }
    return true;
}

void problemDampener(int *numbers, int len){
    //if (isValid && ffFound){
    FILE *fp;
    fp = fopen("diff2", "a");
    for(int i=0; i<len; i++){
        printf("%d ", numbers[i]);
        fprintf(fp, "%d ", numbers[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
    printf("\n");
}

bool validIncreasing(int *numbers, int len){
    int diff = 0;
    bool increasing = false;
    bool decreasing = false;
    for(int i=0; i<len-1; i++){
        diff = numbers[i] - numbers[i+1];
        if (diff < 0) {
            decreasing = true;
        } else {
            increasing = true;
        }
    }
    //printf("increase: %d, decreasing: %d\n", increasing, decreasing);
    if (increasing & decreasing)
        return false;
    return true;
}


bool isSafe(int *numbers, int len){
    int diff = 0;
    bool isValid = true;
    for(int i=0; i<len-1; i++){
        diff = numbers[i] - numbers[i+1];
        if (diff < 0) {
            diff *= -1;
        }

        if (diff > 3 || diff == 0) isValid = false;
        //printf("%d - %d = %d, diff: %d\n", numbers[i], numbers[i+1]diff);
    }
    //for(int i=0; i<len; i++)
    //    printf("%d ", numbers[i]);
    //printf(" \t\tvalid: %d\n", isValid);
    return isValid;
} 

void readFile(void){
    FILE *fp;
    fp = fopen(INPUT_FILE, "r");

    char line[1024];
    int numbers[20] = {};
    int num = 0;
    char *pch;
    char *endptr;
    int count = 0;
    int validCount = 0;
    int validCount2 = 0;
    while(fgets(line, 1024, fp) != NULL){
        count = 0;
        for(int i = 0; i<20; i++)
            numbers[i] = 0;

        pch = strtok(line, " ");
        while (pch != NULL){
            num= strtol(pch, &endptr, 10);
            numbers[count++] = num;
            pch = strtok(NULL, " ");
        }

        //if (diffToLarge(numbers, count))
        //    continue;
        if (increaseAndDecrease(numbers, count))
            continue;
        //if (!findDouble(numbers, count))
        //    continue;
        problemDampener(numbers, count);
        validCount2++;

        //if (!validIncreasing(numbers, count))
        //    continue;
        //if (isSafe(numbers, count))
        //    validCount++;
        for(int i = 0; i<1024; i++)
            line[i] = 0;
    }
    //printf("Found: %d valid rows\n", validCount);
    printf("2Found: %d valid rows\n", validCount2);
    fclose(fp);
}


int main(){
    printf("hello, day2!\n");
    readFile();
}
