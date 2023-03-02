#ifndef CONSOLEAPPLICATION_SERIALPORT_MSGPACK_H
#define CONSOLEAPPLICATION_SERIALPORT_MSGPACK_H

#include <vector>
#include <iostream>

const std::string READ_COMMAND = "r";
const std::string WRITE_COMMAND = "w";
const std::string UPDATE_COMMAND = "u";
const std::string DELETE_COMMAND = "d";
const std::string PRINT_COMMAND = "p";

class MSGPack {
private:
    std::string command;
    std::string fileName;
    std::string content;

public:
    MSGPack ( ) = default;

    explicit MSGPack ( std::string &com, std::string &file, std::string &cnt );

    static void Pack ( const std::string &msg, MSGPack &packMSG );

    static void Unpack ( const MSGPack &packMSG, std::string &msg );

    std::string getCommand ( ) { return command; }

    void setCommand ( std::string &com ) { command = com; }

    std::string getFileName ( ) { return fileName; }

    void setFileName ( std::string &file ) { fileName = file; }

    std::string getContent ( ) { return content; }

    void setContent ( std::string &cnt ) { content = cnt; }

};

#endif //CONSOLEAPPLICATION_SERIALPORT_MSGPACK_H
