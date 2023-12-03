

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 150
#define POSSES 1199


//const char file[] = "test.txt";
const char file[] = "input.txt";

struct Position{
    int line;
    int start;
    int end;
};


void find_parts(char **file, int line_count, struct Position *pos){
    int start = 0;
    int end = 0;

    int pos_count = 0;

    int loc_start = 0, loc_end = 0;
    for(int line = 0; line < line_count; line++){
        for(int ch = 0; ch < LENGTH; ch++){
            char c = file[line][ch];
            if(c >= 48 && c <= 57)
                if(start == 0) {
                    start = c; 
                    pos[pos_count].start = ch;
                }
                else {
                    end = c;
                    pos[pos_count].end = ch;
                }
            if ((start != 0 && end != 0) && (c < 48 || c > 57)) {
                pos[pos_count].line = line;
                pos_count++;
                start = 0;
                end = 0;
                if (pos_count >= POSSES)
                    return;
            }
        }
    }
}


int main(){
    FILE *fp;

    char line[LENGTH] = {0};
    char *original;
    uint64_t sum = 0;
    char *token;

    long file_size = 0;

    fp = fopen(file, "r");

    // get file size
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
    char **file = (char**) malloc(file_size);
    int line_count = 0;

    printf("file is: %ld long\n", file_size);
    while(fgets(line, LENGTH, fp) != NULL){
        file[line_count] = malloc(strlen(line) -1);
        strncpy(file[line_count++], line, strlen(line) - 1);
    }
    fclose(fp);

    printf("lines: %d\n", line_count);
    int start, end;
    struct Position posses[POSSES] = {0};
    find_parts(file, line_count, posses);
    for(int i = 0; i < POSSES; i++)
    {
        printf("[%.4d] start: %d, end: %d, line: %d\n", i, posses[i].start, posses[i].end, posses[i].line);
    }

    //for(int i = 0; i < line_count; i++)
    //    printf("%s\n", file[i]);

    for (int i = 0; i < LENGTH; i++)
        free(file[i]);
    free(file);
    return 0;
}