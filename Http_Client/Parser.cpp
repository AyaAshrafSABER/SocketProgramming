//
// Created by saber on ٢٠‏/١١‏/٢٠١٩.
//

#include "Parser.h"

int Parser::sendBufferToSocket(char *buffer, int buffer_size, int socketfd) {
    int sent = 0;
    const int TIMEOUT = 5;
    clock_t curTime = clock();
    // checking Timeout as socket may fail for many many times so we will stop trying to repeat.
    while(sent < buffer_size && (clock() - curTime)/CLOCKS_PER_SEC < TIMEOUT) {
        sent += send(socketfd, (void *)(buffer + sent), buffer_size - sent, 0);
    }
    if(sent != buffer_size) {
        // then that means not all characters are sent because of timeout */
        return 0;
    }
    return 1;
}

int Parser::getFileLength(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int x = ftell(fp);
    rewind(fp);
    return x;
}

void Parser::sendFile(FILE *file, int client, char *status_line) {
    char statusLine[strlen(status_line)];
    for(int i = 0 ;i < strlen(status_line); i++){
        statusLine[i] = status_line[i];
    }
    //get file size.
    fseek(file, 0, SEEK_END);
    int bufferSize = ftell(file);
    //cout << "The file lenght is :" << bufferSize << endl;
    rewind(file);

    //this creates unique pointer to my array
    unique_ptr<char[]> myBufferedFile = make_unique<char[]>(bufferSize);

    //this reads whole file into buffer.
    int numRead = fread(myBufferedFile.get(), sizeof(char), bufferSize, file);
    int totalSend = bufferSize;

    unique_ptr<char[]> myUniqueBufferToSend = make_unique<char[]>(strlen(statusLine) + bufferSize);
    //add status line.
    memcpy(myUniqueBufferToSend.get(), &statusLine, strlen(statusLine));
    //add data.
    memcpy(myUniqueBufferToSend.get() + strlen(statusLine), myBufferedFile.get(), bufferSize);
    //memcpy(myUniqueBufferToSend.get() + strlen(statusLine), myBufferedFile.get(), bufferSize);

    //cout << "Sending File and headers" << endl;
    //cout << "start of data at " << strlen(statusLine) << endl;
    int iResult = send(client, myUniqueBufferToSend.get() , strlen(statusLine) + bufferSize , 0);
    if (iResult == -1) {
        printf("send failed with error: %d\n");
    }
    cout << "Total bytes send: " << iResult << endl;
    //cout << "Total bytes send: " << iResult << endl;
}




string Parser::parse_req(string p_toParse, int order_of_returned_str) {
    istringstream s(p_toParse);
    string extractedSubmatchPath;
    if(order_of_returned_str == 1){
        s >> extractedSubmatchPath;
        return extractedSubmatchPath;
    }else if(order_of_returned_str == 2){
        s >> extractedSubmatchPath;
        s >> extractedSubmatchPath;
        return extractedSubmatchPath;
    }
    return extractedSubmatchPath;
}
