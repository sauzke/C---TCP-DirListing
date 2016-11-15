class SocketServer{
    public:
        SocketServer(int port);
        ~SocketServer();
        int Accept();
        void GetRequest(int msgsock, char* out);
        void SendResponse(int msgsock, char* res);
    private:
        int sock;
};