// Import required header files
#include <stdio.h>
#include "hangfunctions.h"
#include <stdbool.h>
#include <string.h>

// Define constants
#define MAX_WORD_SIZE 20
#define NUM_CHAR 26

int main(){
    // Declare variables
    char word[MAX_WORD_SIZE];
    char game_state[MAX_WORD_SIZE];
    bool already_guessed[NUM_CHAR];
    char guessedChar;
    bool correct;
    int wrong = 0;

    // Initialize the game
    initialize_game_state(word, game_state, already_guessed);
    
    // While loop until we win or lose
    do {
        // Print game state
        print_game_state(word, game_state, already_guessed);

        // Get guess from user
        bool validChar;
        guessedChar = get_guess();
        validChar = previous_guess(guessedChar, already_guessed);
        // Re-prompt if already guessed
        while (validChar) {
            printf("Already Guessed. ");
            guessedChar = get_guess();
            validChar = previous_guess(guessedChar, already_guessed);
        };

        // Update game state and check if the character is correct
        correct = update_game_state(guessedChar, word, game_state);

        // If the guess is correct
        if (correct){
            printf("Good guess.\n");
        }
        // If bad guess, increase wrong count
        else {
            printf("Bad guess!\n");
            wrong++;
        }
    } while (!won(word, game_state) && wrong < 7);

    // If win, print the winning message
    if (won(word, game_state)){
        print_game_state(word, game_state, already_guessed);
        printf("Congratulations! The word was %.*s.\n", (int)(strlen(word)), word);
    }
    // If lose, print the losing message
    else {
        print_game_state(word, game_state, already_guessed);
        printf("You lost and made stick-person sad...\n");
        printf("The word was %.*s.\n", (int)(strlen(word)), word);
    }
    return 0;
}
