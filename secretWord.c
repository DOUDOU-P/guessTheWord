#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "secretWord.h"
unsigned int generateRandomNumber(const unsigned int min, const unsigned int max)
{
    srand(time(0));
    return (min + rand() % (max - min + 1));
}
void getSecretWord(FILE* file, const unsigned int wordNumber, const unsigned int wordSizeMax, char* secretWord)
{
    fseek(file, 0, SEEK_SET);
    for(short i = 0; i < wordNumber; ++i)
        fgets(secretWord, wordSizeMax, file);
    
    size_t len = strlen(secretWord);

    if(len > 0 && secretWord[len - 1] == '\n')
        secretWord[--len] = '\0';

    // For Windows \r
    if(len > 0 && secretWord[len - 1] == '\r')
        secretWord[--len] = '\0';
}
void initializeWithStars(char* string, const size_t len)
{
    short i;
    for(i = 0; i < len - 1; i++)
        *(string + i) = '*';

    *(string + i) = '\0';
}

void clearBuffer()
{
    while(getchar() != '\n');
}
void gameLoop(const char* secretWord, char* secretWordCopy, char* guessedLetters, unsigned int numberOfChances)
{
    int guessed = 0;
    do
    {
        printf("Il vous reste %d tentatives\n", numberOfChances);
        printf("Quel lettre se trouve dans le mot secret: ");
        char userLetter;
        scanf("%c", &userLetter);
        clearBuffer();

        while(1)
        {
            char* letter = strchr(secretWordCopy, userLetter);
            if(letter)
            {
                guessedLetters[letter - secretWordCopy] = *letter;
                secretWordCopy[letter - secretWordCopy] = '.';
            }

            else
                break;
        }

        if(!strcmp(secretWord, guessedLetters))
        {
            guessed = 1;
            break;
        }

        else
        {
            printf("Lettres devinees: %s\n", guessedLetters);
            --numberOfChances;
        }
        
    } while (numberOfChances > 0);

    if(guessed)
        printf("Bravo, le mot secret etait %s\n", secretWord);
    
    else
        printf("Desolé, vous n'avez pas devine le mot secret qui etait %s\n", secretWord);
    
}