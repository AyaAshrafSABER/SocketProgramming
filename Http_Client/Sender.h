//
// Created by saber on ٢٠‏/١١‏/٢٠١٩.
//

#ifndef HTTP_CLIENT_SENDER_H
#define HTTP_CLIENT_SENDER_H
#include <bits/stdc++.h>
#include "ClientManager.h"
#include "Receiver.h"
#include "Parser.h"


class Sender {
public:
    void sendRequest(Receiver::requestType type, char* hostname, char * port_number, char * file_url, int client_socketfd);
private:
    void waitUnitOK(int client_socketfd, FILE* file);
    void sendGETRequest(char* hostname, char * port_number, char * file_url, int client_socketfd);
    void sendPOSTRequest(char* hostname, char * port_number, char * file_url, int client_socketfd);

};


#endif //HTTP_CLIENT_SENDER_H
