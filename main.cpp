#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include "SerialPort.h"
#include "msgpack.h"

int main ( ) {
    
    SerialPort serialPort( false );
    MSGPack sendPack;
    MSGPack receivePack;

    while ( true ) {
        while ( !serialPort.IsConnected( )) {

            std::string portName;
            std::cout << "\nSelect your COM Port: ";
            std::cin >> portName;
            std::cin.clear( );
            std::cout << '\n';

            if ( portName.length( ) > 0 ) {
                serialPort.SetPortName( portName );
                serialPort.OpenCommPort( );
            }
        }

        // TODO: Protect against integers while()
        std::string election;
        std::cout
                << "\nCommands:\n\t - read (r)\n\t - write (w)\n\t - update/override (u)"
                   "\n\t - delete (d)\n\t - quit (q)\n\t - print content (p)\n";
        std::cout << "Election: ";
        std::cin >> election;
        std::cout << "\n";
        std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );

        if ( election == "q" ) { break; }

        sendPack.setCommand( election );

        std::string fileName;
        std::string content;
        // TODO: control pathName length
        if( election != "p") {
            std::cout << "Set file path name: ";
            std::cin >> fileName;
            std::cin.clear( );
            std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );
            sendPack.setFileName( fileName );
        }

        if ( election == UPDATE_COMMAND || election == WRITE_COMMAND ) {
            std::cout << "Write the content of the file:\n";
            std::cin >> content;
            std::cin.clear( );
            std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );
            sendPack.setContent( content );
        }

        std::string sendPackedMSG;
        MSGPack::PackToString( sendPack, sendPackedMSG );

        std::string stringRead;
        DWORD bytes;
        DWORD read = 500;

        std::cout << "Connected to: " << serialPort.GetPortName( ) << '\n';

        serialPort.WriteCommPort( sendPackedMSG );
        Sleep(1000);
        serialPort.ReadCommPort( stringRead, read, bytes );

        MSGPack::Pack( receivePack, stringRead );
        std::cout << "Received content: \n";
        MSGPack::PrintContent( receivePack.getContent() );
    }

    return 0;
}

