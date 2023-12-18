

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 1024 


const char file[] = "test.txt";
//const char file[] = "input.txt";

static int rows = 0;
static int columns = 0;

typedef struct Seeds{
    uint64_t *seeds;
    int count;
} Seeds;

typedef struct Map {
    long int **values;
    int count;
} Map;


int get_int_len (int value){
    int l=1;
    while(value>9){ l++; value/=10; }
    return l;
}

int count_numbers(char *str){
    int amount_seeds = 1;
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

Map get_numbers(char **file, char *search_str){
    Map map;
    int line = 0;
    for(int i =0; i< rows; i++){
        if (strstr(file[i], search_str)){
            //printf("Found: %s\n", search_str);
            line = i+1;
            break;
        }
    }
    // get rows of numbers
    int count = 0;
    int i = line;
    while (true) {
        //printf("strlen: %d\t%s\n", strlen(file[i]), file[i]);
        if(i >= rows){
            count--;
            break;
        }
        if (strlen(file[i]) > 1)
            count++;
        else break;
        i++;
    }

    // malloc the correct size
    map.values = malloc(sizeof(map.values) * count * 3);
    for(int i=0; i < count; i++){
        map.values[i] = malloc(sizeof(map.values) * 3);
    }
    map.count = count;

    int index = 0;
    for(int i =line; i < line+count; i++){
        if (strlen(file[i]) > 1){
            int found = 0;
            char *ptr;
            long int a, b, c;
            map.values[index][found++] = strtol(file[i], &ptr, 10);
            while(*ptr != '\n'){
                map.values[index][found++] = strtol(ptr, &ptr, 10);
            }
            index++;
        }
        else
            break;
    }
    return map;
}

void free_maps(Map map){
    for (int i = 0; i < map.count; i++)
        free(map.values[i]);
    free(map.values);
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
        file[rows] = malloc(strlen(line)+1 );
        strncpy(file[rows++], line, strlen(line) );
        //if(rows-1 < 20)
        //    printf("line[%d], len: %lu, str: %s", rows-1, strlen(line), line);
        size_t tmp = strlen(line);
        if (columns == 0 || columns < tmp){
            columns = tmp;
        }
        memset(line, 0, LENGTH);
    }
    fclose(fp);
    printf("rows: %d, columns: %d\n", rows, columns);
    //for(int i=0; i< rows; i++){
    //    printf("file[%d], len: %lu, str: %s", i, strlen(file[i]), file[i]);
    //}

    Seeds seeds = get_seeds(file[0]);
    printf("seeds amount: %d\n", seeds.count);

    Map soil_map = get_numbers(file, "seed-to-soil");
    Map fertilizer_map = get_numbers(file, "soil-to-fertilizer");
    Map water_map = get_numbers(file, "fertilizer-to-water");
    Map light_map = get_numbers(file, "water-to-light");
    Map temperature_map = get_numbers(file, "light-to-temperature");
    Map humidity_map = get_numbers(file, "temperature-to-humidity");
    Map location_map = get_numbers(file, "humidity-to-location");


    free(seeds.seeds);
    free_maps(soil_map);
    free_maps(fertilizer_map);
    free_maps(water_map);
    free_maps(light_map);
    free_maps(temperature_map);
    free_maps(humidity_map);
    free_maps(location_map);

    for (int i = 0; i < rows; i++){
        free(file[i]);
    }
    free(file);
    return 0;
}
