

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 150
#define POSSES 2000


//const char file[] = "input_stan.txt";
const char file[] = "input.txt";

static int rows = 0;
static int columns = 0;


int get_int_len (int value){
    int l=1;
    while(value>9){ l++; value/=10; }
    return l;
}

void get_numbers(char *part, int *numbers){
    char *token;
    int count = 0;
    token = strtok(part, " ");
    while (token != NULL){
        if (strstr(token, ":") == NULL && strstr(token, "Card") == NULL ){
            numbers[count++] = atoi(token);
        }
        //printf("token: %s\n", token);
        token = strtok(NULL, " ");
    }
}

int get_points(char *file){
    char *part1 = strtok(file, "|");
    char *part2 = strtok(NULL, "|");
    printf("part1: %s\n", part1);
    printf("part2: %s\n", part2);

    int winning_nmbrs[10] = {0};
    int nmbrs[25] = {0};

    get_numbers(part1, winning_nmbrs);
    get_numbers(part2, nmbrs);
    printf("winning: ");
    for(int i =0; i < 10; i++){
        printf("%d, ", winning_nmbrs[i]);
    }
    printf("\nreceived: ");
    for(int i =0; i < 25; i++){
        printf("%d, ", nmbrs[i]);
    }
    printf("\n");

    int amount = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 25; j++){
            if(winning_nmbrs[i] == nmbrs[j]){
                amount++;
                printf("Found winning number: %d!\n", nmbrs[j]);
            }
        }
    }
    int points = 1<<(amount-1);
    if (points < 0)
        points = 0;
    printf("Points: %d\n", points);
    return points;
}

int main(){
    FILE *fp;

    char line[LENGTH] = {0};
    char *original;
    uint64_t sum = 0;
    long file_size = 0;

    fp = fopen(file, "r");

    // get file size
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
    char **file = (char**) malloc(file_size);

    printf("file is: %ld long\n", file_size);
    while(fgets(line, file_size, fp) != NULL){
        file[rows] = malloc(strlen(line) -1);
        strncpy(file[rows++], line, strlen(line) - 1);
        if (columns == 0){
            columns = strlen(line) -1;
        }
    }
    fclose(fp);
    printf("rows: %d, columns: %d\n", rows, columns);

    for (int i = 0; i < rows; i++){
        sum += get_points(file[i]);
    }
    printf("sum: %llu\n", sum);


    for (int i = 0; i < rows; i++)
        free(file[i]);
    free(file);
    return 0;
}
