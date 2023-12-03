

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 1000

struct Cubes{
    int red;
    int green;
    int blue;
};
struct Cubes cmp_cubes = {.red=12, .green=13, .blue=14}; // compare cubes

//const char file[] = "test.txt";
const char file[] = "input.txt";

void removeSubstr (char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match+len);
    }
}

struct Cubes get_cubes(char string[LENGTH]){
    char saveptr[LENGTH*LENGTH] = {0};
    struct Cubes cubes = {0};

    char *token = strtok_r(string, ",", (char**)&saveptr);
    while (token != NULL){
        //printf("\tset: %s\n", token);
        if (strstr(token, "red")){
            cubes.red += atoi(token);
        }
        else if (strstr(token, "green"))
            cubes.green += atoi(token);
        else if (strstr(token, "blue"))
            cubes.blue += atoi(token);
        token = strtok_r(NULL, ",", (char**)&saveptr);
    }
    printf("\tcubes: red: %d, green: %d, blue: %d\n", cubes.red, cubes.green, cubes.blue);
    //printf("\tcubes: red: %d, green: %d, blue: %d\n", cmp_cubes.red, cmp_cubes.green, cmp_cubes.blue);
    return cubes;
}

bool find(char *string, int set_count, uint64_t *power){
    char saveptr[LENGTH] = {0};
    struct Cubes *cubes_lst = (struct Cubes*) malloc(set_count*sizeof(struct Cubes));
    bool ret = true;


    //printf("string: %s, setcount: %d\n", string, set_count);

    int count = 0;
    char *token = strtok_r(string, ";", (char**)&saveptr);
    while (token != NULL){
        printf("set: %s\n", token);
        //printf("before get_cubes\n");
        cubes_lst[count++] = get_cubes(token);
        //printf("after get_cubes\n");
        //printf("before strok_r\n");
        token = strtok_r(NULL, ";", (char**)&saveptr);
        //printf("after strok_r: %s\n", token);
    }
    //printf("strok_r NULL received!!\n");
    int largest_red = 0;
    int largest_green = 0;
    int largest_blue = 0;
    for(int i = 0; i < set_count; i++){
        //printf("%d, setcount: %d\n", i, set_count);
        struct Cubes cube = cubes_lst[i];
        if(cube.red > cmp_cubes.red || cube.green > cmp_cubes.green || cube.blue > cmp_cubes.blue)
        {
            ret = false;
        }
        if (cube.red > largest_red)
            largest_red = cube.red;
        if (cube.green > largest_green)
            largest_green = cube.green;
        if (cube.blue > largest_blue)
            largest_blue = cube.blue;
    }
    printf("%d, %d, %d\n", largest_blue, largest_green, largest_red);
    *power += (largest_red * largest_green * largest_blue);

    free(cubes_lst);
    return ret;
}

int main(){
    FILE *fp;


    char read[LENGTH] = {0};
    char *original;
    uint64_t sum = 0;
    uint64_t sum_power = 0;
    char *token;

    fp = fopen(file, "r");
    while(fgets(read, LENGTH, fp) != NULL){
        original = (char*) malloc(LENGTH);
        for(int i = 0; i < LENGTH; i++)
            original[i] = 0;
        if (original == NULL){
            printf("unable to malloc!\n");
            return -1;
        }
        printf("%s", read);
        strncpy(original, read, strlen(read)-1);
        char *ptr = original;

        int set_count = 0; 
        for(int i = 0; i < LENGTH; i++){
            if(original[i] == ';')
                set_count++;
        }
        set_count++;

        token = strtok(read, ":");
        int game = atoi(token+4); // +4 to remove "game"
        removeSubstr(ptr, token);
        *ptr++;
        if (find(ptr, set_count, &sum_power)){
            sum+=game;
            printf("good\n");
        }
        else printf("bad\n");

        printf("game: %d, sum: %ld, sum_power: %ld\n", game, sum, sum_power);
        free(original);
        memset(read, 0, 1000);
        //printf("Press Enter to Continue");
        //while( getchar() != '\n' );
    }
    fclose(fp);
    printf("sum: %ld, sum_power: %ld\n", sum, sum_power);
    return 0;
}