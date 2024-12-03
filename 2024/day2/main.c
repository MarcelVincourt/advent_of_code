
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


int compAsc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int compDesc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

void printNumbers(int *numbers, int len){
    for(int i=0; i<len; i++){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}


bool isGood(int *numbers, int len){
    int newNumbers[20] = {};
    bool increase = false;
    bool decrease = false;
    bool incOrDec = false;
    memcpy(newNumbers, numbers, len*sizeof(len));
    qsort(newNumbers, len, sizeof(int), compAsc);
    memcmp(newNumbers, numbers, len) == 0 ? increase = true : false;
    printf("increase: %d\norigi: ", increase);
    for(int i=0; i<len; i++){
        printf("%d ", numbers[i]);
    }
    printf("\nnew:  ");
    for(int i=0; i<len; i++){
        printf("%d ", newNumbers[i]);
    }
    printf("\n");

    memcpy(newNumbers, numbers, len*sizeof(len));
    qsort(newNumbers, len, sizeof(int), compDesc);
    memcmp(newNumbers, numbers, len) == 0 ? decrease = true : false;
    printf("decrease: %d\norigi: ", decrease);
    for(int i=0; i<len; i++){
        printf("%d ", numbers[i]);
    }
    printf("\nnew:  ");
    for(int i=0; i<len; i++){
        printf("%d ", newNumbers[i]);
    }
    printf("\n");
    incOrDec = increase || decrease;
    printf("incOrDec: %d\n\n", incOrDec);

    int diff = 0;
    bool ok = true;
    for(int i=0; i<len-1; i++){
        diff = abs(numbers[i] - numbers[i+1]);
        if (diff < 1 || diff > 3) {
            ok = false;
            break;
        }
        
    }
    incOrDec = true;
    return incOrDec && ok;
}

bool diffToLarge(int *numbers, int len){
    int diff = 0;
    for(int i=0; i<len-1; i++){
        diff = abs(numbers[i] - numbers[i+1]);
        if (diff < 1 || diff > 3)
            return true;
    }
    return false;
}

bool increaseAndDecrease(int *numbers, int len){
    int increasing = 0;
    int decreasing = 0;
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
    }
    if(increasing && decreasing )
        return true;
    return false;
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

        if (!diffToLarge(numbers, count) && !increaseAndDecrease(numbers, count))
            validCount++;

        int newNumbers[20] = {};
        for(int indexToSkip=0; indexToSkip<count; indexToSkip++){
            int index = 0;
            for (int j=0; j<count; j++){
                if (indexToSkip != j){
                    newNumbers[index] = numbers[j];
                    index++;
                }
            }
            //printNumbers(newNumbers, count-1);
            //printNumbers(numbers, count);
            //printf("\n");
            if (!diffToLarge(newNumbers, index) && !increaseAndDecrease(newNumbers, index)) {
                validCount2++;
                break;
            }
            
        }
        //break;
        //if (!diffToLarge(newNumbers, count-1) && !increaseAndDecrease(newNumbers, count-1))
        //    validCount2++;

    }
    printf("Found: %d valid rows\n", validCount);
    printf("2Found: %d valid rows\n", validCount2);
    fclose(fp);
}


int main(){
    printf("hello, day2!\n");
    readFile();
}
