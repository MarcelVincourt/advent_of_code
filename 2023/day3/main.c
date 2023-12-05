

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 150
#define POSSES 2000


//const char file[] = "test.txt";
const char file[] = "input.txt";

static int line_count = 0;
static int end_line = 0;

struct Position{
    int number;
    int line;
    int start;
    int end;
};

int get_int_len (int value){
    int l=1;
    while(value>9){ l++; value/=10; }
    return l;
}


void find_parts(char **file, int line_count, struct Position *pos){
    int start = 0;
    int end = 0;
    int pos_count = 0;
    int loc_start = 0, loc_end = 0;
    for(int line = 0; line < line_count; line++){
        for(int ch = 0; ch < LENGTH; ch++){
            char c = file[line][ch];
            char *cp = &file[line][ch];
            if(c >= 48 && c <= 57){
                int number = atoi(cp);
                int num_len = get_int_len(number);
                pos[pos_count].number = number;
                pos[pos_count].start = ch;
                pos[pos_count].end = ch + num_len -1;
                pos[pos_count].line = line;
                pos_count++;
                ch += num_len;
            }
        }
    }
}

bool is_part(char **file, int line_count, int end_line, struct Position pos){
    int top_file = pos.line == 0 ? 0 : pos.line -1;
    int bot_file = pos.line == line_count-1 ? line_count-1 : pos.line +1;
    int start = pos.start == 0 ? 0 : pos.start -1;

    for (int i = start; i <= pos.end+1; i++){
        if (i >= end_line)
            break;
        char ct = file[top_file][i]; // char top
        char cb = file[bot_file][i]; // char bottem
        char cc = file[pos.line][i]; // char current(middle)
        if((ct < 48 || ct > 57) && ct != '.'){
            return true;
        }
        if((cc < 48 || cc > 57) && cc != '.'){
            return true;
        }
        if((cb < 48 || cb > 57) && cb != '.'){
            return true;
        }
    }
    return false;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < line_count && y >= 0 && y < end_line;
}

int get_number(char **file, int x, int y){
    int number = 0;
    bool prev_num = false;
    for (int i = y; i >= 0; i--){
        char c = file[x][i];
        if (c >= 48 && c <= 57){
            number = atoi(&file[x][i]);
        }
        else
            break;
    }
    return number;
}

int check_gear(char **file, int x, int y){
    int numbers[8] = {0};
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};  // Relative x coordinates
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};  // Relative y coordinates
    for (int i = 0; i < 8; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if (is_valid(new_x, new_y)) {
            int number = get_number(file, new_x, new_y);
            bool dup = false;
            for(int j = 0; j < 8; j++)
                if (numbers[j] == number)
                    dup = true;
            if(!dup) {
                numbers[i] = number;
                //printf("At (%d, %d): %c, nmbr: %d\n", new_x, new_y, file[new_x][new_y], number);
            }
        }
        //else {
        //    printf("At (%d, %d): Out of bounds\n", new_x, new_y);
        //}
    }
    int prev_num = 0;
    int num_cnt = 0;
    int num_mul = 0;
    for (int i = 0; i < 8; i++) {
        //if (prev_num == numbers[i]) {
        //    numbers[i] = 0;
        //}
        if(numbers[i] != 0){
            num_cnt++;
            if (num_cnt == 1 && prev_num != numbers[i])
                num_mul = numbers[i];
            if(num_cnt == 2 && prev_num != numbers[i])
                num_mul *= numbers[i];
        }
        prev_num = numbers[i];
    }
    if (num_cnt != 2)
        num_mul = 0;
    //else
    //    printf("mul: %d\n", num_mul);
    //printf("\n");
    return num_mul;
}

void part2(char **file){
    uint64_t sum = 0;
    int start = 0;
    int end = 0;
    int pos_count = 0;
    int loc_start = 0, loc_end = 0;
    for(int line = 0; line < line_count; line++){
        for(int ch = 0; ch < end_line; ch++){
            char c = file[line][ch];
            if (c == '*'){
                sum += check_gear(file, line, ch);
            }
        }
    }
    printf("part2 sum: %llu\n", sum);
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

    printf("file is: %ld long\n", file_size);
    while(fgets(line, LENGTH, fp) != NULL){
        file[line_count] = malloc(strlen(line) -1);
        strncpy(file[line_count++], line, strlen(line) - 1);
        end_line = strlen(line) -1;
    }
    fclose(fp);

    printf("lines: %d, end_line: %d\n", line_count, end_line);
    int start, end;
    struct Position posses[POSSES] = {0};
    find_parts(file, line_count, posses);
    for(int i = 0; i < POSSES; i++)
    {
        //printf("[%.4d] start: %d, end: %d, line: %d, number: %d\n", i, posses[i].start, posses[i].end, posses[i].line, posses[i].number);
        if (is_part(file, line_count, end_line, posses[i]))
            sum+=posses[i].number;
    }
    printf("part1 sum: %llu\n", sum);
    
    part2(file);

    for (int i = 0; i < line_count; i++)
        free(file[i]);
    free(file);
    return 0;
}
