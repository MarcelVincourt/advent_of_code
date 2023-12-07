

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 150

#define ROWS 190
#define LEN_WINNING 10 
#define LEN_GAME 25 

//#define ROWS 6
//#define LEN_WINNING 5 
//#define LEN_GAME 8 

//const char file[] = "test.txt";
const char file[] = "input.txt";

static int rows = 0;
static int columns = 0;


struct Cards{
    int game_id;
    int matches;
    //int win_nums;
    //int game_nums;
};

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

void get_matching(struct Cards *card, int *win_nums, int *game_nums){
    int matches = 0;
    for (int i = 0; i < LEN_WINNING; i++){
        for (int j = 0; j < LEN_GAME; j++){
            //printf("%d ", card->win_nums[i]);
            if(win_nums[i] == game_nums[j]){
                matches++;
            }
        }
    }
    card->matches = matches;
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
    int win_nums[ROWS][LEN_WINNING] = {0};
    int game_nums[ROWS][LEN_GAME] = {0};


    //rows = 4;
    for (int i = 0; i < rows; i++){
        get_cards(file[i], win_nums[i], game_nums[i]);
        sum += get_points(win_nums[i], game_nums[i]);
    }
    printf("Part1 sum: %lu\n", sum);

    uint64_t card_size = rows;
    struct Cards *cards = malloc(sizeof(*cards) * card_size);
    printf("size: %ld\n", sizeof(cards) * card_size);
    for(int i = 0; i<rows; i++){
        struct Cards *card = &cards[i];
        card->game_id = i+1;
        get_matching(card, win_nums[i], game_nums[i]);
        printf("card: [%d], matches: %d\n", card->game_id, card->matches);
    }
    uint64_t count = 0;
    int point = card_size;
    while (true){
        struct Cards card = cards[count];
        uint64_t old_size = card_size;
        card_size += card.matches;
        cards = realloc(cards, sizeof(*cards)* card_size);
        for(int i = card.game_id; i< card.game_id + card.matches; i++){
            cards[point].game_id = cards[i].game_id;
            cards[point].matches = cards[i].matches;
            point++;
        }
        count++;
        if (count == card_size)
            break;
    }
    printf("\ncards: %ld, count: %ld, point: %d\n", card_size, count, point);

    free(cards);

    for (int i = 0; i < rows; i++)
        free(file[i]);
    free(file);
    return 0;
}
