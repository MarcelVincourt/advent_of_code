
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBERS 1000
#define INPUT_FILE "input.txt"

enum LEFTRIGHT{
    LEFT,
    RIGHT
};

unsigned int leftColumn[NUMBERS];
unsigned int rightColumn[NUMBERS];
unsigned int diffList[NUMBERS];


void readFile(void){
    FILE *fp;
    fp = fopen(INPUT_FILE, "r");

    char line[1024];
    char *pch;
    char *endptr;
    int num;
    int leftFound = 0;
    int rightFound = 0;
    int count = 0;
    while(fgets(line, 1024, fp) != NULL){
        leftFound = 0;
        rightFound = 0;
        pch = strtok(line, "   ");
        while (pch != NULL){
            num= strtol(pch, &endptr, 10);
            if (!leftFound) {
                leftColumn[count] = num;
                leftFound = 1;
            }
            else if(leftFound && !rightFound){
                rightColumn[count] = num;
                rightFound = 1;
            }
            pch = strtok(NULL, "");
        }
        //printf("[%d] left: %d, right: %d\n", count, leftColumn[count], rightColumn[count]);
        count++;
    }
    fclose(fp);
}

void removeNumFromList(int num, enum LEFTRIGHT leftRight){
    if(leftRight == LEFT){
        for(int i = 0; i < NUMBERS; i++){
            if (leftColumn[i] == num){
                leftColumn[i] = 999999;
                return;
            }
        }
    }
    else {
        for(int i = 0; i < NUMBERS; i++){
            if (rightColumn[i] == num){
                rightColumn[i] = 999999;
                return;
            }
        }
    }
}

int findLowest(void){
    int lowNumberLeft = 999999;
    int lowNumberRight = 999999;
    for(int i = 0; i < NUMBERS; i++){
        if (leftColumn[i] < lowNumberLeft)
            lowNumberLeft = leftColumn[i];
        if (rightColumn[i] < lowNumberRight)
            lowNumberRight = rightColumn[i];
    }
    removeNumFromList(lowNumberLeft, LEFT);
    removeNumFromList(lowNumberRight, RIGHT);
    //printf("Lowest number in leftColumn is: %d\n", lowNumberLeft);
    //printf("Lowest number in rightColumn is: %d\n", lowNumberRight);
    int diff = lowNumberLeft - lowNumberRight;
    if (diff < 0)
        return diff *-1;
    return diff;
}

void findSimilarity(void){
    int similarityList[NUMBERS];
    int numToFind = 0;
    int timesFound = 0;
    for(int i = 0; i < NUMBERS; i++){
        numToFind = leftColumn[i];
        timesFound = 0;
        for (int j = 0; j < NUMBERS; j++){
            if (rightColumn[j] == numToFind)
                timesFound++;
        }
        similarityList[i] = numToFind * timesFound;
        //printf("found: %d, %d times. answer: %d\n", numToFind, timesFound, similarityList[i]);
    }
    unsigned long int sum = 0;
    for (int i = 0; i < NUMBERS; i++){
        sum += similarityList[i];
        //printf("[%d] sum: %ld\n", i, sum);
    }
    printf("similarity SUM: %ld\n", sum);
}

int main(){
    printf("hello, day1!\n");
    readFile();
    int count = 0;
    while (count < NUMBERS){
        diffList[count] = findLowest();
        //printf("diff: %d\n", diffList[count]);
        count++;
    }
    unsigned long int sum = 0;
    for (int i = 0; i < NUMBERS; i++)
        sum += diffList[i];
    printf("SUM: %ld\n", sum);

    // read file again to fill the arrays correctly
    readFile();
    findSimilarity();
    return 0;
}
