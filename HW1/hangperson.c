#include <stdio.h>
#include "hangfunctions.c"

int main(){
    char word[11];
    char game_state[11];
    bool already_guessed[26];
    char guessedChar;
    bool correct;

    initialize_game_state(word, game_state, already_guessed);
    do {
        print_game_state(word, game_state, already_guessed);
        guessedChar = get_guess();
        correct = update_game_state(guessedChar, word, game_state);
        if (correct){
            printf("Good guess.\n");
        }
        else {
            printf("Bad guess!\n");
        }
    } while (!won(word, game_state));
    return 0;
}