#include<stdio.h>

#define bool char
#define FALSE 0
#define TRUE 1

void initialize_game_state(char word[], char game_state[], bool already_guessed[26]){
    
}

bool update_game_state(char guess, const char word[], char game_state[]){

}

void print_game_state(const char word[], char game_state[], bool already_guessed[26]){

}

char get_guess(void){

}

bool won(const char word[], char game_state[]){

}

bool previous_guess(char guess, bool already_guessed[26]){
    int num = guess - 'a';
    return already_guessed[num];
}