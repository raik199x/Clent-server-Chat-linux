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
#define SERVER_IP "127.0.0.1"

bool is_client_connection_close(const char*msg){
    for(int i = 0; i < strlen(msg);i++)
        if(msg[i] == '#')
            return true;

    return false;
}

int main(int argc, char *argv[]){
    int client;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM,0);
    if (client == -1){
        perror("failed to activate socket");
        exit(-1);
    }
    std::cout << "LOG: socket ready\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
    
    std::cout << "\n=> client socket created.";

    int ret = connect(client, reinterpret_cast<const struct sockaddr*>(&server_address),sizeof(server_address));
    if (ret == 0){
        perror("connect failed");
        exit(-1);
    }

std::cout << "Waiting for server confirmation\n";
char buffer[255];
recv(client,buffer,255,0);
std::cout << "Connection established\nTo end connection sed #\n";

while(true){
    std::cin.getline(buffer,255,0);
    send(client,buffer,255,0);
    if(is_client_connection_close(buffer))
        break;
}
    std::cout << "goodbye\n";
    return 0;
}