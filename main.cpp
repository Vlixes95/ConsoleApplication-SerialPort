#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include "SerialPort.h"
#include "msgpack.h"

int main ( ) {

//    std::string sendString;
//
//    std::string command = "r";
//    std::string fileName = "LOGS/Folder/Buenas.txt";
//    std::string content = "Lorem ipsum dolor sit.";
//    MSGPack msgPack = MSGPack( command, fileName, content );
//
//    MSGPack::Unpack( msgPack, sendString );
//
//    MSGPack msgPack1 = MSGPack( );
//    MSGPack::Pack( sendString, msgPack1 );


    SerialPort serialPort( false );
    MSGPack sendPack;
    std::string portName;

    while ( true ) {
        while ( !serialPort.IsConnected( )) {

            std::cout << "Select your COM Port: ";
            std::cin >> portName;
            std::cin.clear( );
            std::cout << '\n';

            if ( portName.length( ) > 0 ) {
                std::string portPathName = R"(\\.\)";
                portPathName.append( portName );

                serialPort.SetPortName( portPathName );
                serialPort.OpenCommPort( );
            }

            if ( !serialPort.IsConnected( )) {
                std::cout << "There has been an error connecting with the COM port. Try again\n";
            }

        }

        // TODO: Protect against integers while()
        std::string election;
        std::cout
                << "\nCommands:\t r (read)\t w (write)\t u (update/override)\t d (delete)\t q (quit)\t p (print content)\n";
        std::cin >> election;
        std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );

        if ( election == "q" ) { break; }

        if ( election != "p" ) {
            sendPack.setCommand( election );
        }

        std::string fileName;
        std::string content;
        // TODO: control pathName length
        std::cout << "Set file path name: ";
        std::cin >> fileName;
        std::cin.clear( );
        std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );
        sendPack.setFileName( fileName );

        if ( election == UPDATE_COMMAND || election == WRITE_COMMAND ) {
            std::cout << "Write the content of the file:\n";
            std::cin >> content;
            std::cin.clear( );
            std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );
            sendPack.setContent( content );
        }

        std::string sendPackedMSG;
        MSGPack::Unpack( sendPack, sendPackedMSG );

        std::string stringRead;
        DWORD bytes;
        DWORD read = 500;

        std::cout << "Connected to: " << serialPort.GetPortName( ) << '\n';

        serialPort.WriteCommPort( sendPackedMSG );
        Sleep(1000);
        serialPort.ReadCommPort( stringRead, read, bytes );

        std::cout << "String read: " << stringRead << '\n';

    }

    return 0;
}

