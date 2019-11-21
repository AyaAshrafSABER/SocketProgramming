//
// Created by saber on ١٩‏/١١‏/٢٠١٩.
//

#include <zconf.h>
#include <cstdio>
#include <netdb.h>
#include "my_client.h"
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ClientManager.h"


int main(int argc, char * argv[])
{
//    if(argc != 3){
//        printf("Invalid number of arguments\n");
//        return 0;
//    }
//    char* ip_number = argv[1];
//    char* port_number = argv[2];
    char* ip_number = "127.0.0.1";
    char* port_number = "8088";

    ClientManager *cm = new ClientManager();
    cm->run_client(ip_number, port_number, "/home/saber/CLionProjects/Http_Client/commands_input_file.txt");
    return 0;
}




