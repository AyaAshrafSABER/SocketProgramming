//
// Created by saber on ١٩‏/١١‏/٢٠١٩.
//

#ifndef HTTP_CLIENT_CLIENTMANAGER_H
#define HTTP_CLIENT_CLIENTMANAGER_H


#include <cstdio>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include "Receiver.h"
#include "Sender.h"

#define DEFAULT_PORT_NUMBER "80";

using namespace std;
class ClientManager {
public:
    void run_client(char *client_hostname, char *client_portnumber, char* command_url);
private:
    typedef struct command_struct{
        Receiver::requestType type;
        char* file_name;
        char* ip_number;
        char* port_number = DEFAULT_PORT_NUMBER;
    };

    command_struct parse_req(string p_toParse);
    string readCommand();
    void setPortNumber(char* portnumber);
    void setIPNumber(char* hostname);
    int establishConnection(char * client_ipaddress, int client_port_number);
    void closeConnection();
};


#endif //HTTP_CLIENT_CLIENTMANAGER_H
