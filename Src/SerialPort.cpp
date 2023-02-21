#include "../Inc/SerialPort.h"
#include <iostream>

void SerialPort::OpenCommPort ( ) {

// TODO: Control string size
    handleCom = CreateFile( static_cast<LPCSTR>(this->portName.c_str( )),
                       GENERIC_READ | GENERIC_WRITE,
                            0,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL );

    if ( handleCom == INVALID_HANDLE_VALUE) {
        printf( "CreateFile failed with error %ld.\n", GetLastError( ));
    } else {
        connected = true;
    }

    // Initialize the DCB structure
    /* DCB: Define the configuration of the comm port*/
    SecureZeroMemory( &portConfig, sizeof( portConfig ));
    portConfig.DCBlength = sizeof( DCB );

    if ( IsConnected( )) {
        GetCommPortState( );

        if ( ConfigureCommPort( )) {
            std::cout << "Serial port configuration :\n";
            GetCommPortState( );
            PrintComPortState( );
        }
    }
    COMMTIMEOUTS a;
    a.ReadIntervalTimeout = 1000;
    a.ReadTotalTimeoutConstant = 1000;
    a.ReadTotalTimeoutMultiplier = 10;
    a.WriteTotalTimeoutConstant = 1000;
    a.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts( handleCom, &a );

}

bool SerialPort::ConfigureCommPort ( ) {
    portConfig.BaudRate = CBR_9600;
    portConfig.ByteSize = 8;
    portConfig.Parity = NOPARITY;
    portConfig.StopBits = ONESTOPBIT;
    if ( !SetCommPortState( )) {
        return false;
    }
    return true;
}

void SerialPort::PrintComPortState ( ) {
    printf( TEXT( "\nBaudrate=%ld, ByteSize=%d, Parity=%d, StopBits=%d\n" ),
            portConfig.BaudRate,
            portConfig.ByteSize,
            portConfig.Parity,
            portConfig.StopBits
    );
}

bool SerialPort::GetCommPortState ( ) {

    fSuccess = GetCommState( handleCom, &portConfig );
    if ( !fSuccess ) {
        printf("GetCommPort failed with error %ld.\n", GetLastError( ));
        return false;
    }
    return true;

}

bool SerialPort::SetCommPortState ( ) {

    fSuccess = SetCommState( handleCom, &portConfig );
    if(!fSuccess){
        printf( "SetCommState failed with erros %ld.\n", GetLastError());
        return false;
    }
    return true;

}

std::string SerialPort::GetPortName ( ) {
    return portName;
}

void SerialPort::SetPortName ( std::string portName ) {
    this->portName = portName;
}

bool SerialPort::IsConnected ( ) {
    return connected;
}
