

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 150


const char file[] = "test.txt";
//const char file[] = "input.txt";

static int rows = 0;
static int columns = 0;

typedef struct Seeds{
    uint64_t *seeds;
    int count;
} Seeds;

typedef struct Map {
    uint64_t **values;
    int count;
} Map;


int get_int_len (int value){
    int l=1;
    while(value>9){ l++; value/=10; }
    return l;
}

int count_numbers(char *str){
    int amount_seeds = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if (str[i] == 32) // space
            amount_seeds++;
    }
    return amount_seeds;
}



Seeds get_seeds(char *file){
    printf("%s\n", &file[7]);
    int amount_seeds = 0;
    amount_seeds = count_numbers(&file[7]);

    Seeds seeds;
    seeds.seeds = (uint64_t*) malloc(sizeof(seeds.seeds) * amount_seeds);
    int found = 0;
    char *token = strtok(&file[7], " ");
    while (token != NULL){
        seeds.seeds[found++] = atoi(token);
        token = strtok(NULL, " ");
    }
    seeds.count = found;
    return seeds;
}

Map get_value(char **file, char *search_str){
    Map map;
    int line = 0;
    for(int i =0; i< rows; i++){
        if (strstr(file[i], search_str)){
            printf("Found: %s\n", search_str);
            line = i+1;
            break;
        }
    }
    // get rows of numbers
    int count = 0;
    for(int i =line; i < line+5; i++){
        if (strlen(file[i]) > 1)
            count++;
        else break;
    }

    for(int i =line; i < line+5; i++){
        if (strlen(file[i]) > 1){
            int c = count_numbers(file[i]);
            printf("[%d] Found: %d number int str: %s\n",i, c, file[i]);
        }
        else
            break;

        //printf("strlen: %ld\n", strlen(file[i]));
    }
    return map;
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
    
    char **file = (char**) calloc(file_size, sizeof(char));

    printf("file is: %ld Bytes large\n", file_size);
    while(fgets(line, file_size, fp) != NULL){
        file[rows] = malloc(strlen(line) );
        strncpy(file[rows++], line, strlen(line) );
        size_t tmp = strlen(line) - 1;
        if (columns == 0 || columns < tmp){
            columns = tmp;
        }
    }
    fclose(fp);
    printf("rows: %d, columns: %d\n", rows, columns);

    Seeds seeds = get_seeds(file[0]);
    printf("seeds amount: %d\n", seeds.count);

    get_value(file, "seed-to-soil");
    //get_value(file, "soil-to-fertilizer");
    //get_value(file, "fertilizer-to-water");
    //get_value(file, "water-to-light");
    //get_value(file, "light-to-temperature");
    //get_value(file, "temperature-to-humidity");
    //get_value(file, "humidity-to-location");

    free(seeds.seeds);
    for (int i = 0; i < rows; i++){
        free(file[i]);
    }
    free(file);
    return 0;
}
