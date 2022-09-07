// Import required header files
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Define constants
#define MAX_LINE_LENGTH 100
#define NUM_WORD 50
#define MAX_INPUT_SIZE 3

// Declare the names of functions
void initialize_game_state(char word[], char game_state[], bool already_guessed[26]);
bool update_game_state(char guess, const char word[], char game_state[]);
void print_game_state(const char word[], char game_state[], bool already_guessed[26]);
char get_guess(void);
bool won(const char word[], char game_state[]);
bool previous_guess(char guess, bool already_guessed[26]);

// Define the global variable to draw the state of the game
char pic[8][20] = {"|||========|||", "|||", "|||", "|||", "|||", "|||", "|||", "================="};

void initialize_game_state(char word[], char game_state[], bool already_guessed[26]){
    /*
    Param:
        word: the string that represent the word
        game_state: the array that contains information on the game state. Each character can be an upper case char or "_"
        already_guess: the array tells information on what char has already been guessed
    
    Return: None

    This function initiates the game by modifying the three parameters. word will be chosen as random, game_state will be initiated as all "_" and already_guess will be all false
    */

   // Define variables to read words from the text file 
    FILE    *textfile;
    char    line[MAX_LINE_LENGTH];
    char    words[NUM_WORD][MAX_LINE_LENGTH];
    
    // Open the file, read it and store it in array words
    textfile = fopen("words.txt", "r");
    if(textfile == NULL)
        return;

    for (int i = 0; i<NUM_WORD; i++){
        fgets(line, MAX_LINE_LENGTH, textfile);
        strcpy(words[i], line);
    }
    // Close the file
    fclose(textfile);

    // Randomly select a word from that file
    srand(time(NULL)); 
    int chosen_index = rand() % NUM_WORD;
    int chosen_len = strlen(words[chosen_index])-1;
    char new_game_state[chosen_len];

    // Initate new game state
    for (int i = 0; i<chosen_len; i++){
        strcpy(&new_game_state[i], "_");
    }

    // Initiate already_guessed
    for (int i = 0; i<26; i++){
        already_guessed[i] = false;
    }
    // Initate game state
    strcpy(game_state, new_game_state);

    // Initate the chosen word and convert it to uppercase
    strcpy(word, words[chosen_index]);
    word[strcspn( word, "\n" )] = '\0';
    for (int i = 0; i< chosen_len; i++){
        word[i] = toupper(word[i]);
    }
}

bool update_game_state(char guess, const char word[], char game_state[]){
    /*
    Param:
        guess: the guessed character from the input
        word: the string that represent the word
        game_state: the array that contains information on the game state. Each character can be an upper case char or "_"
    
    Return: boolean value indicate whether the letter was in word (true for found in word, false otherwise)

    This function updates the game state based on the guessed character (Change "_" to the character at any locations it appears). 
    */

    // Initiate the boolean value to be false, meaning that the character is not in word initially
    bool found = false;
    for (int i = 0; i<strlen(word); i++){
        if (word[i] == guess){
            // If it is in word, change found to true and update game state
            found = true;
            game_state[i] = guess;
        }
    }
    return found;
}

void print_game_state(const char word[], char game_state[], bool already_guessed[26]){
    /*
    Param:
        word: the string that represent the word
        game_state: the array that contains information on the game state. Each character can be an upper case char or "_"
        already_guess: the array tells information on what char has already been guessed
    
    Return: None

    This function prints the game state, including the game_state array, the hangman picture and the number of misses.
    */

    // Calculate the total number of guesses
    int allGuess = 0;
    for (int i = 0; i<26; i++){
        if (already_guessed[i]){
            allGuess += 1;
        }
    }

    // Calculate the number of correct guess
    int correctGuess = 0;
    if (isalpha(game_state[0])){
        correctGuess = 1;
    }
    int i, j = 0;
    for (i = 1; i<strlen(word); i++){
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

    // Calculate the number of incorrect guess
    int incorrectGuess = allGuess - correctGuess;

    // Update the picture based on the number of incorrect guesses
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

    // If there was a guess, print the number of misses
    if (allGuess != 0){
        printf("Missed: %d\n", incorrectGuess);
    }
    printf("\n");

    // Print the hangman picture
    for (i = 0; i<8; i++){
        printf("%s\n", pic[i]);
    }
    printf("\n");

    // If we have not lost or won, print the game state and already guessed letters.
    if (incorrectGuess < 7 && !won(word, game_state)){
        for (i = 0; i<strlen(word); i++){
            if (i == strlen(word)-1){
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
    /*
    Param: None
    
    Return: None

    This function gets the input character from the user
    */

    // Initiate the guess array to only store 3 characters
    char guess[MAX_INPUT_SIZE];
    while (1){
        // Prompt the user for the input
        printf("What is your guess? ");
        fgets(guess, MAX_INPUT_SIZE, stdin);

        // If the user input 1 valid character and hit enter (\n), break the loop to return
        if (strlen(guess)==2 && isalpha(guess[0]) && strchr(guess, '\n') != NULL){
            break;
        } 
        // If the user only hit enter, continue to prompt for input
        else if (guess[0] == '\n') {
            continue;
        } 
        // Else, since fgets continue to read characters beyond MAX_INPUT_SIZE-1 in the buffer, we have to clear everything after it
        else {
            int c;
    	    while((c = getc(stdin)) != '\n' && c != EOF);
        }
    }

    // Return the first character
    return toupper(guess[0]);
}

bool won(const char word[], char game_state[]){
    /*
    Param:
        word: the string that represent the word
        game_state: the array that contains information on the game state. Each character can be an upper case char or "_"
    
    Return: a boolean indicates if the user has won (true for won, false otherwise)

    This function indicates if the player won
    */

    // The user wins if the game state contains only valid character
    for (int i = 0; i<strlen(word); i++){
        if (!isalpha(game_state[i])){
            return false;
        }
    }
    return true;
}

bool previous_guess(char guess, bool already_guessed[26]){
    /*
    Param:
        guess: the guessed character from the user
        already_guess: the array tells information on what char has already been guessed
    
    Return: a boolean value indicates if the character was already guessed (true for already guessed, false otherwise)

    This function checks if the character is already guessed and not penalize the user if it was already guessed.
    */
    
    // Find the index of the guess
    int num = guess - 'A';

    // If already guessed, then just return true
    if (already_guessed[num]){
        return already_guessed[num];
    }

    // If not, update the already_guess array and return false
    else {
        already_guessed[num] = true;
        return false;
    }
}