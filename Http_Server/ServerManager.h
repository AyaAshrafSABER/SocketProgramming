//
// Created by saber on ١٩‏/١١‏/٢٠١٩.
//

#ifndef HTTP_SERVER_SERVERMANAGER_H
#define HTTP_SERVER_SERVERMANAGER_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<pthread.h>
#include <thread>
#include <mutex>
#include "Reciever.h"

class ServerManager {

public:
    void run_server(int port_number);
private:
   // void *handle_connection(void *arg);
    void handle_connection(int client_fd);

    void handle_request(int client_fd);
    int waitForRequest(int client_fd);
    void init_server(int port_number);
    const int SERVER_CONNECTION_QUEUE_SIZE = 10;
    const int MAX_ALLOWED_CONNECTIONS = 20;
    const int MAX_ALLOWED_REQUESTS_PER_CONNECTION = 30;
    int server_socketfd;
// number of clients can be used as counter to handle number of current connections.
    int clients;

    std::mutex mtx;
};


#endif //HTTP_SERVER_SERVERMANAGER_H
