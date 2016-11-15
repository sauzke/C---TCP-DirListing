#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include "socketServer.h"
#include "dir.h"
using namespace std;

static void* SocketThread(void*);
SocketServer *ss;

main(){
    ss = new SocketServer(8888);
    pthread_t thread;
    if(ss != NULL){
        while(true){            
            int sock = ss->Accept();     

            // cout<<sock<<"\n";   
            // char* out;
            // ss->GetRequest(sock, out);
            // if(out != NULL){
            //     char msg[1024];
            //     strcpy(msg,"");
            //     Dir *dir = new Dir();
            //     dir->GetPaths(out,msg);
            //     ss->SendResponse(sock,msg);
            // }

            pthread_create(&thread, NULL, SocketThread, (void*) &sock);       
            pthread_detach(thread);

            //SocketThread((void*) &sock);     
        }
    }
}

static void* SocketThread(void* lp){    
    // SocketServer *ss = (SocketServer*) lp;
    int sock = *(int *) lp;

    //cout<<sock<<"\n";

    char out[1024];
    ss->GetRequest(sock, out);
    if(out != NULL){
        char msg[1024];
        strcpy(msg,"");
        Dir *dir = new Dir();
        dir->GetPaths(out,msg);
        ss->SendResponse(sock,msg);
    }
}