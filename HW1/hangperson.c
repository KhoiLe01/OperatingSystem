#include <stdio.h>
#include "hangfunctions.c"

int main(){
    char word[20];
    char game_state[20];
    bool already_guessed[26];
    char guessedChar;
    bool correct;
    int wrong = 0;

    initialize_game_state(word, game_state, already_guessed);
    printf("%s\n", word);
    printf("%d\n", strlen(word));
    printf("last %c\n", word[strlen(word)-1]);
    do {
        print_game_state(word, game_state, already_guessed);
        bool validChar;
        guessedChar = get_guess();
        validChar = previous_guess(guessedChar, already_guessed);
        while (validChar) {
            printf("Already Guessed. ");
            guessedChar = get_guess();
            validChar = previous_guess(guessedChar, already_guessed);
        };

        correct = update_game_state(guessedChar, word, game_state);
        if (correct){
            printf("Good guess.\n");
        }
        else {
            printf("Bad guess!\n");
            wrong++;
        }
    } while (!won(word, game_state) && wrong < 7);
    if (won(word, game_state)){
        printf("Congratulations! The word was %.*s.", strlen(word)-1, word);
    }
    else {
        print_game_state(word, game_state, already_guessed);
    }
    return 0;
}