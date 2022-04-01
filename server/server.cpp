#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstring>
#include <sys/types.h>

#define DEFAULT_PORT 3002

// 1 создать сокет
// 2 bind объединить с портом+авйпи
// 3 listen Запустить сокет на слушание порта
// 4 если кто-то присоединился accept
// 5 recv recive общение

bool is_client_connection_close(const char*msg){
    for(int i = 0; i < strlen(msg);i++)
        if(msg[i] == '#')
            return true;

    return false;
}

int main(int argc, char *argv[]){
    int client,server;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM,0);
    if (client == -1){
        perror("failed to activate socket");
        exit(-1);
    }
    std::cout << "LOG: socket ready\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client,reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address));
    if (ret == -1){
        perror("Bind failed");
        exit(-1);
    }

    socklen_t size = sizeof(server_address);
    std::cout << "LOG: server listening clients..\n";
    listen(client,1);

    server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    if (server == -1){
        perror("Listening failed");
        exit(-1);
    }

    char buffer[255];
    while(server > 0){
         strcpy(buffer,"-> Server connected!\n");
         send(server,buffer,255,0);
         std::cout << "=> Connected to the client" << std::endl;
         std:: cout << "send # to disconect user\n" << std::endl;
         recv(server,buffer,255,0);
         std::cout << buffer << std::endl;
         if(is_client_connection_close(buffer) == true)
            break;
         
    }

    return 1;
}