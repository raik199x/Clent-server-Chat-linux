//standart C libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

//Server libs
#include "RegisterLogic/RegisterRequest.h"
#include "RecoveryLogic/RecoveryRequest.h"
#include "ValidateData/ValidateData.h"
#include "Slots.h"
#include "functions.h"

#define PORT 3002

struct sockaddr_in address;
int addrlen = sizeof(address);

void *WorkingWithClient(void *arg){
    struct Slots *clientSlots = (*(void **)arg);
    printf("Info about new connection: %d - connection descriptor  '%s' - Nickname\n",clientSlots->ConnectionDescriptor, clientSlots->Nickname);
    char *buffer = (char*)malloc(20);
    //preparing message about new client
    buffer[0] = 'A'; buffer[1] = 'D'; buffer[2] = 'D';
    for(int i = 3; clientSlots->Nickname[i-3] != '\0';i++){
        buffer[i] = clientSlots->Nickname[i-3];
        buffer[i+1] = '\0';
    }
    struct Slots *runner = clientSlots;
    //going to the first client
    while(runner->left != NULL) runner = runner->left;
    //Sending everyone that new user joined chat
    while(runner != NULL){
        if(runner->ConnectionDescriptor != -1){
            send(runner->ConnectionDescriptor,buffer,20,0);
            //also sending info about active clients for new user
            if(runner != clientSlots){
                char *tempBuff = (char*)malloc(20); tempBuff[0] = 'A'; tempBuff[1] = 'D'; tempBuff[2] = 'D';
                for(int i = 3; runner->Nickname[i-3]!='\0';i++){
                   tempBuff[i] = runner->Nickname[i-3];
                   tempBuff[i+1] = '\0';
                }
                send(clientSlots->ConnectionDescriptor,tempBuff,20,0);
                free(tempBuff);
            }
        }
        runner = runner->right;
    }
    buffer[0] = 'D'; send(clientSlots->ConnectionDescriptor,buffer,1,0); //tell client that info about users online is over
    //message handler
    while(buffer[0] != '#'){
        free(buffer);
        buffer = (char*)malloc(150);
        recvfrom(clientSlots->ConnectionDescriptor, buffer, 150, 0,(struct sockaddr*)&address, (socklen_t*)&addrlen);
        //sending this message to all clients
        if(buffer[0] == 'M' && buffer[1] == 'E' && buffer[2] == 'S'){
            //beautify message
            char *beautified = (char*)malloc(150); int foundTwoPoints = 0;
            for(int i = 0,j = 0; buffer[i] != '\0';i++,j++){
                if(foundTwoPoints == 0 && buffer[i] == ':'){
                    beautified[j] = buffer[i];
                    j++;
                    beautified[j] = '\n';
                    foundTwoPoints = 1;
                    continue;
                }
                beautified[j] = buffer[i];
            }
            //first of all, running to the start of users
            runner = clientSlots;
            while(runner->left != NULL) runner = runner->left;
            //now sending messages
            while(runner != NULL){
                if(runner->ConnectionDescriptor != -1)
                    send(runner->ConnectionDescriptor,beautified,150,0);
                runner = runner->right;
            }
            free(beautified);
        } else if(buffer[0] == '\0')
            continue;
    }
    //Sending everyone that user leaving chat
    runner = clientSlots;
    free(buffer); buffer = (char*)malloc(20); buffer[0] = 'D'; buffer[1] = 'I'; buffer[2] = 'S';
    for(int i = 3; clientSlots->Nickname[i-3] != '\0';i++){
        buffer[i] = clientSlots->Nickname[i-3];
        buffer[i+1] = '\0';
    }
    while(runner->left != NULL) runner = runner->left;
    while(runner != NULL){
        if(runner->ConnectionDescriptor != -1 && runner != clientSlots)
            send(runner->ConnectionDescriptor,buffer,20,0);
        runner = runner->right;
    }
    //disconnecting
    buffer[0] = '#'; send(clientSlots->ConnectionDescriptor,buffer,1,0);
    free(buffer);
    printf("LOG: Client %s exited normally\n",clientSlots->Nickname);
    close(clientSlots->ConnectionDescriptor);
    clientSlots->ConnectionDescriptor = -1;
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
    printf("\n\nServer is active now\n"
           "Made by raik199x\n"
           "Ctrl+C to shutdown server\n");
    return;
}

