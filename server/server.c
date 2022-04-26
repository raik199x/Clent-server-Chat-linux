// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "functions.h"

#define PORT 3002

struct sockaddr_in address;
int addrlen = sizeof(address);
int *ActiveClients, NumberClients = 0;

void *WorkingWithClient(void *arg){
    int *client = (int *)arg;

    char *buffer = (char*)malloc(sizeof(char)); buffer[0] = '1';
    while(buffer[0] != '#'){
        free(buffer);
        buffer = (char*)malloc(255);
        recvfrom((*client), buffer, 255, 0,(struct sockaddr*)&address, (socklen_t*)&addrlen);
        if(buffer[0] == '\0')
            continue;
        printf("message: %s\n",buffer);
    }
    free(buffer);
    printf("Client exited\n");
    (*client) = -1;
    close((*client));
    pthread_exit(NULL);
}

int CheckAllFiles(){
    DIR* dir = opendir("database");
    if (dir)
        closedir(dir);
    else if (ENOENT == errno) {
        int check = mkdir("database",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(check){
            printf("Error creating folder!\n");
            return -1;
        }
    }else {
        printf("Unexpected error: Cannot check existing file\n");
        return -1;
    }
    FILE *file = fopen("database/accounts.txt","r+");
    if(!file){
        file = fopen("database/accounts.txt","w");
        fprintf(file,"\0");
    }
    fclose(file);
    file = fopen("database/recovery_keys.txt","r+");
    if(!file){
        file = fopen("database/recovery_keys.txt","w");
        fprintf(file,"\0");
    }
    fclose(file);
    return 0;
}

char *GenerateRecoveryKey(){
    char *RecKey = (char*)malloc(201);
    for(int i = 0; i < 200;i++){
        unsigned int temp = rand()%26+1;
        RecKey[i] = temp+96;
    }
    if(RecKey[0] = 'b' && RecKey[1] == 'a' && RecKey[2] == 'd')
        RecKey = GenerateRecoveryKey();
    //now we need to write + check recovery keys
    FILE *RecKeys = fopen("database/recovery_keys.txt","r+");
    if(!RecKeys){
        SetOutputColor("RED");
        printf("CRITICAL ERROR: file 'database/recovery_keys.txt' is not found!\n");
        SetOutputColor("def");
        return "bad\0";
    }
    char LetterFromFile = '1'; unsigned int i = 0;
    while(LetterFromFile != '\0'){
        fscanf(RecKeys,"%c",&LetterFromFile);
        if(LetterFromFile != RecKey[i++]){
            i = 0;
            while(LetterFromFile != '\n')
                fscanf(RecKeys,"%c",&LetterFromFile);
        } else if(LetterFromFile == '\n'){
            SetOutputColor("YELLOW");
            printf("WARNING: recovery key function generate existing key\n");
            SetOutputColor("def");
            return "rep\0";
        }
    }
    //if all checkers are passed
    fpos_t temp;
    fgetpos(RecKeys,&temp);
    fseek(RecKeys,-1,SEEK_CUR);
    for(int i = 0;i < 199;i++)
        fprintf(RecKeys,"%c",RecKey[i]);
    fprintf(RecKeys,"\n\0");
    return RecKey;
}

char* RegisterClient(const char *data){
    char *Nickname, *Password, *RecoveryKey;
    Nickname = (char*)malloc(17);
    Password = (char*)malloc(101);

    //Parse login + password
    unsigned int i = 3, j = 0;
    for(j = 0; data[i] != ':';i++,j++)
        Nickname[j] = data[i];
    Nickname[++j] = '\0'; i++;
    for(j = 0; data[i] != '\0'; i++,j++)
        Password[j] = data[i];
    Password[++j] = '\0';

    //running through file and check if such username is already taken
    FILE *ClientsData = fopen("database/accounts.txt","r+");
    if(!ClientsData){
        SetOutputColor("RED");
        printf("CRITICAL ERROR: file 'database/accounts.txt' is not found!\n");
        SetOutputColor("def");
        free(Nickname); free(Password);
        return "critical\0";
    }

    char LetterFromFile = '1'; i = 0;
    while(LetterFromFile != '\0'){
        fscanf(ClientsData,"%c",&LetterFromFile);
        //if nickname is not equal to our new
        if(LetterFromFile != Nickname[i++]){
            //we simply skip the whole line
            while(LetterFromFile != '\n')
                fscanf(ClientsData,"%c",&LetterFromFile);
            i=0;
        }
        //if such nickname already exist
        else if(LetterFromFile == ':'){
            SetOutputColor("YELLOW");
            printf("WARNING: some client tried to register with an existing nickname\n");
            SetOutputColor("def");
            free(Nickname); free(Password);
            return "exist\0";
        }
    }
    //if we decided to register client we go back by one symbol
    fpos_t temp; fgetpos(ClientsData, &temp);
    fseek(ClientsData,-1,SEEK_CUR);
    //writting new data
    i = 0;
    while(data[i] != '\0')
        fprintf(ClientsData,"%c",data[i]);
    fprintf(ClientsData,"\n\0");
    fclose(ClientsData);            //end working with client credintals

    RecoveryKey = GenerateRecoveryKey(); //generating recovery key;
    //add error handling
    free(Nickname); free(Password);
    return RecoveryKey;
}

int main(int argc, char const* argv[]){
    //preparations
    if(CheckAllFiles() != 0)
        return -1;
    //++++++++++++++++++++++++++++++++++++++++++++++++++++DATA SEG
    int server_fd, valread;
    int opt = 1;
    pthread_t *ClientsOnServer = (pthread_t*)malloc(sizeof(pthread_t));
    //----------------------------------------------------DATA SEG
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    while(1){
        char *buffer; int WaitClient;
        if (listen(server_fd, 3) < 0) {
            SetOutputColor("RED");
            printf("Client listen error!\n");
            SetOutputColor("def");
            continue;
        }
        if(WaitClient = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen) < 0){
            SetOutputColor("RED");
            printf("Client connection error!\n");
            SetOutputColor("def");
            continue;
        }

        recv(server_fd,buffer,1000,0);
        //client asks for registration
        if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'G'){
            char *response;
            response = RegisterClient(buffer);
            send(WaitClient,response,202,0);
            free(response);
            continue;
        }
        /*  Simple server connect implementation;
        NumberClients++;
        ActiveClients = (int*)realloc(ActiveClients,sizeof(int)*NumberClients);
        if ((ActiveClients[NumberClients-1] = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Server Log: New client arrived\n");

        ClientsOnServer = (pthread_t*)realloc(ClientsOnServer,sizeof(pthread_t)*NumberClients);
        pthread_create(&ClientsOnServer[NumberClients-1],NULL,&WorkingWithClient,&ActiveClients[NumberClients-1]);
        */
    }

    return 0;
}