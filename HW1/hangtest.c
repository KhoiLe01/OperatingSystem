#include <stdio.h>
#include "hangfunctions.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

int test_initialize_game_state();
int test_update_game_state();
int test_print_game_state();
int test_get_guess();
int test_won();
int test_previous_guess();

int main(){
	// Test for initialize game state
    assert(test_initialize_game_state() == 0);
    printf("Initialize successful!\n");
    
    // Test for previous guess
    assert(test_previous_guess() == 0);
    printf("Previous test successful!\n");
    
    // Test for get guess
    assert(test_get_guess() == 0);
    printf("Get guess successful!\n");
    
    // Test for won
    assert(test_won() == 0);
    printf("Won successful!\n");
    
    // Test for update game state
    assert(test_update_game_state() == 0);
    printf("Update game state successful!\n");
    printf("\n");
    // Test for print game state
    assert(test_print_game_state() == 0);
    printf("Print game state successful!\n");
    
    printf("All test cases passed!\n");
    
    return 0;
}

int test_initialize_game_state() {
    // Test 1: Initialize a game and check for the length, etc.
    char word[20];
    char game_state[30];
    bool already_guessed[26];
    initialize_game_state(word, game_state, already_guessed);
    int word_len = strlen(word);
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

int test_update_game_state(){
	char guess;
	char word[20];
	char game_state[20];
	
	// Test 1: Guess correct 2 letters
	strcpy(word, "HELLO");
	strcpy(game_state, "HE__O");
	guess = 'L';
	assert(strlen(word) == strlen(game_state));
	assert(update_game_state(guess, word, game_state) == true);
	assert(strcmp(word, game_state) == 0);
	
	// Test 2: Wrong guess
	strcpy(word, "HELLO");
	strcpy(game_state, "HE__O");
	guess = 'K';
	assert(strlen(word) == strlen(game_state));
	assert(update_game_state(guess, word, game_state) == false);
	assert(strcmp(word, game_state) != 0);
	assert(strcmp("HE__O", game_state) == 0);
	
	// Test 3: 2 correct guess 
	strcpy(word, "ACTIVITY");
	strcpy(game_state, "ACT_V_T_");
	guess = 'I';
	assert(strlen(word) == strlen(game_state));
	assert(update_game_state(guess, word, game_state) == true);
	assert(strcmp(word, game_state) != 0);
	assert(strcmp("ACTIVIT_", game_state) == 0);
	
	// Test 4: Update game state from empty
	strcpy(word, "ACTIVITY");
	strcpy(game_state, "________");
	guess = 'I';
	assert(strlen(word) == strlen(game_state));
	assert(update_game_state(guess, word, game_state) == true);
	assert(strcmp(word, game_state) != 0);
	assert(strcmp("___I_I__", game_state) == 0);
	
	// Test 5: wrong guess from empty
	strcpy(word, "ACTIVITY");
	strcpy(game_state, "________");
	guess = 'X';
	assert(strlen(word) == strlen(game_state));
	assert(update_game_state(guess, word, game_state) == false);
	assert(strcmp(word, game_state) != 0);
	assert(strcmp("________", game_state) == 0);
	
	// Test 6
	strcpy(word, "ABCDEFGHI");
	strcpy(game_state, "ABC______");
	guess = 'F';
	assert(strlen(word) == strlen(game_state));
	assert(update_game_state(guess, word, game_state) == true);
	assert(strcmp(word, game_state) != 0);
	assert(strcmp("ABC__F___", game_state) == 0);
	
	// Note: test case where the guess is a letter in game_state is not realistic because 
	// previous_guess() already guarantee to not pick repeated character.
	return 0;
}

int test_print_game_state(){
	char word[20];
	char game_state[20];
	bool already_guessed[26];
	
	// Test 1:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LL_");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 2:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LL_");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['A'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 3:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LL_");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['A'-'A'] = true;
	already_guessed['B'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 4:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LL_");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['A'-'A'] = true;
	already_guessed['B'-'A'] = true;
	already_guessed['C'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 5:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LLO");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['O'-'A'] = true;
	already_guessed['A'-'A'] = true;
	already_guessed['B'-'A'] = true;
	already_guessed['C'-'A'] = true;
	already_guessed['D'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 6:
	strcpy(word, "HELLO");
	strcpy(game_state, "HELL_");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['E'-'A'] = true;
	already_guessed['A'-'A'] = true;
	already_guessed['B'-'A'] = true;
	already_guessed['C'-'A'] = true;
	already_guessed['D'-'A'] = true;
	already_guessed['F'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 7:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LLO");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['O'-'A'] = true;
	already_guessed['A'-'A'] = true;
	already_guessed['B'-'A'] = true;
	already_guessed['C'-'A'] = true;
	already_guessed['D'-'A'] = true;
	already_guessed['F'-'A'] = true;
	already_guessed['G'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Test 8:
	strcpy(word, "HELLO");
	strcpy(game_state, "H_LL_");
	for (int i = 0; i < 26; i++){
		already_guessed[i] = false;
	}
	already_guessed['H'-'A'] = true;
	already_guessed['L'-'A'] = true;
	already_guessed['A'-'A'] = true;
	already_guessed['B'-'A'] = true;
	already_guessed['C'-'A'] = true;
	already_guessed['D'-'A'] = true;
	already_guessed['F'-'A'] = true;
	already_guessed['G'-'A'] = true;
	already_guessed['I'-'A'] = true;
	print_game_state(word, game_state, already_guessed);
	
	// Note: test 8 does not print out the game_state because it is the end of the game,
	// the end message should pop up instead of the game_state
	
	return 0;
	
}

int test_get_guess() {
    char guess;

    // Test 1: test to handle input more than 1 letter and accept an uppercase letter
    guess = get_guess_for_testing();
    assert(guess == 'A');

    // Test 2: test to handle empty input and accept 1 lowercase letter
    guess = get_guess_for_testing();
    assert(guess == 'D');

    // Test 3: combination of test 1 and 2
    guess = get_guess_for_testing();
    assert(guess == 'Y');

    // Test 4: handle 1 non-character and accept a lower case letter
    guess = get_guess_for_testing();
    assert(guess == 'A');

    // Test 5: handle empty input, multiple non-character letters, 1 non-character letter, multiple letters and accept a lowercase letter.
    guess = get_guess_for_testing();
    assert(guess == 'R');
    
    // Test 6: Literally everything
    guess = get_guess_for_testing();
    assert(guess == 'H');
    
    return 0;
}

int test_won() {
	char word[20];
	char game_state[20];
	
	// Test 1: Not win by 2 letters
	strcpy(word, "HELLO");
	strcpy(game_state, "HE__O");
	assert(strlen(word) == strlen(game_state));
	assert(won(word, game_state) == false);
	
	// Test 2: Win
	strcpy(word, "ACTIVITY");
	strcpy(game_state, "ACTIVITY");
	assert(strlen(word) == strlen(game_state));
	assert(won(word, game_state) == true);
	
	// Test 3: Not win by 1 letter
	strcpy(word, "ENVY");
	strcpy(game_state, "ENV_");
	assert(strlen(word) == strlen(game_state));
	assert(won(word, game_state) == false);
	
	// Test 4: Not win by most of the letters
	strcpy(word, "DESTROY");
	strcpy(game_state, "D______");
	assert(strlen(word) == strlen(game_state));
	assert(won(word, game_state) == false);
	
	// Test 5
	strcpy(word, "HAPPY");
	strcpy(game_state, "_APP_");
	assert(strlen(word) == strlen(game_state));
	assert(won(word, game_state) == false);
	
	// Test 6: Not guessed yet
	strcpy(word, "HOMEWORK");
	strcpy(game_state, "________");
	assert(strlen(word) == strlen(game_state));
	assert(won(word, game_state) == false);
	
	return 0;
}

int test_previous_guess() {
    // Test 1: Check if it change when not guessed and return false
    char guess = 'F';
    int indx = guess - 'A';
    bool already_guessed[26];
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    assert(already_guessed[indx] == false);
    assert(previous_guess(guess, already_guessed) == false);
    assert(already_guessed[indx] == true);

    // Test 2: Check if it does not change when already guessed
    guess = 'G';
    indx = guess - 'A';
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    already_guessed[indx] = true;
    assert(already_guessed[indx] == true);
    assert(previous_guess(guess, already_guessed) == true);
    assert(already_guessed[indx] == true);
    
    // Test 3: Check if it does not change anything other than the exact index
    guess = 'G';
    indx = guess - 'A';
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    already_guessed[0] = true;
    already_guessed[25] = true;
    already_guessed[10] = true;
    already_guessed[indx-1] = true;
    already_guessed[indx+1] = true;
    assert(already_guessed[indx] == false);
    assert(previous_guess(guess, already_guessed) == false);
    assert(already_guessed[indx] == true);
    assert(already_guessed[indx+1] == true);
    assert(already_guessed[indx-1] == true);
    assert(already_guessed[0] == true);
    assert(already_guessed[25] == true);
    assert(already_guessed[10] == true);
    
    // Test 4: Check if the guess is not changed
    guess = 'K';
    indx = guess - 'A';
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    already_guessed[indx] = true;
    assert(already_guessed[indx] == true);
    assert(previous_guess(guess, already_guessed) == true);
    assert(already_guessed[indx] == true);
    assert(guess == 'K');

    return 0;
}
