#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 1000
#define NUM_WORD 50
#define ALLOWED_INPUT_SIZE 3
int main() {
    // FILE    *textfile;
    // char    line[MAX_LINE_LENGTH];
    // char    words[50][MAX_LINE_LENGTH];
     
    // textfile = fopen("words.txt", "r");
    // if(textfile == NULL)
    //     return 1;

    // for (int i = 0; i<50; i++){
    //     fgets(line, MAX_LINE_LENGTH, textfile);
    //     strcpy(words[i], line);
    //     printf("%s", words[i]);
    // }
     
    // fclose(textfile);

    // time_t t;

    // srand((unsigned) time(&t));
    // int chosen_index = rand();
    // printf("%d", chosen_index);
    // return 0;

    printf("Enter a word: ");
    char guess[ALLOWED_INPUT_SIZE];
    fgets(guess, ALLOWED_INPUT_SIZE, stdin);
    fflush(stdin);
    guess[strcspn( guess, "\n" )] = '\0';
    // printf("%d", strlen(guess));
    while(strlen(guess) != 1 || !isalpha(guess[0])){
        printf("Enter a word: ");
        fgets(guess, ALLOWED_INPUT_SIZE, stdin);
        fflush(stdin);
        guess[strcspn( guess, "\n" )] = '\0';
        printf("%d", strlen(guess));
    }
    printf("%d", strlen(guess));

    // char a = '_';
    // printf("%c", a);
}

