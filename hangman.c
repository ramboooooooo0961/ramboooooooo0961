#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6

// Function to print the current state of the word
void printWord(char word[], char guessed[], int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (guessed[i] == 1)
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

// Function to select a random word from a list of words
void chooseRandomWord(char *word) {
    char *words[] = {
        "hangman", "programming", "computer", "developer", "language", "code", "challenge", "function", "debug", "variable"
    };
    int numWords = sizeof(words) / sizeof(words[0]);
    srand(time(NULL)); // Initialize random seed
    int randomIndex = rand() % numWords;
    strcpy(word, words[randomIndex]); // Copy the randomly selected word to the 'word' variable
}

int main() {
    char word[50]; // To store the selected word
    chooseRandomWord(word); // Choose a random word
    int wordLength = strlen(word);
    
    char guessed[wordLength]; // Keeps track of guessed letters (0 = not guessed, 1 = guessed)
    int wrongGuesses = 0;
    char guessedLetter;
    int guessedCorrectly;

    // Initialize guessed array
    for (int i = 0; i < wordLength; i++) {
        guessed[i] = 0; // All letters are initially not guessed
    }

    printf("Welcome to Hangman!\n");

    // Main game loop
    while (wrongGuesses < MAX_TRIES) {
        printf("\nGuess the word: ");
        printWord(word, guessed, wordLength);

        printf("Enter a letter: ");
        scanf(" %c", &guessedLetter);
        guessedLetter = tolower(guessedLetter); // Convert input to lowercase for simplicity

        // Check if the letter is in the word
        guessedCorrectly = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guessedLetter && guessed[i] == 0) {
                guessed[i] = 1; // Mark letter as guessed
                guessedCorrectly = 1;
            }
        }

        if (!guessedCorrectly) {
            wrongGuesses++;
            printf("Wrong guess! You have %d tries left.\n", MAX_TRIES - wrongGuesses);
        }

        // Check if the player has guessed all letters
        int allGuessed = 1;
        for (int i = 0; i < wordLength; i++) {
            if (guessed[i] == 0) {
                allGuessed = 0;
                break;
            }
        }

        if (allGuessed) {
            printf("Congratulations! You guessed the word: %s\n", word);
            break;
        }
    }

    if (wrongGuesses == MAX_TRIES) {
        printf("You lost! The word was: %s\n", word);
    }

    return 0;
}
