#include <stdio.h>
#include "hangfunctions.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int test_initialize_game_state();
int test_update_game_state();
int test_print_game_state();
int test_get_guess();
int test_won();
int test_previous_guess();

int main(){
    assert(test_initialize_game_state() == 0);
    printf("Initialize successful!\n");
    assert(test_previous_guess() == 0);
    printf("Previous test successful!\n");
    assert(test_get_guess() == 0);
    printf("Get guess successful!\n");
    return 0;
}

int test_initialize_game_state() {
    // Test 1
    char word[20];
    char game_state[30];
    bool already_guessed[26];
    initialize_game_state(word, game_state, already_guessed);
    int word_len = strlen(word)-1;
    bool word_check = true;
    bool game_state_check = true;
    bool already_guessed_check = true;

    for (int i = 0; i<word_len; i++){
        if (!isalpha(word[i])){
            word_check = false;
        }
        if (game_state[i] != '_'){
            game_state_check = false;
        }
    }
    for (int i = 0; i<26; i++){
        if (already_guessed[i]){
            already_guessed_check = false;
        }
    }
    assert(word_check == true);
    assert(game_state_check == true);
    assert(already_guessed_check == true);
    assert(strlen(word) == strlen(game_state));
    assert(strlen(word) != 20);
    assert(strlen(game_state) != 30);

    return 0;
}

int test_get_guess() {
    char guess;

    // Test 1
    guess = get_guess();
    assert(guess == 'A');

    // Test 2
    guess = get_guess();
    assert(guess == 'D');

    // Test 3
    guess = get_guess();
    assert(guess == 'Y');

    // Test 4
    guess = get_guess();
    assert(guess == 'A');

    // Test 5
    guess = get_guess();
    assert(guess == 'R');

    return 0;
}

int test_won() {

}

int test_previous_guess() {
    // test 1
    char guess = 'F';
    int indx = guess - 'A';
    bool already_guessed[26];
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    assert(already_guessed[indx] == false);
    assert(previous_guess(guess, already_guessed) == false);
    assert(already_guessed[indx] == true);

    // test 2
    guess = 'G';
    indx = guess - 'A';
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    already_guessed[indx] = true;
    assert(already_guessed[indx] == true);
    assert(previous_guess(guess, already_guessed) == true);
    assert(already_guessed[indx] == true);

    return 0;
}