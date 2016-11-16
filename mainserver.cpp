#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <resolv.h>
#include <unistd.h>
#include "socketServer.h"
#include "dir.h"
using namespace std;

static void* SocketThread(void*);
static int decode(const char*, char*);
SocketServer *ss;

inline int ishex(int x)
{
	return	(x >= '0' && x <= '9')	||
		(x >= 'a' && x <= 'f')	||
		(x >= 'A' && x <= 'F');
}

main(){
    ss = new SocketServer(8888);
    pthread_t thread;
    if(ss != NULL){
        while(true){            
            int sock = ss->Accept();    

            pthread_create(&thread, NULL, SocketThread, (void*) &sock);       
            pthread_detach(thread);
        }
    }
}

static void* SocketThread(void* lp){    
    int sock = *(int *) lp;

    char out[1024];
    ss->GetRequest(sock, out);
    //cout<<out<<"\n";
    char *data = strstr( out, "\r\n\r\n" );
    if ( data != NULL )
    {         
        data += 4;
        char strdata[strlen(data - 5)];
        memcpy(&strdata, &data[5],sizeof(strdata));

        //cout<<data;
        char url[strlen(strdata + 1)];

        decode(strdata,url);

        //cout<<url<<"\n";

        if(url != NULL){
            char msg[1024];
            strcpy(msg,"");
            Dir *dir = new Dir();
            dir->GetPaths(url,msg);
            ss->SendResponse(sock,msg);
        }

        // do something with the data
    }

    // char* chars = strtok(out,"\n");
    // while(chars){
    //     char subchar[]
    // }
    //cout<<chars<<"\n";

    

    close(sock);
    
    // char msg[1024];
    // strcpy(msg,"hello");
    // ss->SendResponse(sock,msg);
}

static int decode(const char *s, char *dec)
{
	char *o;
	const char *end = s + strlen(s);
	int c;
 
	for (o = dec; s <= end; o++) {
		c = *s++;
		if (c == '+') c = ' ';
		else if (c == '%' && (	!ishex(*s++)	||
					!ishex(*s++)	||
					!sscanf(s - 2, "%2x", &c)))
			return -1;
 
		if (dec) *o = c;
	}
 
	return o - dec;
}