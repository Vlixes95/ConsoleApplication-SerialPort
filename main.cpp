#include <iostream>
#include "SerialPort.h"
#include "msgpack.h"
#include "actions.h"

int main ( ) {

    SerialPort serialPort( false );
    MSGPack sendPack;
    MSGPack receivePack;

    do {
        std::string portName;
        std::cout << "\nSelect your COM Port: ";
        std::cin >> portName;
        std::cin.clear( );
        std::cout << '\n';

        if ( portName.length( ) > 0 ) {
            serialPort.SetPortName( portName );
            serialPort.OpenCommPort( );
        }
    } while ( !serialPort.IsConnected( ));

    while ( true ) {

        std::string election = ChooseAction( );

        if ( election == "q" ) { break; }
        sendPack.setCommand( election );

        AddFileNameToMSGPack( sendPack, election );
        AddContentToMSGPack( sendPack, election );

        std::string sendPackedMSG;
        MSGPack::PackToString( sendPack, sendPackedMSG );

        serialPort.WriteCommPort( sendPackedMSG );
        Sleep( 500 );

        DWORD bytes;
        DWORD read = 500;
        std::string stringRead;
        serialPort.ReadCommPort( stringRead, read, bytes );

        MSGPack::Pack( receivePack, stringRead );
        std::cout << "Operation message:\n";
        MSGPack::PrintContent( receivePack );
    }

    serialPort.CloseCommPort( );

    return 0;
}
