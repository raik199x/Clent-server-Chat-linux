#include <stdio.h>
#include <malloc.h>
#include "../functions.h"

char *RecoverClient(const char *RecKey){
    FILE *file = fopen("database/recovery_keys.txt","r+");
    char *response;
    //finding key
    char LetterFromFile = '1'; unsigned int i = 3; unsigned long long FileLine = 0;
    while(LetterFromFile != '~'){
        fscanf(file,"%c",&LetterFromFile);
        if(LetterFromFile == '~'){
            RawStringToCharPointer(&response,"notexist\0");
            SetOutputColor("YELLOW");
            printf("WARNING: some client send not existing recovery key\n");
            SetOutputColor("def");
            return response;
        }
        if(LetterFromFile == '\n')
            break;
        else if(LetterFromFile != RecKey[i]){
            while(LetterFromFile != '\n')
                fscanf(file,"%c",&LetterFromFile);
            i = 3;
            FileLine++;
            continue;
        }
        i++;
    }
    //if key was found, time to read data from file
    fclose(file);
    file = fopen("database/accounts.txt","r+");

    LetterFromFile = '1';
    //running through data to find needed creditals
    for(unsigned long long j = 0; j != FileLine;){
        fscanf(file,"%c",&LetterFromFile);
        if(LetterFromFile == '\n')
            j++;
    }
    response = (char*)malloc(119); //(maxlogin)16 + (maxpassword)100 + (:\0)2 + (to be save =))1
    LetterFromFile = '1'; FileLine = 0;
    while(1){
        fscanf(file,"%c",&LetterFromFile);
        if(LetterFromFile == '\n'){
            response[FileLine] = '\0';
            printf("LOG: client recovered data\n");
            return response;
        }
        response[FileLine++] = LetterFromFile;
    }
}