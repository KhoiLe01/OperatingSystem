#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000
#define NUM_WORD 50
#define MAX_INPUT_SIZE 3

void initialize_game_state(char word[], char game_state[], bool already_guessed[26]);
bool update_game_state(char guess, const char word[], char game_state[]);
void print_game_state(const char word[], char game_state[], bool already_guessed[26]);
char get_guess(void);
bool won(const char word[], char game_state[]);
bool previous_guess(char guess, bool already_guessed[26]);


char pic[8][20] = {"|||========|||", "|||", "|||", "|||", "|||", "|||", "|||", "================="};

void initialize_game_state(char word[], char game_state[], bool already_guessed[26]){
    FILE    *textfile;
    char    line[MAX_LINE_LENGTH];
    char    words[NUM_WORD][MAX_LINE_LENGTH];
     
    textfile = fopen("words.txt", "r");
    if(textfile == NULL)
        return;

    for (int i = 0; i<NUM_WORD; i++){
        fgets(line, MAX_LINE_LENGTH, textfile);
        strcpy(words[i], line);
    }
     
    fclose(textfile);

    srand(time(NULL)); 
    int chosen_index = rand() % NUM_WORD;
    int chosen_len = strlen(words[chosen_index])-1;
    char new_game_state[chosen_len];
    for (int i = 0; i<chosen_len; i++){
        strcpy(&new_game_state[i], "_");
    }
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }

    strncpy(game_state, new_game_state, chosen_len);
    strcpy(word, words[chosen_index]);
    for (int i = 0; i< chosen_len; i++){
        word[i] = toupper(word[i]);
    }
}

bool update_game_state(char guess, const char word[], char game_state[]){
    bool found = false;
    for (int i = 0; i<strlen(word)-1; i++){
        if (word[i] == guess){
            found = true;
            game_state[i] = guess;
        }
    }
    return found;
}

void print_game_state(const char word[], char game_state[], bool already_guessed[26]){
    int allGuess = 0;
    for (int i = 0; i<26; i++){
        if (already_guessed[i]){
            allGuess += 1;
        }
    }

    int correctGuess = 0;
    if (isalpha(game_state[0])){
        correctGuess = 1;
    }
    int i, j = 0;
    for (i = 1; i<strlen(word)-1; i++){
        if (isalpha(game_state[i])){
            for (j = 0; j<i; j++){
                if (game_state[i] == game_state[j]){
                    break;
                }
            }
            if (i == j){
                correctGuess += 1;
            }
        }
    }
    int incorrectGuess = allGuess - correctGuess;

    switch(incorrectGuess){
        case 1:
            strcpy(pic[1], "||| |");
            break;
        case 2:
            strcpy(pic[2], "||| O");
            break;
        case 3:
            strcpy(pic[3], "||| /");
            break;
        case 4:
            strcpy(pic[3], "||| /|");
            break;
        case 5:
            strcpy(pic[3], "||| /|\\");
            break;
        case 6:
            strcpy(pic[4], "||| /");
            break;
        case 7:
            strcpy(pic[4], "||| / \\");
            break;
        default:
            break;
    }
    if (allGuess != 0){
        printf("Missed: %d\n", incorrectGuess);
    }
    printf("\n");
    for (i = 0; i<8; i++){
        printf("%s\n", pic[i]);
    }
    printf("\n");
    if (incorrectGuess < 7 && !won(word, game_state)){
        for (i = 0; i<strlen(word)-1; i++){
            if (i == strlen(word)-2){
                printf("%c\n", game_state[i]);
            }
            else {
                printf("%c ", game_state[i]);
            }
        }
        printf("Already guessed: ");
        for (i = 0; i< 26; i++){
            if (already_guessed[i]) {
                char temp = 'A' + i;
                printf("%c", temp);
            }
        }
        printf("\n\n");
    }
};

char get_guess(void){
    char guess[MAX_INPUT_SIZE];
    while (1){
        printf("What is your guess? ");
        fgets(guess, MAX_INPUT_SIZE, stdin);
        //guess[strcspn( guess, "\n" )] = '\0';
        //printf("%d\n", strlen(guess));
        if (strlen(guess)==2 && isalpha(guess[0]) && strchr(guess, '\n') != NULL){
            break;
        } else if (guess[0] == '\n') {
            continue;
        } 
        else {
            int c;
    	    while((c = getc(stdin)) != '\n' && c != EOF);
        }
    }
    return toupper(guess[0]);
}

bool won(const char word[], char game_state[]){
    for (int i = 0; i<strlen(word)-1; i++){
        if (!isalpha(game_state[i])){
            return false;
        }
    }
    return true;
}

bool previous_guess(char guess, bool already_guessed[26]){
    int num = guess - 'A';
    if (already_guessed[num]){
        return already_guessed[num];
    }
    else {
        already_guessed[num] = true;
        return false;
    }
}