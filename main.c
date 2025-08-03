#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "secretWord.h"
#define FILE_SIZE 100
#define wordSizeMax 50
#define numberOfChances 10

int main(void)
{
    FILE* file = fopen("words.txt", "r");
    if(file)
    {
        char secretWord[wordSizeMax];
        char choice;
        printf("Devine le mot secret\n");
        printf("Vous avez droit à %d tentatives\n", numberOfChances);
        while(1)
        {
            printf("Souhaitez vous continuer la partie?(o = oui, n = non): ");
            scanf("%c", &choice);
            clearBuffer();

            switch(choice)
            {
                case 'o':
                case 'O':
                    unsigned int wordNumber = generateRandomNumber(1, FILE_SIZE);
                    getSecretWord(file, wordNumber, wordSizeMax, secretWord);
                    size_t len = strlen(secretWord) + 1;

                    char* secretWordCopy = malloc(len * sizeof(char));
                    char* guessedLetters = malloc(len * sizeof(char));

                    strcpy(secretWordCopy, secretWord);

                    initializeWithStars(guessedLetters, len);

                    gameLoop(secretWord, secretWordCopy, guessedLetters, numberOfChances);

                    free(secretWordCopy);
                    free(guessedLetters);
                    break;
                
                default:
                    printf("Fin de la partie\n");
                    return 0;
            }
        }

    }
}