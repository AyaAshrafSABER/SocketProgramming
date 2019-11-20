//
// Created by saber on ١٧‏/١١‏/٢٠١٩.
//

#include <cstdlib>
#include "my_Server.h"
#include "ServerManager.h"

int main(int argc, char** argv){
//    if(argc != 2){
//        printf("Invalid number of arguments\n");
//        return 0;
//    }
    printf("Starting Server, Server is waiting now for client connections\n");
    ServerManager *sm = new ServerManager();

    sm->run_server(atoi("8088"));
    return 0;
}