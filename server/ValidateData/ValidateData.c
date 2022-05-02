#include <stdio.h>

int DecideAccess(char *data){
    FILE *file = fopen("database/accounts.txt","r");
    char LetterFromFile = '1'; int runner = 3;
    while(1){
        fscanf(file,"%c",&LetterFromFile);
        if(LetterFromFile == '~'){
            fclose(file);
            return 0;
        }
        if(LetterFromFile == '\n'){
            fclose(file);
            return 1;
        } else if(LetterFromFile != data[runner]){
            runner = 3;
            while(LetterFromFile != '\n')
                fscanf(file,"%c",&LetterFromFile);
            continue;
        }
        runner++;
    }
}