#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "socketServer.h"

SocketServer::SocketServer(int port){    
    sock = socket (AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("opening stream socket");
    }
    
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = port;

    if (bind (sock, (struct sockaddr *)&server, sizeof server) < 0) {
        perror ("binding stream socket");
    }
    listen (sock, 5);
}

SocketServer::~SocketServer(){
}

int SocketServer::Accept(){
    // sockaddr_in localAddr, remoteAddr;
    // int addrLen = sizeof(remoteAddr);
    
    int msgsock = accept(sock, (struct sockaddr *)0, (socklen_t *)0);
    if (msgsock == -1) {
        perror("accept");
    }

    return msgsock;
}

void SocketServer::GetRequest(int msgsock, char* out){
    char buf[1024];
    int rval;
    if ((rval = read(msgsock, buf, 1024)) < 0){
        perror("reading socket");
    }else{
        strcpy(out,buf);
        //printf(buf);
    }
}

void SocketServer::SendResponse(int msgsock, char* res){    
    // char buf[1024];
    int rval;
    // strcpy(buf,res);
    if ((rval = write(msgsock, res, 1024)) < 0){
        perror("writing socket");
    }
    //close (msgsock);
}