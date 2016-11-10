#include <resolv.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Socket.h"

Socket::Socket(int port){    
    struct hostent *hp;
    //char *host = "127.0.0.1";
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("opening stream socket");
    }

    bzero(&server, sizeof(server));
    hp = gethostbyname("localhost");
    bcopy((char*)hp->h_addr, (char*)&server.sin_addr, hp->h_length);
    server.sin_family = AF_INET;
    server.sin_port = port;
}

Socket::~Socket(){

}
void Socket::Connect(){
    if (connect(sock, (struct sockaddr*)&server, sizeof(server))<0){
        perror("connecting");
    }
}
void Socket::GetResponse(char* out){
    char buf[1024];
    int rval;
    if ((rval = read(sock, buf, 1024)) < 0){
        perror("reading socket");
    }
    strcpy(out,buf);
}
void Socket::SendRequest(char* input){
    //printf(input);
    int rval;
    if ((rval = write(sock, input, 1024)) < 0){
        perror("writing socket");
    }
}