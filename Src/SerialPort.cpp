#include "../Inc/SerialPort.h"
#include <iostream>

void SerialPort::OpenCommPort ( ) {

// TODO: Control string size
    std::string portPathName = R"(\\.\)";
    portPathName.append( portName );
    handleCom = CreateFile( static_cast<LPCSTR>(portPathName.c_str( )),
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL );

    LPTSTR errorText = nullptr;
    FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_ALLOCATE_BUFFER
            | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError( ),
            MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
            ( LPTSTR ) &errorText,
            0,
            NULL );

    if ( handleCom == INVALID_HANDLE_VALUE) {
        std::cout << "There has been an error connecting with the COM port. Try again. \n";
        std::cout << "CreateFile failed with following error:\n\t- " << errorText << "\n";
    } else {
        std::cout << "Successfully connected to the COM Port:\t " << GetPortName( ) << "\n";
        connected = true;
    }

    // Initialize the DCB structure
    /* DCB: Define the configuration of the comm port*/
    SecureZeroMemory( &portConfig, sizeof( portConfig ));
    portConfig.DCBlength = sizeof( DCB );

    if ( IsConnected( )) {
        GetCommPortState( );

        if ( ConfigureCommPort( )) {
            std::cout << "COMM Port configuration :\n";
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
    printf( TEXT( "\tBaudrate: %ld, \n\tByteSize: %d, \n\tParity: %d, \n\tStopBits: %d\n" ),
            portConfig.BaudRate,
            portConfig.ByteSize,
            portConfig.Parity,
            portConfig.StopBits
    );
}

bool SerialPort::GetCommPortState ( ) {

    fSuccess = GetCommState( handleCom, &portConfig );
    if ( !fSuccess ) {
        printf( "GetCommPort failed with error %ld.\n", GetLastError( ));
        return false;
    }
    return true;

}

bool SerialPort::SetCommPortState ( ) {

    fSuccess = SetCommState( handleCom, &portConfig );
    if ( !fSuccess ) {
        printf( "SetCommState failed with erros %ld.\n", GetLastError( ));
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

bool SerialPort::ReadCommPort ( std::string &buffer, DWORD &bytesToRead, DWORD &bytesRead ) {

    ClearCommError( handleCom, &errors, &status );

    unsigned int toRead = 0;
    if ( status.cbInQue > 0 ) {
        if ( status.cbInQue > bytesToRead ) {
            toRead = bytesToRead;
        } else {
            toRead = status.cbInQue;
        }

        char *tempBuff = ( char * ) malloc( toRead * sizeof( char ) + 1 );

        if ( !ReadFile( handleCom, tempBuff, bytesToRead, &bytesRead, NULL )) {
            printf( "Failed reading the file\n" );
        }
        tempBuff[toRead] = '\0';
        buffer.append( tempBuff );
        free( tempBuff );
        return true;
    }

    return false;
}

bool SerialPort::WriteCommPort ( std::string &buffer ) {

    LPDWORD bytesWritten = nullptr;
    if ( WriteFile( handleCom, buffer.c_str( ), buffer.length( ), bytesWritten, NULL )) {
        return true;
    }
    ClearCommError( handleCom, &errors, &status );

    return false;
}
