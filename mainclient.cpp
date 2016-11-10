#include "socket.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

main(){
    Socket *cs = new Socket(8888);
    if(cs != NULL){
        cs->Connect();
        char buf[1024];
        cout<<"type some stuffs\n";
        cin.getline(buf, sizeof buf);
        //printf(buf);
        cs->SendRequest(buf);
        char* out;
        cs->GetResponse(out);
        cout<<out;
    }
}