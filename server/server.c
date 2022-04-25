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
    if(!file)
        file = fopen("database/accounts.txt","w");
    fclose(file);
    return 0;
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
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        NumberClients++;
        ActiveClients = (int*)realloc(ActiveClients,sizeof(int)*NumberClients);
        if ((ActiveClients[NumberClients-1] = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Server Log: New client arrived\n");

        ClientsOnServer = (pthread_t*)realloc(ClientsOnServer,sizeof(pthread_t)*NumberClients);
        pthread_create(&ClientsOnServer[NumberClients-1],NULL,&WorkingWithClient,&ActiveClients[NumberClients-1]);
    }

    return 0;
}