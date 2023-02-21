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

    if(serialPort.IsConnected()){

        std::cout << "Connected to: " << serialPort.GetPortName() << '\n';

    }

    return 0;
}
