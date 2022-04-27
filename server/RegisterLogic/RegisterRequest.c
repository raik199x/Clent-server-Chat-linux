#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../functions.h"

char *GenerateRecoveryKey(){
    char *RecKey = (char*)malloc(201); char *response;
    char *Letters = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    srand(time(NULL));
    for(int i = 0; i < 200;i++){
        unsigned int temp = rand()%62;
        RecKey[i] = Letters[temp];
    }
    RecKey[200] = '\0';
    if(RecKey[0] == 'b' && RecKey[1] == 'a' && RecKey[2] == 'd')
        RecKey = GenerateRecoveryKey();
    //now we need to write + check recovery keys
    FILE *RecKeys = fopen("database/recovery_keys.txt","r+");
    if(!RecKeys){
        //there is no instructions for registered login+pass
        SetOutputColor("RED");
        printf("CRITICAL ERROR: file 'database/recovery_keys.txt' is not found!\n");
        SetOutputColor("def");
        free(RecKey);
        RawStringToCharPointer(&response,"bad\0");
        return response;
    }
    char LetterFromFile = '1'; unsigned int i = 0;
    while(LetterFromFile != '~'){
        fscanf(RecKeys,"%c",&LetterFromFile);
        if(LetterFromFile == '~')
            break;
        if(LetterFromFile == '\n'){
            SetOutputColor("YELLOW");
            printf("WARNING: recovery key function generate existing key, repeating task\n");
            SetOutputColor("def");
            fclose(RecKeys);
            free(RecKey);
            RecKey = GenerateRecoveryKey();
            return RecKey;
        } else if(LetterFromFile != RecKey[i++]){
            i = 0;
            while(LetterFromFile != '\n')
                fscanf(RecKeys,"%c",&LetterFromFile);
        }
    }
    //if all checkers are passed
    fseek(RecKeys,-1,SEEK_CUR);
    for(int i = 0;i < 200;i++)
        fprintf(RecKeys,"%c",RecKey[i]);
    fprintf(RecKeys,"\n~");
    fclose(RecKeys);
    printf("LOG: Recovery Key generated successfully\n");
    return RecKey;
}

char* RegisterClient(const char *data){
    char *Nickname, *Password, *RecoveryKey, *response;
    Nickname = (char*)malloc(17);
    Password = (char*)malloc(101);

    //Parse login + password
    unsigned int i = 3, j = 0;
    for(j = 0; data[i] != ':';i++,j++)
        Nickname[j] = data[i];
    Nickname[j] = '\0'; i++;
    for(j = 0; data[i] != '\0'; i++,j++)
        Password[j] = data[i];
    Password[j] = '\0';

    //running through file and check if such username is already taken
    FILE *ClientsData = fopen("database/accounts.txt","r+");
    if(!ClientsData){
        SetOutputColor("RED");
        printf("CRITICAL ERROR: file 'database/accounts.txt' is not found!\n");
        SetOutputColor("def");
        free(Nickname); free(Password);
        RawStringToCharPointer(&response,"critical\0");
        return response;
    }

    char LetterFromFile = '1'; i = 0;
    while(LetterFromFile != '~'){
        fscanf(ClientsData,"%c",&LetterFromFile);
        if(LetterFromFile == '~')
            break;
        if(LetterFromFile == ':'){
            SetOutputColor("YELLOW");
            printf("WARNING: some client tried to register with an existing nickname\n");
            SetOutputColor("def");
            free(Nickname); free(Password);
            RawStringToCharPointer(&response,"exist\0");
            return response;
        } else if(LetterFromFile != Nickname[i++]){
             //if nickname is not equal to our new
            //we simply skip the whole line
            while(LetterFromFile != '\n')
                fscanf(ClientsData,"%c",&LetterFromFile);
            i=0;
        }
        //if such nickname already exist
    }
    //if we decided to register client we go back by one symbol
    fseek(ClientsData,-1,SEEK_CUR);
    //writting new data
    i = 3;
    while(data[i] != '\0')
        fprintf(ClientsData,"%c",data[i++]);
    fprintf(ClientsData,"\n~");
    fclose(ClientsData);            //end working with client credintals

    printf("LOG: %s\n",data);


    RecoveryKey = GenerateRecoveryKey(); //generating recovery key;
    //add error handling
    free(Nickname); free(Password);
    return RecoveryKey;
}