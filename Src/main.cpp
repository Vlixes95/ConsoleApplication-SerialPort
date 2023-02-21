#include <iostream>
#include "../Inc/SerialPort.h"

int main ( ) {

    SerialPort serialPort( false );

    std::string portPathName = R"(\\.\)";
    std::string portName;


    std::cout << "Select your COM Port: ";
    std::cin >> portName;
    std::cin.clear( );
    std::cout << '\n';

    portPathName.append( portName );

    serialPort.SetPortName( portPathName );
    serialPort.OpenCommPort();

    std::string string = "Send some data";

    std::string stringRead;
    DWORD bytes;
    DWORD read = 500;

    if(serialPort.IsConnected()){

        std::cout << "Connected to: " << serialPort.GetPortName() << '\n';

        serialPort.WriteCommPort(string, string.length());
        serialPort.ReadCommPort(stringRead, read, bytes);

        std::cout << "String read: " << stringRead << '\n';

    }

    return 0;
}
