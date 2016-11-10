#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
class Socket{
    public:
        Socket(int port);
        ~Socket();
        void Connect();
        void GetResponse(char* out);
        void SendRequest(char* input);
    private:
        int sock;
        struct sockaddr_in server;
};