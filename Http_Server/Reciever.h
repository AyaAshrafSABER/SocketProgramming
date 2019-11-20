//
// Created by saber on ٢٠‏/١١‏/٢٠١٩.
//

#ifndef HTTP_SERVER_RECIEVER_H
#define HTTP_SERVER_RECIEVER_H
#include <string>
#include "Parser.h"
using namespace std;

class Reciever {
public:
    void receiveRequest(char *request, int request_size, int client_socketfd);

private:
    void openFileWithPathAndSend(string file_path, int client);
    void parse_data_from_file(char * buffer, int buffer_size, int &data_start_position, int &data_content_length);
    void receiveGETRequest(int client, int request_size);
    void receivePOSTRequest(int client_socketfd);

};


#endif //HTTP_SERVER_RECIEVER_H
