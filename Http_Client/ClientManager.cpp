//
// Created by saber on ١٩‏/١١‏/٢٠١٩.
//

#include <error.h>
#include <cstring>
#include <vector>
#include "ClientManager.h"

using namespace std;

FILE *fp;
int client_socketfd;
char *commands_file = "/home/saber/CLionProjects/Http_Client/commands_input_file.txt";
char* client_port_number;
char* client_ip;
static const string REGEX_GET_POST = "((GET|POST)\\s(.+)\\s(.+)\\s(.+))";

//steps :
//      a)establish connection for the client
//      b) read Commands from the file
//      c) parse commend from file   -->   1) Get sent commend receive response from server status and data"file"
//                                         2) Post sent commend receive response from server  then sent data to the server
void ClientManager::run_client(char *client_hostname, char *client_portnumber, char *command_url) {
    setIPNumber(client_hostname);
    setPortNumber(client_portnumber);
    printf("Trying to connect to %s on port %s\n",client_hostname, client_portnumber);
    int status = establishConnection(client_hostname, atoi(client_portnumber));
    if(status == 0){
        perror("Failed to connect to the server");
        exit(EXIT_FAILURE);
    }
    printf("Connected Successfully to the server\n");
    // open the file in start Client once.
    fp = fopen(command_url ,"r");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    vector<command_struct> commands;
    Receiver *r = new Receiver();
    Sender *s = new Sender();
    while(1){
        string command_line = readCommand();
        if(command_line.size() == 0 || command_line == ""){
            break;
        }
        command_struct command = parse_req(command_line);
        if(command.type == r->GET){
            commands.push_back(command);
        }else{
            // handling the request using sender
            for(auto x: commands) {
                s->sendRequest(x.type, x.ip_number, x.port_number, x.file_name, client_socketfd);
            }
            for(auto x: commands){
                r->receiveGETResponse(client_socketfd, x.file_name);
            }
            commands.clear();
            //sends post req.
           s->sendRequest(command.type, command.ip_number, command.port_number, command.file_name, client_socketfd);
        }
    }
    for(auto x: commands){
        s->sendRequest(x.type, x.ip_number, x.port_number, x.file_name, client_socketfd);
    }
    for(auto x: commands){
        r->receiveGETResponse(client_socketfd, x.file_name);
    }
    commands.clear();
    closeConnection();
}

int ClientManager::establishConnection(char *client_ipaddress, int client_port_number) {
    int sock;
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\n Socket creation error \n");
        return 0;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(client_port_number);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, client_ipaddress, &serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address / Address not supported \n");
        return 0;
    }
    // Server accepted my connection.
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("\nConnection Failed \n");
        return 0;
    }
    client_socketfd = sock;
    return 1;
}


void ClientManager::setPortNumber(char *portnumber) {
    client_port_number = portnumber;
}

ClientManager::command_struct ClientManager::parse_req(string p_toParse) {
    regex rx(REGEX_GET_POST);
    string extractedSubmatchPath = { "" };
    command_struct result;
    std::smatch pieces_match;
    if (std::regex_match(p_toParse, pieces_match, rx)) {
        std::ssub_match sub_match = pieces_match[2];
        result.type = (sub_match.str() == "GET" ? Receiver::GET : (sub_match.str() == "POST" ? Receiver::POST :Receiver::OTHER));
        sub_match = pieces_match[3];
        result.file_name = strdup(sub_match.str().c_str());
        sub_match = pieces_match[4];
        result.ip_number = strdup(sub_match.str().c_str());
        sub_match = pieces_match[5];
        result.port_number = strdup(sub_match.str().c_str());
    }
    return result;
}

string ClientManager::readCommand() {
    if(fp == NULL) return "";
    char buf[1000];
    if(fgets(buf, sizeof(buf), fp) != NULL){
        string s(buf);
        cout << s << endl;
        return s.substr(0, s.size() - 1);
    }else{
        fclose(fp);
        return "";
    }
}

void ClientManager::closeConnection() {
    close(client_socketfd);
}

void ClientManager::setIPNumber(char *hostname) {
    client_ip = hostname;
}



