#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define bool char
#define FALSE 0
#define TRUE 1

#define MAX_LINE_LENGTH 1000
#define NUM_WORD 50
#define MAX_INPUT_SIZE 3

extern char pic[8][20] = {"|||========|||", "|||", "|||", "|||", "|||", "|||", "|||", "================="};

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
    int chosen_len = strlen(words[chosen_index]);
    char new_game_state[chosen_len];
    for (int i = 0; i<chosen_len; i++){
        strcpy(&new_game_state[i], "_");
    }
    for (int i = 0; i<26; i++){
        already_guessed[i] = FALSE;
    }

    strncpy(game_state, new_game_state, chosen_len);
    strcpy(word, words[chosen_index]);
}

bool update_game_state(char guess, const char word[], char game_state[]){
    bool found = FALSE;
    for (int i = 0; i<strlen(word); i++){
        if (word[i] == guess){
            found = TRUE;
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
    for (i = 1; i<strlen(game_state); i++){
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
    for (i = 0; i<strlen(game_state)-1; i++){
        if (i == strlen(game_state)-1){
            printf("%c\n", game_state[i]);
        }
        else {
            printf("%c ", game_state[i]);
        }
    }
    printf("Already guessed: ");
    for (i = 0; i< 26; i++){
        if (already_guessed[i]) {
            char temp = 'a' + i;
            printf("%c", temp);
        }
    }
    printf("\n\n");
}

char get_guess(void){
    printf("What is your guess? ");
    char guess[MAX_INPUT_SIZE];
    fgets(guess, MAX_INPUT_SIZE, stdin);
    guess[strcspn( guess, "\n" )] = '\0';
    while(strlen(guess) != 1 && !isalpha(guess[0])){
        printf("What is your guess? ");
        fgets(guess, MAX_INPUT_SIZE, stdin);
        guess[strcspn( guess, "\n" )] = '\0';
    }
    return guess[0];
}

bool won(const char word[], char game_state[]){
    for (int i = 0; i<strlen(word); i++){
        int temp = word[i] - 'a';
        if (!game_state[temp]){
            return FALSE;
        }
    }
    return TRUE;
}

bool previous_guess(char guess, bool already_guessed[26]){
    int num = guess - 'a';
    return already_guessed[num];
}