#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "RegisterLogic/RegisterRequest.h"
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
        fprintf(file,"~");
    }
    fclose(file);
    file = fopen("database/recovery_keys.txt","r+");
    if(!file){
        file = fopen("database/recovery_keys.txt","w");
        fprintf(file,"~");
    }
    fclose(file);
    return 0;
}

void WelcomeMessage(){
    system("clear");
    printf("Server is active now\n"
           "Made by raik199x\n"
           "Ctrl+C to shutdown server\n");
    return;
}

void SigIntHandler(){
    printf("\nDisconnecting all clients\n");
    //add disconnecting
    printf("Shutdowning server\n");
    exit(0);
}

int main(int argc, char const* argv[]){
    //preparations
    if(CheckAllFiles() != 0)
        return -1;
    signal(2,SigIntHandler);
    //++++++++++++++++++++++++++++++++++++++++++++++++++++DATA SEG
    int server_fd, valread;
    int opt = 1;
    pthread_t *ClientsOnServer = (pthread_t*)malloc(sizeof(pthread_t));
    //----------------------------------------------------DATA SEG
    printf("LOG: creating socket\n");
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("LOG: activating socket\n");
    // Forcefully attaching socket to the port 3002
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    printf("LOG: Server will run on 127.0.0.1:3002\n"); //make dynamic?
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    system("sleep 0.5");
    WelcomeMessage();
    while(1){
        char *buffer; int WaitClient = -1;
        if (listen(server_fd, 3) < 0) {
            SetOutputColor("RED");
            printf("Client listen error!\n");
            SetOutputColor("def");
            continue;
        }
        if((WaitClient = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen)) < 0){
            SetOutputColor("RED");
            printf("Client connection error!\n");
            SetOutputColor("def");
            continue;
        }
        buffer = (char*)malloc(1000);
        recv(WaitClient,buffer,1000,0);
        //client asks for registration
        if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'G'){
            char *response;
            response = RegisterClient(buffer);
            send(WaitClient,response,202,0);
            free(response);
            continue;
        } else{
            SetOutputColor("YELLOW");
            printf("WARNING: server get unknown request --- %s\n",buffer);
            SetOutputColor("def");
            buffer[0] = 'B'; buffer[1] = 'A'; buffer[2] = 'D'; buffer[3] = '\0';
            send(WaitClient,buffer,4,0);
            close(WaitClient);
        }
        free(buffer);
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