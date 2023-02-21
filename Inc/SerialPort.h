#ifndef CONSOLEAPPLICATION_SERIALPORT_SERIALPORT_H
#define CONSOLEAPPLICATION_SERIALPORT_SERIALPORT_H

#include "windows.h"
#include "winbase.h"
#include <string>

class SerialPort {

private:

    DCB portConfig;
    HANDLE handleCom;

    bool fSuccess;
    DWORD errors;
    COMSTAT status;

    std::string portName;
    bool connected;

public:

    SerialPort ( ) = default;

    ~SerialPort ( ) { }

    explicit SerialPort ( bool connected ) {
        this->connected = connected;
    }

    void OpenCommPort ( );

    bool ConfigureCommPort ( );

    void PrintComPortState ( );

    bool GetCommPortState ( );

    bool SetCommPortState ( );

    std::string GetPortName ( );

    void SetPortName ( std::string portName );

    bool IsConnected ( );

    bool ReadCommPort ( std::string &buffer, DWORD &bytesToRead, DWORD &bytesRead );

    bool WriteCommPort ( const std::string &buffer, const DWORD &bytesToWrite );

};

#endif //CONSOLEAPPLICATION_SERIALPORT_SERIALPORT_H
