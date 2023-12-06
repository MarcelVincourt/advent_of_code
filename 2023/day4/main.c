

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 150

#define ROWS 190
#define LEN_WINNING 10 
#define LEN_GAME 25 


//const char file[] = "test.txt";
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
        token = strtok(NULL, " ");
    }
}

void get_cards(char *file, int *winning_nmbrs, int *nmbrs){
    char *part1 = strtok(file, "|");
    char *part2 = strtok(NULL, "|");

    get_numbers(part1, winning_nmbrs);
    get_numbers(part2, nmbrs);
}

int get_points(int *winning_nmbrs, int *nmbrs){
    int dups[10] = {0};
    int amount = 0;
    for (int i = 0; i < LEN_WINNING; i++){
        for (int j = 0; j < LEN_GAME; j++){
            if(winning_nmbrs[i] == nmbrs[j]){
                dups[amount] = amount+1;
                amount++;
            }
        }
    }
    int points = 1<<(amount-1);
    if (points < 0)
        points = 0;

    return points;
}

void get_matching(int *card_points, int *card, int *winning_nmbrs, int *nmbrs, int count){
    //int dups[10] = {0};
    int amount = 0;
    for (int i = 0; i < LEN_WINNING; i++){
        for (int j = 0; j < LEN_GAME; j++){
            if(winning_nmbrs[i] == nmbrs[j]){
                card_points[*card] = amount +1 + count;
                printf("[%d] add point to card: %d\n", *card, amount +1 + count);
                *card = *card + 1;
                //dups[amount-1] = amount+1;
                amount++;
            }
        }
    }

    //for(int i = 0; i < amount; i++){
    //    printf("%d | ", dups[i]);
    //}
    //printf("\namount: %d\n\n",amount);
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
        if (columns == 0){
            columns = strlen(line) -1;
        }
    }
    fclose(fp);
    printf("rows: %d, columns: %d\n", rows, columns);

    int winning_nmbrs[ROWS][LEN_WINNING] = {0};
    int nmbrs[ROWS][LEN_GAME] = {0};


    //rows = 4;
    for (int i = 0; i < rows; i++){
        get_cards(file[i], winning_nmbrs[i], nmbrs[i]);
        sum += get_points(winning_nmbrs[i], nmbrs[i]);
    }
    printf("sum: %llu\n", sum);


    int card = 6;
    int cards[100000] = {0};
    cards[0] = 0; // actually card 1
    cards[1] = 1;
    cards[2] = 2;
    cards[3] = 3;
    cards[4] = 4;
    cards[5] = 5; //actually card 6

    int count = 0;
    while(true){
        int current_card = cards[count];
        if (count > 0 && current_card == 0)
            break;
        printf("current card: %d\n", current_card); 
        get_matching(cards, &card, winning_nmbrs[current_card], nmbrs[current_card], current_card);
        count++;
    }


    int cart_count[6] = {0};
    for(int i =0; i < 100000; i++){
        printf("[%d] points: %d\n", i+1, cards[i]);
        cart_count[cards[i]]++;
    }
    cart_count[0] = 1;
    sum = 0;
    for(int i =0; i < 6; i++){
        printf("[%d], count: %d\n", i, cart_count[i]);
        sum+= cart_count[i];
    }
    printf("part2 sum: %llu\n", sum);


    for (int i = 0; i < rows; i++)
        free(file[i]);
    free(file);
    return 0;
}
