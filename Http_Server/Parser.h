//
// Created by saber on ١٩‏/١١‏/٢٠١٩.
//

#ifndef HTTP_SERVER_PARSER_H
#define HTTP_SERVER_PARSER_H


#include <cstdio>
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
using namespace std;
class Parser {
public:
    int getFileLength(FILE * fp);
    int sendBufferToSocket(char *buffer, int buffer_size, int socketfd);
    void sendFile(FILE* file, int client, char status_line[]);
    string parse_req(string p_toParse, int order_of_returned_str);
};


#endif //HTTP_SERVER_PARSER_H
