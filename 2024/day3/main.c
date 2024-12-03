
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//30634704 to low
//183530283 to low
//184511516

#define INPUT_LEN 19720
#define INPUT_FILE "input.txt"

static char input[INPUT_LEN] = {};


int find(char *findStr, char **input){
    char *location = strstr(*input, findStr);
    if (location == NULL)
        return 0; 
    *input += location-*input;
    *input += strlen(findStr);
    
    return 1;
}

int findClosingBracket(char **input){
    if((*input)[0] == ')'){
        *input += 1;
        return 1;
    }
    return 0;
}

int findNumbers(char **input, int *number){
    char *end;
    int num = strtol(*input, &end, 10);
    if (*input == end)
        return 0;

    *input = end;
    *number = num;
    return 1;
}

void readFile(void){
    FILE *fp;
    fp = fopen(INPUT_FILE, "r");
    int size = 0;
    while (fgets(&input[size], INPUT_LEN, fp) != NULL){
        //input[strlen(input)-1] = '\0';
        //size = strlen(input);

        printf("size: %ld\n", strlen(input));
        printf("last char: %d\n", input[strlen(input)-1]);
    }
    fclose(fp);

    printf("%s\n", input);
}


int main(){
    printf("hello, day2!\n");
    readFile();
    char *newInput = input;
    int a,b;
    unsigned long int sum = 0;
    while (strlen(newInput)){
        if ( find("mul(", &newInput) &&
             findNumbers(&newInput, &a) &&
             find(",", &newInput) &&
             findNumbers(&newInput, &b) &&
             findClosingBracket(&newInput)){
        printf("got num: %d and %d = %d\n", a, b, a*b);
        sum += (unsigned long int)(a*b);
        //printf("sum: %ld, newInput: %s\n",sum, newInput);
        printf("sum: %ld\n",sum);
        }
        if (!find("mul(", &newInput))
            break;
    }
}