struct Slots *slots = NULL;

void SigIntHandler(){
    printf("\nDisconnecting all clients\n");

    struct Slots *runner = slots;
    while(runner != NULL){
        if(runner->ConnectionDescriptor != -1){
            char buffer = '#';
            send(runner->ConnectionDescriptor,&buffer,2,0);
            close(runner->ConnectionDescriptor);
            printf("%s - forcefully disconnected\n",runner->Nickname);
        }
        runner = runner->right;
    }

    printf("Server closed\n");
    exit(0);
}

int RecheckFiles(){
        FILE *file = fopen("database/accounts.txt","r"); int IsAllOkay = 0;
        if(!file){
            SetOutputColor("RED");
            printf("CRITICAL ERROR: file database/accounts.txt is not found!\n");
            SetOutputColor("def");
            return 1;
        }
        fclose(file);
        file = fopen("database/recovery_keys.txt","r");
        if(!file){
            SetOutputColor("RED");
            printf("CRITICAL ERROR: file database/recovery_keys.txt is not found!\n");
            SetOutputColor("def");
            return 1;
        }
        return 0;
}

int main(int argc, char const* argv[]){
    system("clear");
    //preparations
    if(CheckAllFiles() != 0)
        return -1;
    signal(2,SigIntHandler);
    //++++++++++++++++++++++++++++++++++++++++++++++++++++DATA SEG
    int server_fd, valread;
    int opt = 1;
    slots = NULL;
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
    AppendSlots(&slots);
    AppendSlots(&slots);

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

        //validate that server works properly
        if(RecheckFiles() == 1){
            printf("\nServer faced critical error of missing file, what should server do?\n"
                   "1) Recreate files\n"
                   "2) Shutdown server\n");
            int temp; scanf("%d",&temp);
            if(temp == 1){
                CheckAllFiles();
                //clearing all data
                FILE *temp = fopen("database/accounts.txt","w");
                fclose(temp);
                temp = fopen("database/recovery_keys.txt","w");
                fclose(temp);
            }
            else{
                buffer[0] = 'B'; buffer[1] = 'A'; buffer[2] = 'D'; buffer[3] = '\0';
                send(WaitClient,buffer,4,0);
                kill(0,SIGINT);
            }
        }

        //client asks for registration
        if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'G'){
            char *response;
            response = RegisterClient(buffer);
            send(WaitClient,response,202,0);
            free(response);
        } else if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'C'){
            char *response;
            response = RecoverClient(buffer);
            send(WaitClient,response,300,0);
            free(response);
        } else if (buffer[0] == 'C' && buffer[1] == 'O' && buffer[2] == 'N'){
            if(DecideAccess(buffer) == 0){
                SetOutputColor("YELLOW");
                printf("WARNING: client entered not valid data\n");
                SetOutputColor("def");
                buffer[0] = 'B'; buffer[1] = 'A'; buffer[2] = 'D'; buffer[3] = '\0';
                send(WaitClient,buffer,4,0);
                free(buffer);
                close(WaitClient);
                continue;
            }

            struct Slots *runner = slots;
            while(runner->ConnectionDescriptor != -1){
                if(runner->right == NULL)
                    AppendSlots(&runner);
                runner = runner->right;
            }
            runner->ConnectionDescriptor = dup(WaitClient); //copy file descriptor
            //copy nickname
            for(int i = 3; buffer[i] != ':';i++){
                runner->Nickname[i-3] = buffer[i];
                runner->Nickname[i-2] = '\0';
            }
            buffer[0] = 'G'; buffer[1] = 'O'; buffer[2] = '!'; buffer[3] = '\0';
            send(WaitClient,buffer,4,0);
            printf("LOG: Client arrived\n");
            pthread_create(&runner->ClientThread,NULL,&WorkingWithClient,&runner);
        } else { 
            SetOutputColor("YELLOW");
            printf("WARNING: server get unknown request --- %s\n",buffer);
            SetOutputColor("def");
            buffer[0] = 'B'; buffer[1] = 'A'; buffer[2] = 'D'; buffer[3] = '\0';
            send(WaitClient,buffer,4,0);
        }
        close(WaitClient);
        free(buffer);
    }

    return 0;
}