// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT 3002
 
//return size of line
int EnterMessage(char **message){
    char *line; free((*message));
    int line_size = 0, letter_num = 0; char letter;
    line = (char*)malloc(1*sizeof(char));
    printf("Send: ");
    while(1){
        scanf("%c", &letter);
        if(letter == '\0')
            continue;
        else if (letter == '\n'){
            line[letter_num] = '\0';
            break;
        }
        line[letter_num] = letter;
        line_size+=2; letter_num++;
        line = (char*)realloc(line, line_size);
    }
    (*message) = line;
    return line_size;
}

int main(int argc, char const* argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    char *LineSend; LineSend = (char*)malloc(2);
    printf("Request: %s\n",LineSend);
    int size = EnterMessage(&LineSend);
    send(sock,LineSend,size,0);
    recv(sock,LineSend,1000,0);
    printf("Response: %s",LineSend);
    return 0;
}