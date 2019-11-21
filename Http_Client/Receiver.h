//
// Created by saber on ٢٠‏/١١‏/٢٠١٩.
//

#ifndef HTTP_CLIENT_RECEIVER_H
#define HTTP_CLIENT_RECEIVER_H
#include <regex>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>

#include "Parser.h"
using namespace std;

class Receiver {
public:
    enum requestType {GET,POST,OTHER} ;
void receiveGETResponse(int client_socketfd, char * filename);
};


#endif //HTTP_CLIENT_RECEIVER_H
