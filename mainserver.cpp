#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include <thread>
#include "socketServer.h"
#include "dir.h"
using namespace std;

main(){
    SocketServer *ss = new SocketServer(8888);
    if(ss != NULL){
        int sock = ss->Accept();
        while(true){
            char* out;
            ss->GetRequest(sock, out);
            if(out != NULL){
                char msg[1024];
                strcpy(msg,"");

                Dir *dir = new Dir();
                dir->GetPaths(out,msg);
                ss->SendResponse(sock,msg);
            }
        }
    }
}