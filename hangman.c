#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRIES 6

// Define a structure to store the word and its category/definition
typedef struct {
    char word[100];
    char category[100];
} Word;

void printHangman(int tries) {
    switch (tries) {
        case 0:
            printf("\n\n\n\n\n");
            break;
        case 1:
            printf("\n  -----\n  |   |\n  |\n  |\n  |\n  |\n-----\n");
            break;
        case 2:
            printf("\n  -----\n  |   |\n  |   O\n  |\n  |\n  |\n-----\n");
            break;
        case 3:
            printf("\n  -----\n  |   |\n  |   O\n  |   |\n  |\n  |\n-----\n");
            break;
        case 4:
            printf("\n  -----\n  |   |\n  |   O\n  |  /|\n  |\n  |\n-----\n");
            break;
        case 5:
            printf("\n  -----\n  |   |\n  |   O\n  |  /|\\\n  |\n  |\n-----\n");
            break;
        case 6:
            printf("\n  -----\n  |   |\n  |   O\n  |  /|\\\n  |  /\n  |\n-----\n");
            break;
        case 7:
            printf("\n  -----\n  |   |\n  |   O\n  |  /|\\\n  |  / \\\n  |\n-----\n");
            break;
        default:
            break;
    }
}

// Function to select a random word from the list
void selectWord(Word *selectedWord) {
    // Array of words with their categories (hints)
    Word words[] = {
        {"programming", "A field of study involving writing code"},
        {"computer", "An electronic device for processing data"},
        {"hangman", "A popular word-guessing game"},
        {"developer", "A person who writes code"},
        {"puzzle", "A game or problem designed to test ingenuity"}
    };
    int wordCount = 5;

    // Select a random word from the list
    int index = rand() % wordCount;
    *selectedWord = words[index];
}

// Function to give a hint (reveal the category of the word)
void giveHint(Word selectedWord) {
    printf("\nHint: The word belongs to the category: %s\n", selectedWord.category);
}

int main() {
    Word selectedWord;
    char guessedWord[100];
    int tries = 0;
    int wordLength;
    char guess;
    int gameWon = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Select a random word
    selectWord(&selectedWord);
    wordLength = strlen(selectedWord.word);

    // Initialize the guessed word with underscores
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[wordLength] = '\0';

    // Game loop
    while (tries < MAX_TRIES) {
        printf("\nWord: %s\n", guessedWord);
        printf("Tries left: %d\n", MAX_TRIES - tries);
        printf("Would you like a hint? (y/n): ");
        
        char hintChoice;
        scanf(" %c", &hintChoice);

        if (hintChoice == 'y' || hintChoice == 'Y') {
            giveHint(selectedWord);
        }

        printf("Enter a letter: ");
        scanf(" %c", &guess);  // Take user input

        // Check if the guessed letter is in the word
        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (selectedWord.word[i] == guess && guessedWord[i] == '_') {
                guessedWord[i] = guess;
                found = 1;
            }
        }

        if (!found) {
            tries++;
            printHangman(tries);
        }

        // Check if the player has guessed the whole word
        if (strcmp(selectedWord.word, guessedWord) == 0) {
            printf("Congratulations! You guessed the word: %s\n", selectedWord.word);
            gameWon = 1;
            break;
        }
    }

    if (!gameWon) {
        printf("\nGame Over! The word was: %s\n", selectedWord.word);
    }

    return 0;
}
