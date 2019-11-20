//
// Created by saber on ١٩‏/١١‏/٢٠١٩.
//

#include "ServerManager.h"
using namespace std;


void ServerManager::run_server(int port_number) {
    init_server(port_number);
    int status;
    /* start listening on this port */
    status = listen(server_socketfd, SERVER_CONNECTION_QUEUE_SIZE);
    /* if error happened print it*/
    if(status){
        perror("error in listening");
        exit(EXIT_FAILURE);
    }
    printf("Server is waiting for connections\n");

    struct sockaddr_storage client_addr;    /* client address info */
    socklen_t sock_size;
    int client;                          /* client socket descriptor */
//    pthread_t tid[MAX_ALLOWED_CONNECTIONS];
//  int i = 0;
    while(1) {
        /* server main loop */
        sock_size = sizeof(client_addr);
        client = accept(server_socketfd, (struct sockaddr *)&client_addr, &sock_size); /* accept connection */
        if(client == -1){
            perror("accept error ");
            continue;
        }
        printf("Successfully Established Connection with a Client has fd = %d \n",client);
        /*
         *    handle the connection, by creating new thread and send it all the information needed
         *    and the function which will handle the connection
         */
        printf("Thread Started for the new client.\n");
        if(clients == MAX_ALLOWED_CONNECTIONS){
            printf("Reached the max limit number of connections, So server can't handle that client connection\n");
            continue;
        }
        //for each client request creates a thread and assign the client request to it to process
        std::thread t(&ServerManager::handle_connection,this,client);
        t.detach();//this will allow the thread run on its own see join function in docs for more information
        clients++;
    }
}
void  ServerManager::handle_connection(int client_fd) {
    // That thread will serve the single client
    int requests_count = 0;
    while(1){
        // serving the requests
        int status = waitForRequest(client_fd);
        if(status == -1){
            printf("No more requests from client with fd = %d within the last 5 seconds, So the server will close the client connection\n",client_fd);
            break;
        }
        handle_request(client_fd);
    }
    mtx.lock();
    clients--;
    mtx.unlock();
}
void  ServerManager::init_server(int port_number) {
    struct sockaddr_in address;
    //initialize number of clients
    clients = 0;
    address.sin_family = AF_INET;
    // Creating socket file descriptor for the server
    if ((server_socketfd = socket(address.sin_family, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    // Check if it is used and forcefully attaching socket to our desired address and port
    if (setsockopt(server_socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_number);

    int ret = bind(server_socketfd, (struct sockaddr *)&address, sizeof(address));
    if (ret < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void  ServerManager::handle_request(int client_fd) {
    const int request_size = 10000;
    char* buffer = (char*) malloc(request_size);
    int val_read = recv(client_fd , buffer, request_size, MSG_PEEK);
    int index = 0;
    int start = -1;
    int end = -1;
    Reciever *r = new Reciever();
    while(index < val_read){
        if(strncmp(buffer + index, "GET", 3) == 0){
            if(start == -1){
                start = index;
            }else if(end == -1){
                end = index - 1;
                printf("%d %d\n",start, end);
                r->receiveRequest(buffer, end - start + 1, client_fd);
                start = end + 1;
                end = -1;
            }
        }else if (strncmp(buffer, "POST", 4) == 0){
            start = -1;
            r->receiveRequest(buffer, val_read, client_fd);
            break;
        }
        index++;
    }
    if(start != -1){
        end = val_read - 1;
        r->receiveRequest(buffer, end - start + 1, client_fd);
    }
}

int  ServerManager::waitForRequest(int client_fd) {
    struct timeval tv;
    /* wait up to 5 seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(client_fd, &rfds);
    int retval = select(1, &rfds, NULL, NULL, &tv);
    return (retval!= -1) ? 1 : -1;
}






