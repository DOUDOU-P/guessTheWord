#ifndef SECRET_WORD_H_INCLUDED
    #define SECRET_WORD_H_INCLUDED
    #include<stdio.h>
    unsigned int generateRandomNumber(const unsigned int, const unsigned int);
    void getSecretWord(FILE*, const unsigned int, const unsigned int, char* word);
    void initializeWithStars(char*, const size_t);
    void gameLoop(const char*, char*, char*, unsigned int);
    void clearBuffer();
#endif