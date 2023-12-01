
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LOOKUP_SIZE 9
char *lookup[LOOKUP_SIZE] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

char lookup_int[LOOKUP_SIZE][1] = {
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
};

char *strrstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *) haystack;
    }

    char *lastOccurrence = NULL;
    while (1) {
        char *p = strstr(haystack, needle);
        if (!p) {
            break;
        }
        lastOccurrence = p;
        haystack = p + 1;
    }
    
    return lastOccurrence;
}



int main(){
    FILE *fp;

    char read[100];
    uint64_t sum = 0;

    fp = fopen("input.txt", "r");
    while(fgets(read, 100, fp) != NULL){
        char *ptr = read;
        char getal[3] = {47, 47, 0};
        int index = 0;
        int low_pos = 255;
        int high_pos = -1;
        int lookup_low_pos = 0;
        int lookup_high_pos = 0;
        // loop through read as pointer
        for(int i = 0; i < LOOKUP_SIZE; i++){
            char *res = strstr(read, lookup[i]);
            if(res != NULL){
                if (res-read < low_pos){
                    low_pos = res-read;
                    lookup_low_pos = i;
                }
            }
            // last occurence
            res = strrstr(read, lookup[i]);
            if(res != NULL){
                if (res-read > high_pos){
                    high_pos = res-read;
                    lookup_high_pos = i;
                }
            }
        }
        //printf("low_pos: %d, high_pos: %d, lookup_low_pos: %d, lookup_high_pos: %d\n", low_pos, high_pos, lookup_low_pos, lookup_high_pos);
        while (*ptr != '\0') {
            if(*ptr >= 48 && *ptr <= 57){
                if (ptr - read < low_pos){
                    low_pos = ptr - read;
                    getal[0] = *ptr;
                }
                if (ptr - read > high_pos){
                    high_pos = ptr - read;
                    getal[1] = *ptr;
                }
            }
            ptr++;
        }
        getal[2] = '\0';
        if(getal[0] == 47){
            getal[0] = lookup_int[lookup_low_pos][0];
        }
        if(getal[1] == 47 && lookup_high_pos != -1){
            getal[1] = lookup_int[lookup_high_pos][0];
        }
        else if(getal[1] == 47 && lookup_high_pos == -1){
            printf("gek geval\n");
        }
        sum += atoi(getal);
        //printf("getal: %s, sum: %lu, text: %s\n", getal, sum, read);
        //printf("Press Enter to Continue");
        //while( getchar() != '\n' );
    }
    printf("sum: %lu\n", sum);



    fclose(fp);
    return 0;
}
